#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) {
	string pkg_name;
	unsigned long long pkg_ID;
	string buf;

	vector<string> dependency_list;

	cout << "Enter package name: ";
	cin >> pkg_name;

	cout << "Enter package ID: ";
	cin >> pkg_ID;

	cout << "Enter package ID's of dependencies (enter '-1' when you're done): ";
	while(buf.compare("-1") == 0) {
		cin >> buf;
		if(buf.compare("-1") != 0)
			dependency_list.push_back(buf);
	}

	//write to file


	return EXIT_SUCCESS;
}
