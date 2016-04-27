#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "client.h"
#include "error.h"

int client() {
  int sockfd, portno, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  portno = 5000;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }
  server = gethostbyname("localhost");
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host\n");
    exit(0);
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR connecting");
  }
  return sockfd;
}

int client_write(int sockfd, char *msg, int nbytes) {
  nbytes++;
  char buffer[nbytes];
  bzero(buffer, nbytes);
  strcpy(buffer, msg);
  return write(sockfd, buffer, nbytes);
}
