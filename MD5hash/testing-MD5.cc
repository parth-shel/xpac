#include <stdio.h>
#include <iostream>
#include <cassert>

// uncomment to disable assert()
// #define NDEBUG

#include "MD5checksum.hh"

int main(int argc, char* argv[]) {
	if(argc != 3) {
		std::cout << "please specify file path" << std::endl;
		exit(EXIT_FAILURE);
	}

	MD5checksum* md51 = new MD5checksum(std::string("test1.txt"));
	MD5checksum* md52 = new MD5checksum(std::string("test2.txt"));
	MD5checksum* md53 = new MD5checksum(std::string("test3.txt"));

	assert(md51->compare_hashes(md52));
	std::cout << "files 1 and 2 are the same!" << std::endl;
	assert(!(md51->compare_hashes(md53)));
	std::cout << "files 1 and 3 differ.." << std::endl;

	std::string hash_path(std::string("test2.txt"));
	hash_path.append(".md5hash");
	md52->save_hash();
	assert(md51->compare_saved_hash(hash_path));
	std::cout << "saved hash matches for files 1 and 2!" << std::endl;

	delete md51;
	delete md52;
	delete md53;

	return EXIT_SUCCESS;
}