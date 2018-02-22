#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <stdio.h>

using namespace std;

void man_help() {
	string line;
	string token;
	ifstream help_file("man_help_txt");
	if(help_file.is_open()) {
		cout<<"These are common xpac commands used in various situations:"<<endl<<endl;		
		while(getline(help_file, line)) {	
			istringstream stream(line);
			// parse command option
			getline(stream, token, '|');
			string option_str = token;
			// parse functionality
			getline(stream, token, '\n');
			string functionality_str = token;
			
			// display to standard output
			printf("%-35s %-100s\n\n", option_str.c_str(), functionality_str.c_str());
		}

	} else {
		cout<<"Error accessing xpac -help"<<endl;
	}
	return;
}
