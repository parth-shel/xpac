/** 
 *	MD5 checksum utility - C++ wrapper around C implementation
 * 
 * @author: parth_shel
 * @version: v:0.1 Apr. 5, 2018
 **/ 

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/md5.h>

#include <string>
#include <fstream>
#include <iostream>

#include "MD5checksum.hh"

MD5checksum::MD5checksum(std::string file_path) {
	this->file_path = file_path;
	this->generate_hash();
}

unsigned long MD5checksum::get_file_size(int fd) {
	struct stat statbuf;
	if(fstat(fd, &statbuf) < 0) {
		return 0;
	}
	return statbuf.st_size;
}

void MD5checksum::generate_hash() {
	int fd;
	unsigned char result[MD5_DIGEST_LENGTH]; 
	void * file_buffer;
	if((fd = open(this->file_path.c_str(), O_RDONLY)) < 0) {
		return;
	}

	if((this->file_size = get_file_size(fd)) == 0) {
		return;
	}
	
	file_buffer = mmap(0, file_size, PROT_READ, MAP_SHARED, fd, 0);
	MD5((unsigned char*) file_buffer, file_size, result);
	munmap(file_buffer, file_size);

	this->result_hash = std::string(reinterpret_cast<char*> (result));
}

std::string MD5checksum::get_hash() {
	return this->result_hash;
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cout << "please specify file path" << std::endl;
		exit(EXIT_FAILURE);
	}

	MD5checksum md5(std::string(argv[1]));
	
	std::cout << "generated MD5 hash: " << md5.get_hash() << std::endl;

	return EXIT_SUCCESS;
}
