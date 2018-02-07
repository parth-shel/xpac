#ifndef metadata_h
#define metadata_h

#include<vector>
#include<string>
#include<functional>

class metadata{
	private std::string pkg_name;
	private std::string pkg_hash;
	private std::vector<std::string> dep_list;
	private std::hash<std::string> str_hash;
	private int size;
}

#endif
