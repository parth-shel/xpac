#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int build(std::string command) {
	int current_uid = getuid();
	printf("My UID is: %d. My GID is: %d\n", current_uid, getgid());
	system("%s", command.c_str());
	if (seteuid(0)) {
		perror("setuid");
		return -1;
	}
	//I am now root!
	printf("My UID is: %d. My GID is: %d\n", getuid(), getgid());
	system("%s", command.c_str());
	//Time to drop back to regular user privileges
	seteuid(current_uid);
	printf("My UID is: %d. My GID is: %d\n", getuid(), getgid());
	system("%s", command.c_str());
	return 0;
}

int main(int argc, char * argv[]) {
	std::string command("/usr/bin/id");

	if( build(command) < 0 ) {
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
