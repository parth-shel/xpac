/* @author Amol Moses Jha
 *
 * Client for xpac
 */

#include<iostream>
#include<string.h>
#include<functional>
#include<string>

std::hash<std::string> str_hash;

static inline void print_err(int errflag){
	if(errflag == 1)	printf("Unknown command; please type xpac -help for help\n");
	if(errflag == 2)	printf("Wrong number of arguments; please type xpac -help for help\n");
}

extern int client_driver(char * request, char * ip);

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
		client_driver(command_to_server,strdup("localhost"));
	}
	else if(!strcmp(argv[1],"-remove")){
		//Deletion code here
	}
	else if(!strcmp(argv[1],"-help")){
		//Help code here
	}
	return 0;
}
