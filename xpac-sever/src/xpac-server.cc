/** 
 *	xpac-server
 * 
 * @author: parth_shel
 * @version: v:0.1 Feb 11, 2018
**/

#include <stdio.h> // printf and standard i/o 
#include <sys/socket.h> // socket, bind, listen, accept, socklen_t
#include <arpa/inet.h> // sockaddr_in, inet_ntop
#include <string.h> // strlen
#include <stdlib.h> // atoi, EXIT_FAILURE, EXIT_SUCCESS
#include <fcntl.h> // open, O_RDONLY
#include <unistd.h> // close, read
#include <signal.h> // signal
#include <sys/wait.h> // waitpid 

#include "repo.hh" // parse_request, symbol table
#include "server-log.hh" // initialize-log, log-event

#define SRV_PORT 3702 // default port number
#define LISTEN_ENQ 5 // for listen backlog
#define MAX_RECV_BUF 256
#define MAX_SEND_BUF 256

int get_request(int, char*);
int send_file(int , char*);
void sig_chld(int);

void init() {
	if( repo::build_symbol_table("universe_of_packages.csv") < 0 ) {
		perror("repo failure");
		exit(EXIT_FAILURE);
	}
	if( log::initialize_log("server.log") < 0 ) {
		perror("log failure");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
 	init();

	int listen_fd, conn_fd;
 	struct sockaddr_in srv_addr, cli_addr;
 	socklen_t cli_len;
 	pid_t child_pid; // pid of child process 
 	char file_name [MAX_RECV_BUF]; // name of the file to be sent
 	char print_addr [INET_ADDRSTRLEN]; // readable IP address
 	
	memset(&srv_addr, 0, sizeof(srv_addr));
 	memset(&cli_addr, 0, sizeof(cli_addr));
 	
	srv_addr.sin_family = AF_INET;
 	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
 
	// user specified port or default otherwise
 	srv_addr.sin_port = (argc > 1) ? htons(atoi(argv[1])) : htons(SRV_PORT);
 	if ( (listen_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
 		perror("socket error");
 		exit(EXIT_FAILURE);
 	}
 	
	// bind to created socket
 	if( bind(listen_fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0 ){
 		perror("bind error");
 		exit(EXIT_FAILURE);
 	}

 	printf("listening on port number %d ...\n", ntohs(srv_addr.sin_port));
 	
	if( listen(listen_fd, LISTEN_ENQ) < 0 ) {
 		perror("listen error");
 		exit(EXIT_FAILURE);
 	}
 
	// install signal handler
 	signal (SIGCHLD, sig_chld);

 	while (true) { // run forever
 		cli_len = sizeof(cli_addr);
 		printf ("waiting for a client to connect...\n\n");
 		
		// block until some client connects
 		if ( (conn_fd = accept(listen_fd, (struct sockaddr*) &cli_addr, &cli_len)) < 0 ) {
 			perror("accept error\n");
 			//break; // exit from the server loop
 		}

 		// convert numeric IP to readable format for displaying
 		inet_ntop(AF_INET, &(cli_addr.sin_addr), print_addr, INET_ADDRSTRLEN);
 		printf("client connected from %s:%d\n", print_addr, ntohs(cli_addr.sin_port) );
 		
		// fork a new child process
 		if ( (child_pid = fork()) == 0 ) { // fork returns 0 for child
 			close (listen_fd); // close child's copy of listen_fd
 			
			// get request from client and resolve into a file name to send
			if( get_request(conn_fd, file_name) < 0 ) {
				perror("request error\n");
			}
			else {
 				// flush the request file
				if( send_file(conn_fd, file_name) < 0 ) {
					perror("transmission error\n");
				}
			}
 			
			printf("closing connection\n");
 			close(conn_fd); // close connected socket
 			
			exit(EXIT_SUCCESS); // exit child process
 		}
 		close(conn_fd); // close parent's copy of conn_fd
 	} // end server loop

 	close(listen_fd); // close listening socket
 	
	return EXIT_SUCCESS;
}

int get_request(int sock, char* file_name) {
 	char recv_str[MAX_RECV_BUF]; // received string 
 	char request_str[MAX_RECV_BUF]; // request to parse
	ssize_t rcvd_bytes; // bytes received from socket

 	// read request from socket
 	if ( (rcvd_bytes = recv(sock, recv_str, MAX_RECV_BUF, 0)) < 0) {
 		perror("recv error\n");
 		return -1;
 	}

 	sscanf (recv_str, "%s\n", request_str);
	
	// parse request and resolve into a file to be flushed
	if ( repo::parse_request(request_str, file_name) < 0 ) {
		perror("parse error\n");
		return -1;
	}

	return 0;
}

int send_file(int sock, char *file_name) {
 	int sent_count; // num of sent chunks
 	ssize_t read_bytes, // bytes read from local file
 	sent_bytes, // bytes sent to connected socket
 	sent_file_size;
 	
	char send_buf[MAX_SEND_BUF]; // max chunk size for sending file
 	
 	
	int fd; // file descriptor for reading local file
 	
	sent_count = 0;
 	sent_file_size = 0;
 	
	// attempt to open requested file for reading
 	if( (fd = open(file_name, O_RDONLY)) < 0) { // can't open requested file
		const char * errmsg_notfound = "file not found\n";
		perror(file_name);
 		if( (sent_bytes = send(sock, errmsg_notfound ,strlen(errmsg_notfound), 0)) < 0 ) {
 			perror("send error\n");
 			return -1;
 		}
 	}
 	else { // open file successful
 		printf("sending file: %s\n", file_name);
 		while( (read_bytes = read(fd, send_buf, MAX_RECV_BUF)) > 0 ) {
			if( (sent_bytes = send(sock, send_buf, read_bytes, 0)) < read_bytes ) {
 				perror("send error\n");
 				return -1;
 			}
 		
			sent_count++;
 			sent_file_size += sent_bytes;
 		}
 		close(fd);
 	}

 	printf("flushed %zu bytes in %d send(s)\n\n", sent_file_size, sent_count);
	return sent_count;
}

// signal hanlder
void sig_chld(int signo) {
 	pid_t pid;
 	int stat;
 	
	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
 		printf("child %d terminated\n", pid);
 	
 	return;
}
