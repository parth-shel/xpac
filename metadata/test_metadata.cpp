#include<iostream>
#include "metadata.h"

using namespace std;

int main(){
	metadata * this_pkg = new metadata(std::string("test_pkg"),500);
	cout<<"Local package:\n";
	cout<<this_pkg->get_info()<<endl;
	cout<<"Read package:\n";
	string filepath = metadata::write_package(this_pkg);
	cout<<filepath;
	metadata * read_pkg = metadata::get_package(filepath);
	//cout<<read_pkg->get_info()<<endl;
}
