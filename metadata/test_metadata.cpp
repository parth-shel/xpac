#include<iostream>
#include "metadata.h"

using namespace std;

int main(){
	metadata * this_pkg = new metadata(std::string("test_pkg"),500);
	cout<<this_pkg->get_info()<<endl;
}
