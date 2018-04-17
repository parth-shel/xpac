#include <string>
#include <iostream>

#include <stdlib.h>

#include "packR.hh"
#include "lzw.hh"
#include "tar.h"

void pack(std::string file_path) {
	std::string tar_path(file_path);
	tar_path.append(".tar");
	if(tar(file_path.c_str(), tar_path.c_str()) < 0) {
		std::cout << "tar error" << std::endl;
		return;
	}
	if(!compress_file(tar_path)) {
		std::cout << "lzw compression error" << std::endl;
		return;
	}
	return;
}

void unpack(std::string file_path) {
	if(!decompress_file(file_path)) {
		std::cout << "lzw decompression error" << std::endl;
		return;
	}
	if(file_path.find(".tar") != std::string::npos && file_path.length() > 4)
		file_path.erase(file_path.length() - 4, 4);
	if(untar(file_path.c_str()) < 0) {
		std::cout << "untar error" << std::endl;
		return;
	}
	return;
}

int main(int argc, char** argv) {
	if(argc != 3) {
		std::cout << "usage: packR <mode> <path>" << std::endl;
		std::cout << "modes: -p=pack -u=unpack" << std::endl;
		return EXIT_FAILURE;
	}

	if(std::string("-p") == argv[1]) {
		pack(argv[2]);
	}
	else if(std::string("-u") == argv[1]) {
		unpack(argv[2]);
	}
	else {
		std::cout << "invalid mode!" << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
