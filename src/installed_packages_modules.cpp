#include <unordered_set>
#include <fstream>
#include <string>

extern char * homedir;

std::unordered_set<std::string> user_installed_list;

void calculate_users_packages(){
	std::ifstream file;
	file.open(std::string(homedir) + ".xpac/.installed");
	std::string next_installed;
	while (file >> next_installed) {
		user_installed_list.insert(next_installed);
	}
	
	file.close();
}

void add_to_install_list(std::string str) {
	std::fstream file;
	file.open(std::string(homedir) + ".xpac/.installed", std::fstream::out | std::ios::app);

	// Simply appending to file
	file << str;

	file.close();
}
