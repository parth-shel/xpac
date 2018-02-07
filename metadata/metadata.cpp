#include "metadata.h"

metadata::metadata(std::string pkg_name, int size){
	this.pkg_name = pkg_name;
	this.size = size;
	pkg_id = str_hash(pkg_name);
	dep_list = new std::vector<std::string>;	
}	

metadata::print_info(){
	cout<<"
}
	
	
