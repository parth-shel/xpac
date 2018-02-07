#ifndef metadata_h
#define metadata_h

//Including the following for hashing:
#include "xxhash.hpp"

#include<vector>
#include<string>

class metadata{
	private std::string pkg_name;
	private std::string pkg_hash;
	private std::vector<std::string> dep_list;
	private int size;

}

#endif
