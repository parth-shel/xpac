/* @author Amol Moses Jha
 *
 * Client for xpac
 */

#include<iostream>
#include<string.h>
#include<functional>
#include<string>

//Global variables and extern functions:
std::hash<std::string> str_hash;
extern void man_help();
extern int client_driver(char * request, char * ip);

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
		std::string command = std::string("GPKG-"); 
		std::string pkg_hash = std::to_string(str_hash(std::string(argv[2]))).c_str();
		command.append(pkg_hash);
		char * command_to_server = (char*)command.c_str();
		int bytes_recvd = client_driver(command_to_server,strdup("localhost"));
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
		}
	}
	else if(!strcmp(argv[1],"-help")){
		man_help();
	}
	return 0;
}
