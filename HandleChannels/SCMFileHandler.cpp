#include "SCMFileHandler.h"

#include <dos.h>

SCMFileHandler::SCMFileHandler()
{
	// empty, so far
}


SCMFileHandler::~SCMFileHandler()
{
	// empty, so far
}

bool SCMFileHandler::open(std::string scm_file_name)
{
	// variables needed for parsing
	const int FILENAME_MAX_SIZE = 512;
	char file_name_buffer[FILENAME_MAX_SIZE];
	//const int BUFFER_MAX_SIZE = 8192;
	//uint8_t file_buffer[BUFFER_MAX_SIZE];

	// clear current content of all file maps
	_file_map.clear();
	_file_info_map.clear();

	// open scm file
	unzFile in_zip_file = unzOpen(scm_file_name.c_str());
	// contains results of unz functions
	int res = UNZ_OK; // 0
	// info about zip file (number of entries)
	unz_global_info g_info;
	res = unzGetGlobalInfo(in_zip_file, &g_info);

	if (res != UNZ_OK)
	{
		std::cout	<< "[ERROR]: Could not load scm file <" 
					<< scm_file_name 
					<< ">! Archive file may be corrupted." << std::endl;
		unzClose(in_zip_file);
		return false;
	}

	for (uint8_t i = 0; i < g_info.number_entry; ++i)
	{
		unz_file_info f_info;
		// obtain file name and info of current regarded file
		res = unzGetCurrentFileInfo(in_zip_file, &f_info, 
									file_name_buffer, FILENAME_MAX_SIZE,
									nullptr, 0, nullptr, 0);

		if (res != UNZ_OK)
		{
			std::cout	<< "[ERROR]: Could not obtain file info from scm file" 
						<< scm_file_name 
						<< ">! Archive file may be corrupted." << std::endl;
			unzCloseCurrentFile(in_zip_file);
			unzClose(in_zip_file);
			return false;
		}

		// open current regarded file in zip archive
		res = unzOpenCurrentFile(in_zip_file);

		if (res != UNZ_OK)
		{
			std::cout	<< "[ERROR]: Could not open file <" 
						<< file_name_buffer
						<< "> in archive <"
						<< scm_file_name 
						<< ">! File may be corrupted." << std::endl;
			unzCloseCurrentFile(in_zip_file);
			unzClose(in_zip_file);
			return false;
		}

		// write content of file into memory buffer
		std::vector<int8_t> file_data(f_info.uncompressed_size);
		res = unzReadCurrentFile(in_zip_file, &file_data[0], file_data.size());

		if (res < 0)
		{
			std::cout	<< "[ERROR]: Could not read file <" 
						<< file_name_buffer
						<< "> in archive <"
						<< scm_file_name 
						<< ">! File may be corrupted." << std::endl;
			unzCloseCurrentFile(in_zip_file);
			unzClose(in_zip_file);
			return false;
		}

		// store file buffer data and info in class maps
		_file_map[file_name_buffer] = file_data;
		_file_info_map[file_name_buffer] = f_info;

		unzCloseCurrentFile(in_zip_file);

		// go to the next file in scm archive
		res = unzGoToNextFile(in_zip_file);

		if (res < 0 && i < g_info.number_entry - 1)
		{
			std::cout	<< "[ERROR]: Could not read next file in archive" 
						<< scm_file_name 
						<< ">! Archive may be corrupted." << std::endl;
			unzClose(in_zip_file);
			return false;
		}
	}

	unzClose(in_zip_file);
	return true;
}

