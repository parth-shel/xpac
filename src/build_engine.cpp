#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>

int build(std::string command) {
	int index = command.find('/');
	std::string to_chdir = command.substr(0,index+1);
	char * curr_dir = get_current_dir_name();
	chdir(to_chdir.c_str());
	int current_uid = getuid();
	if (setuid(0)) {
		perror("setuid");
		return -1;
	}
	std::string to_execute = std::string(get_current_dir_name()) + std::string("/.install_script");
	system(to_execute.c_str());
	setuid(current_uid);
	chdir(curr_dir);
	return 0;
}
