#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <unordered_set>
#include <iterator>
#include <string>

using namespace std;

unordered_set<string> universe_list;

void parse_universe_of_packages(string, int);
void print_package_set();

void print_package_set() {
	for(auto itr = universe_list.begin(); itr != universe_list.end(); itr++) {
		cout<<*itr<<endl;
	}
}

void parse_universe_of_packages(string filename, int flag) {
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
		if(!flag)
		cout<<"Latest updates are not found! Please run xpac -update your local package database!"<<endl;
	}
}
