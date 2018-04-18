#include <map>
#include <fstream>
#include <string>

extern std::string xpac_dir;
std::string installed_file = xpac_dir + ".installed";

std::map<std::string, std::string> user_installed_list;

void calculate_users_packages(){
	std::ifstream file;
	file.open(installed_file);
	std::string next_installed;
	while (getline(file,next_installed)) {
		int index = next_installed.find(" ");
		std::string name = next_installed.substr(0,index);
		std::string version = next_installed.substr(index+1, std::string::npos);
		user_installed_list.insert(std::make_pair(name,version));
	}
	file.close();
}

void add_to_install_list(std::string name, std::string version) {
	std::fstream file;
	file.open(installed_file, std::ios::out | std::ios::app);

	// Simply appending to file
	file << name << " " << version <<"\n";

	file.close();
}

void rewrite_installed_packages(){
	std::fstream file;
	file.open(installed_file, std::ios::out | std::ios::trunc);

	for(auto itr = user_installed_list.begin(); itr!=user_installed_list.end(); itr++) {
		file << itr->first << " " << itr->second << "\n";
	}

	file.close();
}
