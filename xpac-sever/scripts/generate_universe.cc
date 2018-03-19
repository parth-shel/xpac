#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]) {
	string pkg_name;
	string pkg_version;
	string pkg_exe;

	cout << "Enter package name: ";
	cin >> pkg_name;

	cout << "Enter the version number of the package";
	cin >> pkg_version;

	cout << "Please enter the executable name";
	cin >> execName;	


	return EXIT_SUCCESS;
}

int initialize_universe (const char * file_name) {

	if (file_exists(file_name)) { // log file exists
		ofstream log_file(file_name, ios::out | ios::app);

		if(log_file.is_open()) {
			log_file.close();
		}

		else {
			return -1;
		}
	}

	else { // need to create a new file
		ofstream log_file(file_name, ios::out | ios::trunc);

		if (log_file.is_open()) {
			log_file << "TIME\t\t\t\tIP\t\t\tREQUEST\n";
			log_file.close();
		}

		else {
			return -1;
		}			
	}

	return 0;
}

inline bool file_exists(const char * file_name) {
	ifstream f(file_name);
	return f.good();
}

