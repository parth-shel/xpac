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
#include <unistd.h>
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

MD5checksum::~MD5checksum() {

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
	if((fd = open(file_path.c_str(), O_RDONLY)) < 0) {
		return;
	}

	if((file_size = get_file_size(fd)) == 0) {
		return;
	}
	
	file_buffer = mmap(0, file_size, PROT_READ, MAP_SHARED, fd, 0);
	MD5((unsigned char*) file_buffer, file_size, result);
	munmap(file_buffer, file_size);

	close(fd);

	// testing
	for(int i = 0;i < MD5_DIGEST_LENGTH;i++) {
		printf("%02x", result[i]);
	}

	std::string hash_file = file_path;
	hash_file.append(".md5hash");

	FILE * f = fopen(hash_file.c_str(), "w");
	for(int i = 0;i < MD5_DIGEST_LENGTH;i++) {
		fprintf(f, "%02x", result[i]);
	}

	// this->result_hash = std::string(reinterpret_cast<char*> (result));
}

/*std::string MD5checksum::get_hash() {
	return this->result_hash;
}*/

bool MD5checksum::compare_hashes(std::string that) {
	std::string hash_file = this->file_path;
	hash_file.append(".md5hash");

	FILE * that_f = fopen(that.c_str(), "r");
	if(that_f == NULL) {
		return false;
	}
	
	FILE * this_f = fopen(hash_file.c_str(), "r");
	if(this_f == NULL) {
		return false;
	}

	unsigned char that_c, this_c;

	while(that_c!=EOF || this_c!=EOF) {
		fscanf(that_f, "%02x", &that_c);
		fscanf(this_f, "%02x", &this_c);
		if(that_c != this_c) {
			return false;
		}
	}

	return true;
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cout << "please specify file path" << std::endl;
		exit(EXIT_FAILURE);
	}

	MD5checksum* md5 = new MD5checksum(std::string(argv[1]));
	
	// std::cout << "generated MD5 hash: " << md5->get_hash() << std::endl;

	char compare[32];
	sprintf(compare, "%s.md5hash", argv[1]);

	if(md5->compare_hashes(std::string(compare))) {
		std::cout << "this shit works!" << std::endl;
	}

	delete md5;

	return EXIT_SUCCESS;
}
