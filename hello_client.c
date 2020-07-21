/*
 *id:     0010
 *name:   client code example
 *time:   2020.7.21
 *author: turlee
 *
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
void error_handling(char *message);

int main(int argc, char* argv[]){

	int clnt_sock;
	struct sockaddr_in serv_addr;
	char message[40];
	int str_len;

	if(argc != 3){
		printf("Usage : %s <ip> <port>\n", argv[0]);
		exit(1);
	}

	//creat socket
	clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(clnt_sock == -1){
		error_handling("socket() error.");
	}

	//config serv_addr (sockaddr_in)
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);//notice
	serv_addr.sin_port = htons(atoi(argv[2]));

	//connect
	if(connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
		error_handling("connect() error.");
	}

	//read
	str_len = read(clnt_sock, message, sizeof(message)-1);
	if(str_len == -1){
		error_handling("read() error.");
	}

	printf("message from server: %s \n", message);
	close(clnt_sock);
	return 0;
}

void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

