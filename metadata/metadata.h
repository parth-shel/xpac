#ifndef metadata_h
#define metadata_h

#include<vector>
#include<string>
#include<functional>

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
	metdata(std::string pkg_name, int size);
	print_info();	//For debugging purposes only
};

#endif
