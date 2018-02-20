#include "metadata.h"
#include<iostream>

metadata::metadata(std::string pkg_name, int size){
	this->pkg_name = pkg_name;
	this->size = size;
	this->str_hash = new std::hash<std::string>;
	pkg_id = std::to_string((*str_hash)(pkg_name));
	dep_list = new std::vector<std::string>;
}

std::string metadata::get_info(){
	std::string info;
	info += "name: " + pkg_name + "\n" + "size: " + std::to_string(size) + "\n" + "id: " + pkg_id + "\n" + "Dependency List: \n";
	for(auto && itr=dep_list->begin(); itr!=dep_list->end(); itr++)
		info += *itr + " ";

	return info;
}

std::string metadata::write_package(metadata * package){
	std::fstream file_object;
	std::string filepath = package->pkg_id;
	file_object.open(filepath,std::ios::out|std::ios::binary);
	file_object.write((char*)package,sizeof(package));
	file_object.close();
	return filepath;
}

metadata * metadata::get_package(std::string filepath){
	std::fstream file_object;
	file_object.open(filepath.c_str(),std::ios::in|std::ios::binary);
	metadata * package = new metadata();
	file_object.read((char*)package, sizeof(metadata));
	file_object.close();
	return package;
}
