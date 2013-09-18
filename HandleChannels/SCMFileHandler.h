#ifndef SCMFILEHANDLER_H
#define SCMFILEHANDLER_H

// c std libraries
#include <ctime>
#include <cstdint>

// c++ std libraries
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <vector>

// third party libraries
#define ZLIB_WINAPI
#include <contrib\minizip\unzip.h>
#include <contrib\minizip\zip.h>

class SCMFileHandler
{
public:
	SCMFileHandler();
	~SCMFileHandler();

	// open exisiting scm archive file
	bool open(std::string scm_file_name);
	// save all fles into scm file
	bool save(std::string out_file_name);
	// obtain raw buffer data from file
	bool get_raw_data_from_file(std::string file_name, std::vector<int8_t>& dst_buffer);
	// update buffer content in file
	bool update_raw_data_in_file(std::string file_name, std::vector<int8_t>& src_buffer);

private:
	// contains buffer data of file
	std::unordered_map<std::string, std::vector<int8_t>> _file_map;
	// contains information about file (size, ...)
	std::unordered_map<std::string, unz_file_info> _file_info_map;
};

#endif
