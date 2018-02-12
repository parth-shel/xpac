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
	
	
