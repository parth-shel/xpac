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

#include "metadata.h"

//Global variables and extern functions:
std::hash<std::string> str_hash;

extern void man_help();
extern int client_driver(char * request, char * ip);

std::string metadata_path;
std::string install_path;

static inline void get_from_server(char * command_to_server, char * pkg_name){

	std::string command = std::string(command_to_server);
	std::string pkg_hash = std::to_string(str_hash(std::string(pkg_name))).c_str();
	command.append(pkg_hash);
	char * final_command_to_server = (char*)command.c_str();
	client_driver(final_command_to_server,strdup("repo.xpac.tech"));
	
	//To untar the recieved file:
	std::string untar_str = std::string("tar -xvf ") + std::string(final_command_to_server);
	system(untar_str.c_str());
	remove(final_command_to_server);

	//Setting metadata and install_paths
	metadata_path = std::string(pkg_name) + std::string("/.metadata");
	install_path = std::string(pkg_name) + std::string("/.install_script");
}

static inline void print_err(int errflag){
	if(errflag == 1)	printf("Unknown command; please type xpac -help for help\n");
	if(errflag == 2)	printf("Wrong number of arguments; please type xpac -help for help\n");
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

		//Getting the metadata for the package:
		//get_from_server("GMDT-",argv[2]);

		//Getting the binary itself
		get_from_server("GPKG-",argv[2]);

		//Building the package here:
		metadata * package = metadata::get_package(metadata_path.c_str());
		std::vector<std::string> * dep_list = package->get_dep_list();

		for(auto itr=dep_list->begin(); itr!=dep_list->end(); itr++){
			//TODO: DEPENDECY LIST HERE:
		}

		//Installing the main package here itself:
		system(install_path.c_str());

		//TODO: MOVE TO XPAC's FOLDERS:
	}
	else if(!strcmp(argv[1],"-help")){
		man_help();
	}
	return 0;
}
