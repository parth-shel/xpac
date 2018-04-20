#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstring>
#include <string>
#include <iostream>

void cleanup_directory(std::string dir_name){
	dir_name = get_current_dir_name() + std::string("/") + dir_name;
	int ret = fork();
	if(ret == 0) {
		execl("/bin/rm", "rm", "-rf", dir_name.c_str(), NULL);
		exit(1);
	} else {
		waitpid( ret, NULL, 0);
	}
}
