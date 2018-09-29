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
	char msg[1024];

	int s = socket(AF_INET,SOCK_STREAM,0);
	if(s < 0){
		printf("Error in Socket\n");
		return EXIT_FAILURE;
	}

	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(atoi("1420"));
	sin.sin_addr.s_addr = INADDR_ANY;

	if((bind(s,(struct sockaddr*) &sin,sizeof(sin))) < 0){
		printf("Error in Bind\n");
		return EXIT_FAILURE;
	}

	if((listen(s,3)) < 0){
		printf("Error in Listen\n");
		return EXIT_FAILURE;
	}

	int length_accept = sizeof(sin);
	int accpt = accept(s,(struct sockaddr*) &sin,(socklen_t*)&length_accept);
	if(accpt < 0){
		printf("Error in Accept\n");
		return EXIT_FAILURE;
	}else{
		printf("[+] a client has been Connected\n\n");
		while(1){
			memset(msg,'\0',sizeof(msg));
			read(accpt,msg,sizeof(msg));
			printf("Client : %s",msg);
			memset(msg,'\0',sizeof(msg));
			printf("Server : ");
			fgets(msg,sizeof(msg) - 1,stdin);
			write(accpt,msg,strlen(msg));
		}
	}
	close(accpt);
	close(s);
	return 0;
}
