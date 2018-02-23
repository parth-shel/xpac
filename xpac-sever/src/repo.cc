#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

#include "repo.hh"

namespace repo {
	std::map<unsigned long long, std::string>symbol_table;

	// build symbol table from file
	extern int build_symbol_table(const char * file_name) {
		std::ifstream universe_file (file_name, std::ios::in);
		if(!universe_file.is_open()) { // file does not exist
			return -1;
		}
		std::string line;
		getline(universe_file, line); // skip the first row of .csv -- line for schema
		while(std::getline(universe_file, line)) {
			std::istringstream iss(line);
			std::string token;

			std::getline(iss, token, ',');
			unsigned long long PKGID = std::strtoull(token.c_str(), NULL, 0);

			std::getline(iss, token, ',');
			std::string package_name = token;
			
			std::getline(iss, token, ',');
			std::string package_version = token;

			std::getline(iss, token, ',');
			std::string executable_name = token;

			std::string repo_path;
			repo_path.append("./repo/");
			repo_path.append(package_name);
			repo_path.append("/");
			repo_path.append(package_version);
			repo_path.append("/");
			repo_path.append(executable_name);

			symbol_table[PKGID] = repo_path;
		}

		universe_file.close();

		return 0;
	}

	// TODO: parse request and resolve to a file to be flushed
	extern int parse_request(char * request, char * file_name) {
		// TODO: fix file fetching using repo symbol table, this is for debugging purposes only
		
		std::string request_str = std::string(request);
		std::istringstream iss(request);
		std::string token;
		std::getline(iss, token, '-');
		if(token.compare("GPKG") == 0) {
			std::getline(iss, token, '-');
			unsigned long long PKGID = std::strtoull(token.c_str(), NULL, 0);
			std::string repo_path = symbol_table[PKGID];
			std::cout<<repo_path<<std::endl;
			std::strcpy(file_name, repo_path.c_str());
			return 0;
		}
		
		std::strcpy(file_name, NULL);
		return -1;
	}
}
