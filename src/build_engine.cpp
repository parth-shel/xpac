#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>

int build(std::string command) {
	int current_uid = getuid();
	if (seteuid(0)) {
		perror("setuid");
		return -1;
	}
	system(command.c_str());
	seteuid(current_uid);
	return 0;
}

/*int main(int argc, char * argv[]) {
	std::string command("/usr/bin/id");

	if( build(command) < 0 ) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}*/
