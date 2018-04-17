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
	std::string pkg_ver;
	std::vector<std::string> * dep_list;
	std::hash<std::string> * str_hash;

	//Member functions:
	public:
	metadata(std::string pkg_name, std::string pkg_ver);
	metadata(): metadata(std::string(""),std::string("")) {}
	std::vector<std::string> * get_dep_list();
	std::string get_info();

	//Static functions for basic file io:
	static void write_package(metadata * package, std::string filepath);
	static metadata * get_package(std::string filepath);

	void add_dep_pkg(std::string pkg_name);
};

#endif
