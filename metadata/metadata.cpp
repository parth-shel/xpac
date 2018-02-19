#include "metadata.h"
#include <fstream>

metadata::metadata(std::string pkg_name, int size){
	this->pkg_name = pkg_name;
	this->size = size;
	pkg_id = str_hash(pkg_name);
	dep_list = new std::vector<std::string>;
}

std::string metadata::get_info(){
	std::string info;
	info += "name: " + pkg_name + "\n" + "size: " + std::to_string(size) + "\n" + "id: " + pkg_id + "\n" + "Dependency List: \n";
	for(auto && itr=dep_list->begin(); itr!=dep_list->end(); itr++)
		info += *itr + " ";

	return info;
}

void write_package(metadata * package,std::string filepath){
	fstream file_object;
	file_object.open(filepath.c_str(),ios::out|ios::app|ios::binary);
	file_object.write((char*)package,sizeof(package));
}

metadata * metadata::get_package(std::string){
	return NULL;
}
