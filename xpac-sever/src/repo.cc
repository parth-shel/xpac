#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "repo.hh"

struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir;

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

			std::string repo_path = std::string(homedir) ;
			repo_path.append("/repo/");
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
		if(token.compare("GPKG") == 0) { // GET PACKAGE
			std::getline(iss, token, '-');
			unsigned long long PKGID = std::strtoull(token.c_str(), NULL, 0);
			if(symbol_table.count(PKGID)) {
				std::string repo_path = symbol_table[PKGID];
				std::strcpy(file_name, repo_path.c_str());
				return 0;
			}
		}

		else if(token.compare("GMDT") == 0) { // GET METADATA
			std::getline(iss, token, '-');
			unsigned long long PKGID = std::strtoull(token.c_str(), NULL, 0);
			if(symbol_table.count(PKGID)) {
				std::string repo_path = symbol_table[PKGID];
				while(repo_path.at(repo_path.length() - 1) != '/') {
					repo_path.erase(repo_path.length() - 1, 1);
				}
				repo_path.append(".metadata");
				std::strcpy(file_name, repo_path.c_str());
				return 0;
			}
		}

		else if(token.compare("CHKSM") == 0) { // GET MD5 HASH
			std::getline(iss, token, '-');
			unsigned long long PKGID = std::strtoull(token.c_str(), NULL, 0);
			if(symbol_table.count(PKGID)) {
				// TODO: calculate MD5 hash and send file path to saved hash	
				return -1;
			}
		}

		else if(token.compare("GUNI") == 0) {
			std::string universe_path("./universe_of_packages.csv");
			std::strcpy(file_name, universe_path.c_str());
			return 0;
		}

		//std::strcpy(file_name, NULL);
		return -1;
	}
}
