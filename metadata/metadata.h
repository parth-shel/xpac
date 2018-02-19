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
	std::hash<std::string> str_hash;
	int size;

	//Member functions:
	public:
	metadata(std::string pkg_name, int size);
	std::string get_info();
	void write_package(metadata * package,std::string filepath);
	metadata * get_package(std::string filepath);
};

#endif
