#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <map>
#include <iterator>
#include <string>

using namespace std;

map<string,string> universe_list;

void parse_universe_of_packages(string);
void print_package_set(std::map<std::string, std::string>& to_print);

void print_package_set(std::map<std::string, std::string>& to_print) {
	for(auto itr = to_print.begin(); itr != to_print.end(); itr++) {
		cout<<"Package name: "<<(itr->first)<<" "<<"Package version: "<<(itr->second)<<endl;
	}
}

void parse_universe_of_packages(string filename) {
	universe_list.clear();
	// assuming relative filepath
	// file resides in same directory as xpac_install_utility executable
	// change accordingly to the needs
	ifstream file(filename.c_str());
	string name;
	string version;
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
			name = token;
			// parse package version
			getline(stream, token, ',');
			version = token;
			universe_list.insert(make_pair(name,version));// add package name to set
			// parse executable name
			getline(stream, token, '\n');
		} 
	} else {
		cout<<"Local package database not found!"<<endl;
	}
}
