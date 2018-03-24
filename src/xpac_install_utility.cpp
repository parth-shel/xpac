#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <set>
#include <iterator>
#include <string>

using namespace std;

static set<string> universe_list;

void parse_universe_of_packages(string);
void print_package_set();

void print_package_set() {
	set<string>::iterator itr;
	for(itr = universe_list.begin(); itr != universe_list.end(); itr++) {
		cout<<*itr<<endl;
	}
}

void parse_universe_of_packages(string filename) {
	// assuming relative filepath
	// file resides in same directory as xpac_install_utility executable
	// change accordingly to the needs
	ifstream file(filename.c_str());
	if(file.is_open()) {
		string line;
		string token;
		getline(file, line);// skip first line containing column headings
		while(getline(file, line)) {
			istringstream stream(line);
			// parse PKGID
			getline(stream, token, ',');
			// parse package name
			getline(stream, token, ',');
			universe_list.insert(token);// add package name to set
			// parse package version
			getline(stream, token, ',');
			// parse executable name
			getline(stream, token, '\n');
		} 
	} else {
		cout<<"File not found"<<endl;
	}
}

/*
int main(int argc, char ** argv) {
	if(argc < 1) {
		cout<<"Usage: xpac_install_utility <universe_of_packages>"<<endl;
	}
	string filename = string(argv[1]);
	parse_universe_of_packages(filename);
	print_package_set();
	return 1;
}*/
