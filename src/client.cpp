/* @author Amol Moses Jha
 *
 * Client for xpac
 */

#include<iostream>
#include<string.h>
#include<functional>
#include<sys/stat.h>
#include<sys/types.h>
#include<string>
#include<cstdlib>
#include<stack>
#include<queue>
#include<unordered_set>

#include "metadata.h"

//Global variables and extern functions:
std::hash<std::string> str_hash;

extern void man_help();
extern int client_driver(char * request, char * ip);

std::string metadata_path;
std::string install_path;

std::stack<std::string> dep_list;
std::queue<std::string> bfs_queue;
std::unordered_set<std::string> marked;

static inline void get_from_server(const char * command_to_server,const char * pkg_name){

	std::string command = std::string(command_to_server);
	std::string pkg_hash = std::to_string(str_hash(std::string(pkg_name))).c_str();
	command.append(pkg_hash);
	char * final_command_to_server = (char*)command.c_str();
	client_driver(final_command_to_server,strdup("repo.xpac.tech"));
	
	//To untar the recieved file:
	std::string untar_str = std::string("tar -xvf ") + std::string(final_command_to_server);
	//system(untar_str.c_str());
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
		//TODO: Substitute parth's build engine here:
		std::string to_install = dep_list.top();
		dep_list.pop();
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
	if(!strcmp(argv[1],"-install")){
		if(argc<3){
			print_err(2);
			exit(1);
		}

		char * pkg_name = strdup(argv[2]);

		//Installing the package:
		install_package(pkg_name);
	}
	else if(!strcmp(argv[1],"-help")){
		man_help();
	}
	return 0;
}
