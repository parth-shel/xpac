#include <stdio.h>
#include <iostream>
#include <cassert>
#include <cstdlib>

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
	MD5checksum* md55 = new MD5checksum(std::string("complexTest"));
	
	std::cout << "\033[1;33m Test Case to check whether the same hash is calculated for similar files \033[0m" << std::endl;
	assert(md51->compare_hashes(md52));
	std::cout << "files 1 and 2 are the same!" << std::endl;
	std::cout << "\033[1;32m Test Case Passed \033[0m" << std::endl;
	
	std::cout << "\033[1;33m Test Case to check whether diferrent hash is calculated for different files \033[0m" << std::endl;
	assert(!(md51->compare_hashes(md53)));
	std::cout << "files 1 and 3 differ.." << std::endl;
	std::cout << "\033[1;32m Test Case Passed \033[0m" << std::endl;
	
	std::cout << "\033[1;33m Test Case to check whether the module can compare the hash of a file to a saved hash \033[0m" << std::endl;
	std::string hash_path(std::string("test2.txt"));
	hash_path.append(".md5hash");
	md52->save_hash();
	assert(md51->compare_saved_hash(hash_path));
	std::cout << "saved hash matches for files 1 and 2!" << std::endl;
	std::cout << "\033[1;32m Test Case Passed \033[0m" << std::endl;
	
	std::cout << "\033[1;33m Test Case to check whether the MD5 hashing module is robust to handle file I/O errors \033[0m" << std::endl;
	assert(!(md54->compare_hashes(md51)));
	std::cout << "file 4 I/O error.." << std::endl;
	std::cout << "\033[1;32m Test Case Passed \033[0m" << std::endl;
	
	std::cout << "\033[1;33m Test Case to check whether the module can handle complex and large files \033[0m" << std::endl;
	md55->save_hash();
    delete md55;
    md55 = new MD5checksum(std::string("complexTest"));
    std::string complex_hash("complexTest.md5hash");
    assert(md55->compare_saved_hash(complex_hash));
    std::cout << "complex hashes match" << std::endl;
	std::cout << "\033[1;32m Test Case Passed \033[0m" << std::endl;

	delete md51;
	delete md52;
	delete md53;
	delete md54;
	delete md55;

	return EXIT_SUCCESS;
}
