/* @author Amol Moses Jha
 *
 * Client for xpac
 */

#include <iostream>
#include <string.h>
#include <functional>
#include <sys/stat.h>
#include <sys/types.h>
#include <string>
#include <cstdlib>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>

#include "metadata.h"

//Initializing the home directory, and the users xpac directory:
struct passwd *pw = getpwuid(getuid());
const char *homedir = pw->pw_dir;
std::string xpac_dir = std::string(homedir) +std::string("/.xpac/");
std::string universe_file = xpac_dir + std::string("universe_of_packages.csv");

//Global variables and extern functions:
std::hash<std::string> str_hash;

extern int build(std:: string command);
extern void man_help();
extern int client_driver(char * request, char * ip);
extern void parse_universe_of_packages(std::string, int);
extern void print_package_set();
extern std::set<std::string> universe_list;
extern void print_package_set();
extern void add_to_install_list(std::string str);
extern void calculate_users_packages();
extern std::unordered_set<std::string> user_installed_list;
extern void cleanup_directory(std::string);

std::string metadata_path;
std::string install_path;

std::stack<std::string> dep_list;
std::queue<std::string> bfs_queue;
std::unordered_set<std::string> marked;

static inline void xpac_dir_handler(){
	DIR* dir = opendir(xpac_dir.c_str());
	if (dir)
	{
		closedir(dir);  //Directory exists and we don't need to so anything
	}
	else if (ENOENT == errno)
	{
		/* Directory does not exist. So we need to create it */
		mkdir(xpac_dir.c_str(),0775);
	}
}

static inline void update_from_server(){
	client_driver(strdup("GUNI"),strdup("repo.xpac.tech"));
	rename("GUNI",universe_file.c_str());
}

static inline void untar_file(std::string filename) {
	std::string untar_str = std::string("tar -xvf ") + std::string(filename);
	system(untar_str.c_str());
}

static inline void get_from_server(const char * command_to_server,const char * pkg_name){

	std::string command = std::string(command_to_server);
	std::string pkg_hash = std::to_string(str_hash(std::string(pkg_name))).c_str();
	command.append(pkg_hash);
	char * final_command_to_server = (char*)command.c_str();
	client_driver(final_command_to_server,strdup("repo.xpac.tech"));
	
	//To untar the recieved file:
	untar_file(final_command_to_server);

	//Removing the downloaded file from server:
	remove(final_command_to_server);

	//Setting metadata and install_paths
	metadata_path = std::string(pkg_name) + std::string("/.metadata");
	install_path = std::string(pkg_name) + std::string("/.install_script");
}

static inline void print_err(int errflag){
	if(errflag == 1)	printf("Unknown command; please type xpac -help for help\n");
	if(errflag == 2)	printf("Wrong number of arguments; please type xpac -help for help\n");
}

static void install_all_packages(){

	while(!dep_list.empty()){
		std::string to_install = dep_list.top();
		std::string to_display = to_install.substr(0,to_install.find("/"));
		cleanup_directory(to_display);
		dep_list.pop();
		std::cout<<"Installing package: "<<to_display<<std::endl;
		if(user_installed_list.find(to_display) != user_installed_list.end()) {
			std::cout<<"Already installed "<<to_display<<"!"<<std::endl;
			if(dep_list.empty())	exit(1);
		} else {
			int rem = system(to_install.c_str());
			if(rem != 0){
				std::cout<<"Unable to install "<<to_display<<"!!"<<std::endl;
				std::cout<<"Please rectify the errors and try again!"<<std::endl;
				//Emptying the stack:
				while(!dep_list.empty()) {
					std::string to_install = dep_list.top();
					cleanup_directory(to_display);
					dep_list.pop();
				}
				exit(1);
			} else {
				add_to_install_list(to_display); //Adding to the list of successfully installed packages
			}
		}
	}
}

static void install_package(const char * pkg_name){
	//Getting the package from the server itself:
	get_from_server("GPKG-",pkg_name);

	//Working on the dependencies:
	metadata * package = metadata::get_package(metadata_path.c_str());

	//Pushing the install path onto the stack:
	dep_list.push(install_path);

	//Initializing the bfs queue:
	marked.insert(std::string(pkg_name));
	bfs_queue.push(std::string(pkg_name));
	
	while(!bfs_queue.empty()){

		std::string next = bfs_queue.front();
		bfs_queue.pop();


		if(next.compare(std::string(pkg_name)) != 0){
			get_from_server("GPKG-",next.c_str());
			package = metadata::get_package(metadata_path.c_str());
			dep_list.push(install_path);
		}

		std::vector<std::string> * curr_dep_list = package->get_dep_list();

		for(auto itr = curr_dep_list->begin(); itr!=curr_dep_list->end(); itr++){
			auto found = marked.find(*itr);
			if(found == marked.end()){	//Not found
				marked.insert(*itr);
				bfs_queue.push(*itr);
			}
		}

	}

	//Finally installing everything in the stack:
	install_all_packages();
}

int main(int argc, char ** argv){
	if(argc<2){
		print_err(1);
		exit(1);
	}

	//Initializing:
	xpac_dir_handler();
	int flag = (!strcmp(argv[1],"-update"))?1:0;
	parse_universe_of_packages(universe_file,flag);
	calculate_users_packages();

	if(!strcmp(argv[1],"-install")){
		if(argc<3){
			print_err(2);
			exit(1);
		}

		char * pkg_name = strdup(argv[2]);

		auto find_itr = universe_list.find(std::string(pkg_name));
		if(find_itr == universe_list.end()){	//Package not available to install in the repo!
			std::cout<<"Sorry, package not available in the repository! Please check the website for more information!"<<std::endl;
			exit(0);
		}
		//Installing the package:
		install_package(pkg_name);
	}
	else if(!strcmp(argv[1],"-update")){
		std::cout<<"Updating xpac"<<std::endl;
		update_from_server();	
	}
	else if(!strcmp(argv[1],"-list")){
		std::cout<<"Listing all packages available for installation: "<<std::endl;
		print_package_set();	
	}
	else if(!strcmp(argv[1],"-help")){
		man_help();
	}
	return 0;
}
