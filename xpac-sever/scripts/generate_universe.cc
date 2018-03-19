#include <stdio.h>
#include <unistd.h>
#include <string>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>

using namespace std;

int main() {
	string name;
	string version;
	string execName;

	cout << "Please enter the name of the package";
	cin >> name;

	cout << "Please enter the version number of the package";
	cin >> version;

	cout << "Please enter the executable name";
	cin >> execName;	

	initialize_universe("universe_of_packages.csv");

	return EXIT_SUCCESS;
}

extern int initialize_universe (const char * file_name) {
	log_file_name = string(file_name);

	if (file_exists(file_name)) { // log file exists
		ofstream log_file(file_name, ios::out | ios::app);

		if(log_file.is_open()) {
			log_file << get_current_time() << "\t---.---.---.---\t\tserver started\n";
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
			log_file << get_current_time() << "\t---.---.---.---\t\tserver started\n";
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

