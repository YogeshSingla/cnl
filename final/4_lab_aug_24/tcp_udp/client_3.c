#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <ctype.h>

void error(char const* msg){
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]){
	int sockfd, portno;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[500];

	if(argc < 3){
		fprintf(stderr, "host or port not entered\n" );
		exit(1);
	}

	portno = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("Unable to connect socket");

	server = gethostbyname(argv[1]);
	if(server==NULL)
		error("no such host");

	serv_addr.sin_family = AF_INET;
	bcopy((char*)server->h_addr, (char*) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portno);

	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Connection error\n");
		
	FILE *f;
	int words=0;
	char c;

	bzero(buffer, 500);

	f = fopen("share.txt", "r");
	while((c = getc(f)) != EOF){
		fscanf(f, "%s", buffer);
		// if(isspace(c) || c=='\t')
			words++;
	}

	write(sockfd, &words, sizeof(int));
	rewind(f);

	char ch;
	while(ch != EOF){
		fscanf(f, "%s", buffer);
		write(sockfd, buffer, 500);
		ch = fgetc(f);
	}
	printf("File sent successfully\n");
	close(sockfd);
	return 0;
}