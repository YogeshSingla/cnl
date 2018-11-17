#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<string.h>
#include<time.h>

void error(const char* msg){
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[]){
	int sockfd, newsockfd, portno;
	socklen_t clilen;
	char buffer[255];
	time_t ticks;
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

	ticks = time(NULL);
    snprintf(buffer, sizeof(buffer), "%.24s\r\n", ctime(&ticks));
	write(newsockfd, buffer, strlen(buffer));
	
	close(newsockfd);
	close(sockfd);
	return 0;
}