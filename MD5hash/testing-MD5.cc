#include <stdio.h>
#include <iostream>
#include <cassert>

// uncomment to disable assert()
// #define NDEBUG

#include "MD5checksum.hh"

int main(int argc, char* argv[]) {
	/*if(argc != 3) {
		std::cout << "please specify file path" << std::endl;
		exit(EXIT_FAILURE);
	}*/

	MD5checksum* md51 = new MD5checksum(std::string("test1.txt"));
	MD5checksum* md52 = new MD5checksum(std::string("test2.txt"));
	MD5checksum* md53 = new MD5checksum(std::string("test3.txt"));
	MD5checksum* md54 = new MD5checksum(std::string("badtest.txt"));

	assert(md51->compare_hashes(md52));
	std::cout << "files 1 and 2 are the same!" << std::endl;
	std::cout << "\033[1;32m Test Case Passed \033[0m" << std::endl;
	assert(!(md51->compare_hashes(md53)));
	std::cout << "files 1 and 3 differ.." << std::endl;
	std::cout << "\033[1;32m Test Case Passed \033[0m" << std::endl;
	
	std::string hash_path(std::string("test2.txt"));
	hash_path.append(".md5hash");
	md52->save_hash();
	assert(md51->compare_saved_hash(hash_path));
	std::cout << "saved hash matches for files 1 and 2!" << std::endl;
	std::cout << "\033[1;32m Test Case Passed \033[0m" << std::endl;
	
	assert(!(md54->compare_hashes(md51)));
	std::cout << "file 4 I/O error.." << std::endl;
	std::cout << "\033[1;32m Test Case Passed \033[0m" << std::endl;
	
	delete md51;
	delete md52;
	delete md53;
	delete md54;

	return EXIT_SUCCESS;
}
