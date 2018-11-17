#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

void error(char const* msg){
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]){
	int sockfd, newsockfd, portno;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;
	char buffer[500];

	if(argc < 2){
		fprintf(stderr, "Port number not entered");
		exit(1);
	}
	portno = atoi(argv[1]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("Error connecting to socket");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Binding error");
	
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);
	if(newsockfd < 0)
		error("Error while coonection");

	FILE *fp;

	int ch = 0;
	fp = fopen("received.txt", "a");
	int words;

	read(newsockfd, &words, sizeof(int));

	 while(ch != words){
		read(newsockfd, buffer, 500);
		fprintf(fp, "%s ", buffer);
	 	ch++;
	 }

	printf("File received. Saved as received.txt\n");

	close(newsockfd);
	close(sockfd);
	return 0;
}	