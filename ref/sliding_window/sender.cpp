#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#define SIZE 4
int main()
{
        int sfd,lfd,i,j,status;
        char str[20],frame[20],temp[20],ack[20];
	socklen_t len;
        struct sockaddr_in saddr,caddr;
        sfd=socket(AF_INET,SOCK_STREAM,0);
        if(sfd<0)
                perror("Error");
                bzero(&saddr,sizeof(saddr));
                saddr.sin_family=AF_INET;
                saddr.sin_addr.s_addr=htonl(INADDR_ANY);
                saddr.sin_port=htons(5465);
                if(bind(sfd,(struct sockaddr*)&saddr,sizeof(saddr))<0)
                        perror("Bind Error");
                listen(sfd,5);
                len=sizeof(&caddr);
                lfd=accept(sfd,(struct sockaddr*)&caddr,&len);
                printf("Enter the text : \n");
                scanf("%s",str);
                i=0;
                while(i<strlen(str))
                {
                        memset(frame,0,20);
                        strncpy(frame,str+i,SIZE);
                        printf("Transmitting Frames...");
                        len=strlen(frame);
			printf(" ");
			strcat(frame," ");
			for(j=0;j<len;j++)
                        {
                                printf("%d ",i+j);
                                sprintf(temp,"%d ",i+j);
                                strcat(frame,temp);
                        }
			strcat(frame,"\0");
			printf("\n");
                        write(lfd,frame,sizeof(frame));
                        read(lfd,ack,20);
                        sscanf(ack,"%d",&status);

                        if(status==-1)
                                printf("Transmission is successful.\n");
                        else
                        {
                                printf("Received error in %d \n",status);
                                printf("Retransmitting Frame.\n");
                                for(j=0;;)
                                {
                                        frame[j]=str[j+status];
                                        printf("%d ",j+status);
                                        j++;
                                    if((j+status)%SIZE==0)
                                                break;
                                }
                                printf("\n");
                                frame[j]='\0';
                                len=strlen(frame);
                                for(j=0;j<len;j++)
                                {
                                        sprintf(temp,"%d",j+status);
                                        strcat(frame,temp);
                                }
                                write(lfd,frame,sizeof(frame));
                        }
                        i+=SIZE;
                }
                write(lfd,"exit",sizeof("exit"));
                printf("Successfully Transmitted Text...Exiting...\n");
                sleep(2);
                close(lfd);
                close(sfd);
}

