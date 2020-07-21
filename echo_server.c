/*
 * id:   003
 * name: echo server code example.
 * time: 2020.07.21
 * author: turlee
 *
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 1024
void error_handing(char *message);

int main(int argc, char *argv[]){
	int serv_sock;
	int clnt_sock;
	int str_len, i;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	char message[BUF_SIZE];

	if(argc != 2){
		printf("Usage : %s <port>\n",argv[0]);
		exit(1);
	}

	//creat socket
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1){
		error_handling("socket() error.");
	}
	
	//config serv_addr (sockaddr_in)
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	//bind   serv_sock (socket) <--> serv_addr ( sockaddr_in)
	if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
		error_handling("bind() error.");
	}
	
	//listen
	if(listen(serv_sock, 5) == -1){
		error_handling("listen() error.");
	}

	clnt_addr_size = sizeof(clnt_addr);

	for(i = 0; i < 5; i++){

	//accept
		clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);//notice
       		if(clnt_sock == -1){
                	error_handling("accept() error.");
        	}else{
			printf("connected client %d \n", i+1);
		}
	//read
		while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0){		
	//write
			write(clnt_sock, message, sizeof(message));//notice
		}
		close(clnt_sock);
        }
	close(serv_sock);
	return 0;
}

void error_handling(char *message){
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
