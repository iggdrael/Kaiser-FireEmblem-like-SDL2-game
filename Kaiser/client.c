#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<strings.h>
#include <sys/time.h>
#include <string.h>
#define SERVEURNAME "127.0.0.1" // adresse IP de mon serveur


#define QUITTER "QUITTER"

int main(int argc, char **argv) {
    char buffer[512];
    fd_set rdfs;

  struct sockaddr_in servaddr;
  int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (sock == -1) perror("Socket");

  bzero((void *) &servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(30000);
  servaddr.sin_addr.s_addr = inet_addr(SERVEURNAME);

  if (-1 == connect(sock, (struct sockaddr *)&servaddr, sizeof(servaddr)))
    perror("Connect");


    memset(buffer, 0, sizeof(buffer));
	recv(sock,buffer,512,0);
	printf("[client] Server name is : '%s'\n", buffer);
  while(1) {
      FD_ZERO(&rdfs);
      FD_SET(STDIN_FILENO, &rdfs);
      FD_SET(sock, &rdfs);

    if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

    if(FD_ISSET(STDIN_FILENO, &rdfs)){
    	char message[6];
    	fgets(message, 6, stdin);
    	message[5] = '\0';
    	send(sock, message, 6, 0);
    }
    else if(FD_ISSET(sock, &rdfs)){
		memset(buffer, 0, sizeof(buffer));
		recv(sock,buffer,512,0);
		printf("[client] response from server : '%s'\n", buffer);
    }
  }
  close(sock);
}

