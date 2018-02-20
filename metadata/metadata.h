#ifndef metadata_h
#define metadata_h

#include<vector>
#include<string>
#include<functional>
#include<fstream>

class metadata{

	//Data Members:
	private:
	std::string pkg_name;
	std::string pkg_id;
	std::vector<std::string> * dep_list;
	std::hash<std::string> * str_hash;
	int size;

	//Member functions:
	public:
	metadata(std::string pkg_name, int size);
	metadata(): metadata(std::string(""),0) {}
	std::string get_info();

	//Static functions for basic file io:
	static std::string write_package(metadata * package);
	static metadata * get_package(std::string filepath);
};

#endif
