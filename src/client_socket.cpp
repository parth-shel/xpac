/**
 *	client_socket.cpp
 *	
 * @author: parth_shel; amol_moses_jha
 * @version: v:0.1 Feb 11, 2018
**/

#include <stdio.h> // printf and standard I/O 
#include <sys/socket.h> // socket, connect, socklen_t
#include <arpa/inet.h> // sockaddr_in, inet_pton
#include <netdb.h> //hostent
#include <string.h> // strlen, strcpy
#include <stdlib.h> // atoi, EXIT_FAILURE, EXIT_SUCCESS
#include <fcntl.h> // open, O_WRONLY, O_CREAT
#include <unistd.h> // close, write, read

#define SRV_PORT 6969
#define MAX_RECV_BUF 256
#define MAX_SEND_BUF 256

int recv_file(int ,char*);
int hostname_to_ip(char*, char*);
int client_driver(char * request, char * ip);

const char * errmsg_notfound = "file not found\n";

int client_driver(char * command, char * ip) {
 	int sock_fd;
 	struct sockaddr_in srv_addr;
 	
	memset(&srv_addr, 0, sizeof(srv_addr));

 	// create a client socket
 	sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
 	srv_addr.sin_family = AF_INET; // internet address

	// DNS lookup
	char * IP = (char *) malloc(128 * sizeof(char));
	if( hostname_to_ip(ip, IP) < 0 ) {
		printf("DNS lookup failure\n");
		exit(EXIT_FAILURE);
	}

 	// convert command line argument to numeric IP
 	if ( inet_pton(AF_INET, IP, &(srv_addr.sin_addr)) < 1 ) {
 		printf("invalid IP address\n");
		exit(EXIT_FAILURE);
 	}

 	// use specified port number or default otherwise
	// TODO: WORK ON PORT SELECTION
 	srv_addr.sin_port = htons(SRV_PORT);

 	if( connect(sock_fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0 ) {
 		perror("connect error");
 		exit(EXIT_FAILURE);
 	}
 	else {
 		printf("connected to:%s:%d ..\n",ip,SRV_PORT);
 	}
 
	if( recv_file(sock_fd, command) < 0 ) { // command
		//perror("receive error\n");
		//exit(EXIT_FAILURE);
		return -1;
	}
 	
	// close socket
 	if(close(sock_fd) < 0) {
 		perror("socket close error");
 		exit(EXIT_FAILURE);
 	}
 
	return EXIT_SUCCESS;
}

int hostname_to_ip(char * hostname, char * ip) {
	struct hostent *ptrh;
    	struct in_addr **addr_list;
         
    	// get host info
	if ( (ptrh = gethostbyname( hostname ) ) == NULL) {
       	 	perror("gethostbyname error\n");
        	return -1;
    	}
 
    	addr_list = (struct in_addr **) ptrh->h_addr_list;
     
    	for(int i = 0; addr_list[i] != NULL; i++) {
        	strcpy(ip , inet_ntoa(*addr_list[i]) );
        	return 0;
    	}
     
    	return -1;
}

int recv_file(int sock, char* file_name) {
 	char send_str [MAX_SEND_BUF]; // message to be sent to server
 	int fd; // file descriptor for receiving file
 	ssize_t sent_bytes, rcvd_bytes, rcvd_file_size;
 	int recv_count; // count of recv() calls
 	char recv_str[MAX_RECV_BUF]; // buffer to hold received data 
 	size_t send_strlen; // length of transmitted string

 	sprintf(send_str, "%s\n", file_name); 
 	send_strlen = strlen(send_str); /* length of message to be transmitted */
 	if( (sent_bytes = send(sock, send_str, send_strlen, 0)) < 0 ) {
 		perror("send error");
 		return -1;
 	}
 
 	// create file to save received data.
 	if ( (fd = open(file_name, O_WRONLY|O_CREAT, 0755)) < 0 ) {
 		perror("error creating file");
 		return -1;
 	}

 	recv_count = 0; // number of recv() calls required to receive the file
 	rcvd_file_size = 0; // size of received file

 	// continue receiving file
 	while ( (rcvd_bytes = recv(sock, recv_str, MAX_RECV_BUF, 0)) > 0 ) {
 		recv_count++;
 		rcvd_file_size += rcvd_bytes;

		if(!strcmp(recv_str,errmsg_notfound)){
			printf("File not found on xpac repo!\nPlease check file name and try again!");
			return -1;
		}
 		if (write(fd, recv_str, rcvd_bytes) < 0 ) {
 			perror("error writing to file");
 			return -1;
 		}
 	}
 	
	close(fd); // close file
 	printf("Client Received: %zu bytes in %d recv(s)\n", rcvd_file_size, recv_count);
 	return rcvd_file_size;
}
