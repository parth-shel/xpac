#include <cstring>
#include <string>
#include <map>

#include "repo.hh"

namespace repo {
	std::map<unsigned long, std::string>symbol_table;

	// TODO: build symbol table from file
	extern int build_symbol_table(const char * file_name) {
		return 0;
	}

	// TODO: parse request and resolve to a file to be flushed
	extern int parse_request(char * request, char * file_name) {
		// TODO: fix file fetching using repo symbol table, this is for debugging purposes only
		char * temp = (char *) malloc(128 * sizeof(char));
		std::strcpy(temp, "./repo/utkycow/v:1.0/");
		std::strcat(temp, request);
		std::strcpy(file_name, temp);
		free(temp);

		return 0;
	}
}
