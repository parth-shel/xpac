#include "metadata.h"

metadata::metadata(std::string pkg_name, int size){
	this->pkg_name = pkg_name;
	this->size = size;
	this->str_hash = new std::hash<std::string>;
	pkg_id = std::to_string((*str_hash)(pkg_name));
	dep_list = new std::vector<std::string>;
}

std::string metadata::get_info(){
	std::string info;
	info += pkg_name + "\n" + std::to_string(size) + "\n" + pkg_id + "\n";
	for(auto && itr=dep_list->begin(); itr!=dep_list->end(); itr++)
		info += *itr+";";
	return info;
}

std::string metadata::write_package(metadata * package){
	std::ofstream file_object;
	std::string filepath = package->pkg_id;
	file_object.open(filepath);
	file_object << package->get_info();
	file_object.close();
	return filepath;
}

metadata * metadata::get_package(std::string filepath){
	std::ifstream file_object;
	file_object.open(filepath.c_str());
	metadata * package = new metadata();
	std::string line_read_arr[4];
	std::string next_line;
	int i = 0;
	while(getline(file_object,next_line)){
		line_read_arr[i++] = next_line;
	}
	package->pkg_name = line_read_arr[0];
	package->size = 	
	file_object.close();
	return package;
}
