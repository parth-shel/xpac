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
	if(dep_list->size()>0 && dep_list!=NULL)
		for(auto && itr=dep_list->begin(); itr!=dep_list->end(); itr++)
			info += *itr+";";
	return info;
}

std::string metadata::write_package(metadata * package){
	std::ofstream file_object;
	std::string filepath = package->pkg_id;
	file_object.open(filepath.c_str(),std::ios::out | std::ios::binary| std::ios::trunc);
	file_object.write((char*)package, sizeof(package));
	file_object.close();
	return filepath;
}

metadata * metadata::get_package(std::string filepath){
	std::ifstream file_object;
	file_object.open(filepath.c_str(),std::ios::in | std::ios::binary);
	metadata * new_package = (metadata*)malloc(sizeof(metadata));
	file_object.read((char*)new_package, sizeof(metadata));
	file_object.close();
	return new_package;
}
