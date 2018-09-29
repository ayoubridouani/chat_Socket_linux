#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char** argv){
	char msg[100];

	int s = socket(AF_INET,SOCK_STREAM,0);
	if(s < 0){
		printf("Error in Socket\n");
		return EXIT_FAILURE;
	}

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(1420);
	struct hostent *hptr;

	hptr = gethostbyname("127.0.0.1");
	memcpy(&sin.sin_addr , hptr->h_addr, hptr->h_length);

	int c = connect(s,(struct sockaddr*) &sin,sizeof(sin));
	if(c < 0){
		printf("Error in Connect\n");
		return EXIT_FAILURE;
	}else{
			puts("[+] Connected to Server Enter your msg ...\n");
		while(1){
			printf("Client : ");
			fgets(msg,sizeof(msg) - 1,stdin);
			write(s,msg,strlen(msg));
			memset(msg,'\0',sizeof(msg));
			read(s,msg,sizeof(msg));
			printf("Server : %s",msg);
		}
	}
	close(s);

	return 0;
}

