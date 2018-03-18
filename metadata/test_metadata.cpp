#include<iostream>
#include "metadata.h"

using namespace std;

int main(){
	metadata * this_pkg = new metadata(std::string("test_pkg"),std::string("1.0.0"));
	std::string dep_pkg;
	while(cin>>dep_pkg)
					this_pkg->add_dep_pkg(dep_pkg);
	cout<<"Local package:\n";
	cout<<this_pkg->get_info()<<endl;
	cout<<"Read package:\n";
  metadata::write_package(this_pkg);
	metadata * new_pkg = metadata::get_package(std::string(".metadata"));
	cout<<new_pkg->get_info();
}
