#include<iostream>
#include<string.h>

void print_err(){
	printf("Unknown command; please type xpac -help for help\n");
}

int main(int argc, char ** argv){
	if(argc<2){
		print_err();
		exit(1);
	}

	if(!strcmp(argv[1],"-install")){
		//Put install code here
	}
	else if(!strcmp(argv[1],"-remove")){
		//Deletion code here
	}
	else if(!strcmp(argv[1],"-help")){
		//Put help code here
	}
	

	return 0;
}
