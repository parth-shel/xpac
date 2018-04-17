#include <string>
#include <iostream>

#include <stdlib.h>

#include "packR.hh"
#include "lzw.hh"
#include "tar.h"

void pack(std::string file_path) {
	std::string tar_path(file_path);
	tar_path.append(".tar");
	std::cout << "tar'ing: " << file_path << " to " << tar_path << std::endl;
	if(tar(file_path.c_str(), tar_path.c_str()) < 0) {
		std::cout << "tar error" << std::endl;
		return;
	}
	std::cout << "compressing: " << tar_path << std::endl;
	if(!compress_file(tar_path)) {
		std::cout << "lzw compression error" << std::endl;
		return;
	}
	
	std::string rm_command("rm -f ");
	rm_command.append(tar_path);
	// system(rm_command.c_str());
	
	return;
}

void unpack(std::string file_path) {
	std::cout << "decompressing: " << file_path << std::endl;
	if(!decompress_file(file_path)) {
		std::cout << "lzw decompression error" << std::endl;
		return;
	}
	
	if(file_path.find(".lzw") != std::string::npos && file_path.length() > 4)
		file_path.erase(file_path.length() - 4, 4);
	std::string untar_path(file_path);
	if(untar_path.find(".tar") != std::string::npos && untar_path.length() > 4)
		untar_path.erase(untar_path.length() - 4, 4);
	
	std::string mkdir_command("mkdir ");
	mkdir_command.append(untar_path);
	system(mkdir_command.c_str());

	std::cout << "untar'ing: " << file_path << " to " << untar_path << std::endl;
	if(untar(file_path.c_str(), untar_path.c_str()) < 0) {
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
