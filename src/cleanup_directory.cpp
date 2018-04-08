#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstring>
#include <string>
#include <iostream>

void cleanup_directory(std::string dir_name){
	int ret = fork();
	if(ret == 0) {
		std::cout<<"HERE TRYNA TO DELETE THIS SHIT!"<<dir_name.c_str();
		char * const * dir_c_str = (char * const *)strdup(dir_name.c_str());
		execvp("rm -rf", dir_c_str);
		exit(1);
	} else {
		waitpid(ret, 0, NULL);
	}
}
