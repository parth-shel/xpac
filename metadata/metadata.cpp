#include "metadata.h"

metadata::metadata(std::string pkg_name){
	this->pkg_name = pkg_name;
	this->str_hash = new std::hash<std::string>;
	pkg_id = std::to_string((*str_hash)(pkg_name));
	dep_list = new std::vector<std::string>;
}

std::string metadata::get_info(){
	std::string info;
	info += pkg_name + "\n" + pkg_id + "\n";
	if(dep_list!=NULL)
		for(auto && itr=dep_list->begin(); itr!=dep_list->end(); itr++)
			info += *itr+";";
	return info;
}

void metadata::write_package(metadata * package){
	std::ofstream file_object;
	std::string filepath = std::string(".metadata");	//Filename consists of package name and a metadata
	file_object.open(filepath.c_str(),std::ios::out | std::ios::trunc);
	file_object << package->pkg_name << "\n" << package->pkg_id << "\n";
	for(auto&& itr = package->dep_list->begin(); itr!=package->dep_list->end(); itr++)
					file_object<< *itr << "\n";
}

metadata * metadata::get_package(std::string filepath){
	std::ifstream file_object;
	file_object.open(filepath.c_str(),std::ios::in | std::ios::binary);
	metadata * new_package = (metadata*)malloc(sizeof(metadata));
	file_object.read((char*)new_package, sizeof(metadata));
	file_object.close();
	return new_package;
}
