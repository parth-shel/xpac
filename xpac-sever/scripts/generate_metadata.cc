#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	string pkg_name;
	string pkg_version;
	unsigned long long pkg_ID;
	string buf;

	vector<string> dependency_list;

	cout << "Enter package name: ";
	cin >> pkg_name;

	cout << "Enter version: ";
	cin >> pkg_version;

	cout << "Enter package ID: ";
	cin >> pkg_ID;

	cout << "Enter package ID's of dependencies (enter '-1' when you're done): ";
	while(buf.compare("-1") != 0) {
		cin >> buf;
		if(buf.compare("-1") != 0)
			dependency_list.push_back(buf);
	}

	string path;
	path.append("./repo/");
	path.append(pkg_name);
	path.append("/");
	path.append(pkg_version);
	path.append("/.metadata");

	cout << path << endl;

	ofstream meta_file(path.c_str(), ios::out | ios::trunc);

	if(meta_file.is_open()) {
		meta_file << pkg_name << endl;
		meta_file << pkg_ID << endl;
		for(vector<string>::iterator itr = dependency_list.begin(); itr != dependency_list.end(); ++itr) {
			meta_file << *itr << endl;
		}
		meta_file << endl;
	}
	meta_file.close();

	return EXIT_SUCCESS;
}
