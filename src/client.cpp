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

#include "metadata.h"

//Global variables and extern functions:
std::hash<std::string> str_hash;

int file_per_bit = 0;				//0 for read/write file; 1 for executable

extern void man_help();
extern int client_driver(char * request, char * ip);

static inline void move_to_folder(char * command_to_server, char * pkg_name , char * append){
	std::string final_path = std::string(pkg_name) + std::string("/") + std::string(append);
	rename(command_to_server,final_path.c_str());
}

static inline void get_from_server(char * command_to_server, char * pkg_name){
	std::string command = std::string(command_to_server);
	file_per_bit = 0;
	std::string pkg_hash = std::to_string(str_hash(std::string(pkg_name))).c_str();
	command.append(pkg_hash);
	char * final_command_to_server = (char*)command.c_str();
	int bytes_recvd = client_driver(final_command_to_server,strdup("localhost"));
	/*
	if(bytes_recvd != 0){
		if(!strcmp(command_to_server,"GMDT-"))	move_to_folder(final_command_to_server,pkg_name, ".metadata");
		else if(!strcmp(command_to_server,"GPKG-"))	move_to_folder(final_command_to_server,pkg_name, pkg_name);
	}
	remove(final_command_to_server);*/
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

		//Creating a directory with the needed files:
		mkdir(argv[2], 0755);

		//Getting the metadata for the package:
		get_from_server("GMDT-",argv[2]);

		//Getting the binary itself
		file_per_bit = 1;
		get_from_server("GPKG-",argv[2]);
		
		/*
		if(bytes_recvd != -1){
			std::string final_path = std::string("/usr/local/bin/") + std::string(argv[2]); 
			int mv_res = rename(command_to_server,final_path.c_str());
			if(mv_res != 0){
				remove(command_to_server);
				perror("Error moving file!");
				exit(1);
			}
			printf("Successfully installed %s!\n",argv[2]);
		}
		else{
			remove(command_to_server);
			exit(1);
		}*/
	}
	else if(!strcmp(argv[1],"-help")){
		man_help();
	}
	return 0;
}
