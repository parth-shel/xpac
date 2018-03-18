#include<iostream>
#include "metadata.h"

using namespace std;

int main(){
	metadata * this_pkg = new metadata(std::string("test_pkg"));
	cout<<"Local package:\n";
	cout<<this_pkg->get_info()<<endl;
	cout<<"Read package:\n";
  metadata::write_package(this_pkg);
}