bool SCMFileHandler::save(std::string out_file_name)
{
	// create new scm file or overwrite existing scm file
	zipFile out_zip_file = zipOpen(out_file_name.c_str(), APPEND_STATUS_CREATE);

	// if scm could not be created
	if (out_zip_file == 0)
	{
		std::cout	<< "[ERROR]: Could not create scm file <"
					<< out_file_name << ">!" << std::endl;
		return false;
	}

	// put all files into scm archive
	for (auto it = _file_map.cbegin(); it != _file_map.cend(); ++it)
	{
		// copy unz_file_info into zip_fileinfo
		zip_fileinfo f_info = {0};
		unz_file_info uf_info = _file_info_map[it->first];
		f_info.dosDate = uf_info.dosDate;
		f_info.external_fa = uf_info.external_fa;
		f_info.internal_fa = uf_info.internal_fa;
		memcpy(	&f_info.tmz_date, 
				&uf_info.tmu_date, 
				sizeof(f_info.tmz_date));

		// create new file in scm archive
		int res = zipOpenNewFileInZip(out_zip_file, it->first.c_str(), &f_info,
									nullptr, 0, nullptr, 0, nullptr, 
									Z_DEFLATED, Z_DEFAULT_COMPRESSION);

		if (res != ZIP_OK)
		{
			std::cout	<< "[ERROR]: Could not create file <"
						<< it->first << "> in output archive <"
						<< out_file_name << ">." << std::endl;
			zipCloseFileInZip(out_zip_file);
			zipClose(out_zip_file, nullptr);
			return false;
		}

		// write buffer data into this file
		res = zipWriteInFileInZip(out_zip_file, &it->second[0], it->second.size());

		if (res != ZIP_OK)
		{
			std::cout	<< "[ERROR]: Could not write data in file <"
						<< it->first << "> in output archive <"
						<< out_file_name << ">." << std::endl;
			zipCloseFileInZip(out_zip_file);
			zipClose(out_zip_file, nullptr);
			return false;
		}

		// close the current created file
		zipCloseFileInZip(out_zip_file);

	}

	zipClose(out_zip_file, nullptr);
	return true;
}

bool SCMFileHandler::get_raw_data_from_file(std::string file_name, std::vector<int8_t>& dst_buffer)
{	
	// locate required file data, if exists
	auto it = _file_map.find(file_name);

	// if there is no file, return false
	if (it == _file_map.cend())
	{
		std::cout	<< "[ERROR]: Could not find file <"
					<< file_name << ">." << std::endl;
		return false;
	}

	// resize vector to required byte size
	dst_buffer.resize(_file_info_map[file_name].uncompressed_size);

	// copy data into dst_buffer
	std::copy(it->second.cbegin(), it->second.cend(), dst_buffer.begin());
	return true;
}

bool SCMFileHandler::update_raw_data_in_file(std::string file_name, std::vector<int8_t>& src_buffer)
{
	// locate file name in map
	auto it = _file_map.find(file_name);

	// if file was not found
	if (it == _file_map.end())
	{
		std::cout	<< "[ERROR]: Could not update file <"
					<< file_name << ">." << std::endl;
		// do not perform an update
		return false;
	}

	// update element
	_file_map[file_name] = src_buffer;
	// update file info
	// -> new uncompressed size
	_file_info_map[file_name].uncompressed_size = src_buffer.size();

	time_t t = time(0);
	tm t_today;
	localtime_s(&t_today, &t);

	// create dos data of format YYYYYYYM MMMDDDDD HHHHHMMM MMMSSSSS
	uint32_t dosData = 0;
	dosData = (t_today.tm_year - 80) & 0x7F;
	dosData <<= 4;
	dosData |= (t_today.tm_mon + 1) & 0xF;
	dosData <<= 5;
	dosData |= t_today.tm_mday & 0x1F;
	dosData <<= 5;
	dosData |= t_today.tm_hour & 0x1F;
	dosData <<= 6;
	dosData |= t_today.tm_min & 0x3F;
	dosData <<= 5;
	dosData |= t_today.tm_sec & 0x1F;

	// -> new modification time
	_file_info_map[file_name].dosDate = dosData;
	_file_info_map[file_name].tmu_date.tm_hour = t_today.tm_hour;
	_file_info_map[file_name].tmu_date.tm_mday = t_today.tm_mday;
	_file_info_map[file_name].tmu_date.tm_min = t_today.tm_min;
	_file_info_map[file_name].tmu_date.tm_mon = t_today.tm_mon;
	_file_info_map[file_name].tmu_date.tm_sec = t_today.tm_sec;
	_file_info_map[file_name].tmu_date.tm_year = t_today.tm_year;

	return true;
}
