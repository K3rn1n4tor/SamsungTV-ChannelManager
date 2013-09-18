#include <cstdio>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <Windows.h>

//#define ZLIB_WINAPI
//#include <contrib\minizip\unzip.h>
//#include <contrib\minizip\zip.h>

#include "SCMFileHandler.h"

//#pragma comment(lib,"../Libraries/zlib-1.2.5/staticx64/zlibstat.lib")

using namespace std;

const uint32_t MAX_BUFFER_SIZE = 10000000;//8192;
const uint16_t MAX_FILENAME_SIZE = 512;

void check_unz_error(unzFile file, int error);

int main(int argc, char**argv)
{
	SCMFileHandler SCMHandler;
	SCMHandler.open("../Data/Test.scm");

	std::vector<int8_t> data, data2;
	SCMHandler.get_raw_data_from_file("CloneInfo", data);
	SCMHandler.get_raw_data_from_file("CloneInfo2", data2);

	data.push_back(95);
	SCMHandler.update_raw_data_in_file("CloneInfo", data);

	SCMHandler.save("../Data/OutTest.scm");

	////////////////////////////////////////////////////////////////////////////
	// Example unzip smc file

	
	/*char read_buffer[MAX_BUFFER_SIZE];
	char f_name[MAX_FILENAME_SIZE];

	// open zip file (SCM)
	unzFile file = unzOpen64("../Data/Test.scm");
	cout << "open Test.scm..." << endl;

	// read global info of scm file (number of files)
	unz_global_info64 g_info;

	// unzip result
	int unz_result = UNZ_OK;

	// if no valid zip file --> return error
	unz_result = unzGetGlobalInfo64(file, &g_info) != UNZ_OK;
	check_unz_error(file, unz_result);
	cout << "number of files in scm: " << g_info.number_entry << endl;

	// read all files
	for (uint16_t i = 0; i < g_info.number_entry - 1; ++i)
	{
		unz_file_info64 f_info;

		// read file descriptor info
		unz_result = unzGetCurrentFileInfo64(file, &f_info, f_name, MAX_FILENAME_SIZE, nullptr, 0, nullptr, 0);
		check_unz_error(file, unz_result);

		cout << f_name << endl;
		cout << f_info.compressed_size << endl;
		cout << f_info.uncompressed_size << endl;

		// read current file
		unz_result = unzOpenCurrentFile(file);
		check_unz_error(file, unz_result);

		

		stringstream o_fname;
		o_fname << f_name;

		FILE* o_file;
		fopen_s(&o_file,o_fname.str().c_str(), "wb");

		if (o_file == nullptr)
		{
			cout << "Could not uncompress file < " << o_fname.str() << ">." << endl;
			system("pause");
			unzCloseCurrentFile(file);
			unzClose(file);
			return -1;
		}

		do 
		{
			unz_result = unzReadCurrentFile(file, read_buffer, MAX_BUFFER_SIZE);
			//check_unz_error(file, unz_result);
			if (unz_result < 0)
			{
				cout << "Error" << endl;
				system("pause");
				unzCloseCurrentFile(file);
				unzClose(file);
				exit(-1);
			}

			if (unz_result > 0)
			{
				fwrite(read_buffer, unz_result, 1, o_file);
			}

		} while (unz_result > 0);
		
		fclose(o_file);

		unzCloseCurrentFile(file);

		// go to next file
		unz_result = unzGoToNextFile(file);
		check_unz_error(file, unz_result);
	}

// seems to be a bug in 64-Bit!
#ifndef _DEBUG
	unzClose(file);
#endif*/

	////////////////////////////////////////////////////////////////////////////
	//Example create zip file

	/*zipFile outZip = zipOpen64("Test.zip", APPEND_STATUS_CREATE);
	
	if (outZip == 0)
	{
		cout << "Error: Could not create Test.zip" << endl;
	}

	// zip is deflated, if compression_method = 8
	// no compression, if compression_method = 0
	zip_fileinfo info = { 0 };
	int res = zipOpenNewFileInZip64(outZip,"Test.txt", &info, nullptr, 0, nullptr, 0, nullptr, Z_DEFLATED, Z_DEFAULT_COMPRESSION, 0);

	if (res != ZIP_OK)
	{
		cout << "Error" << endl;
		zipCloseFileInZip(outZip);
		zipClose(outZip, nullptr);
		system("pause");
		return -1;
	}

	char* testStr = "Dies ist eine Testdatei";
	res = zipWriteInFileInZip(outZip, testStr, strlen(testStr));
	if (res != ZIP_OK)
	{
		cout << "Error" << endl;
		zipCloseFileInZip(outZip);
		zipClose(outZip, nullptr);
		system("pause");
		return -1;
	}



	zipCloseFileInZip(outZip);
	zipClose(outZip, nullptr);*/


	system("pause");
	return 0;
}

void check_unz_error(unzFile file, int error)
{
	if (error != UNZ_OK)
	{
		cout << "Error" << endl;
		unzClose(file);
		system("pause");
		exit(-1);
	}
}

