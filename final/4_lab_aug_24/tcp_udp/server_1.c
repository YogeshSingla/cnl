//server program for chat
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
void error(const char* msg){
	perror(msg);
	exit(1);
}
int main(int argc, char const *argv[]){
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[255];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	if(argc < 2){
		fprintf(stderr, "Port number not provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		error("Error opening the socket");
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Binding error\n");
	
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

	if(newsockfd < 0)
			error("Error on accept");

	while(1){
		bzero(buffer, 255);
		n = read(newsockfd, buffer, 255);
		if(n < 0)
			error("Error on reading");

		printf("Client: %s\n", buffer);
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);

		n = write(newsockfd, buffer, strlen(buffer));
		if(n < 0)
			error("Error in writing\n");

		int i = strncmp("Bye", buffer, 3);
		if(i == 0)
			break;
	}
	close(newsockfd);
	close(sockfd);
	return 0;
}