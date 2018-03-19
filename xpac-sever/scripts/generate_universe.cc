#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

inline bool file_exists(string file_name) {
	fstream fs(file_name.c_str());
	return fs.good();
}

unsigned long long get_pkg_id(string pkg_name, string pkg_version) {
	return str_hash(pkg_name.c_str());
}

int main(int argc, char* argv[]) {
	string pkg_name;
	string pkg_version;
	string pkg_exe;

	cout << "Enter package name: ";
	cin >> pkg_name;

	cout << "Enter version: ";
	cin >> pkg_version;

	cout << "Enter executable file: ";
	cin >> pkg_exe;	
	
	string universe;
	universe.append("universe_of_packages.csv");

	if(file_exists(universe)) {
		ofstream uni_file(universe.c_str(), ios::out | ios::app);

		unifile << get_pkg_id(pkg_name, pkg_version) << "," << pkg_name << "," << pkd_version << "," << pkg_exe << endl;
	}

	else {
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
