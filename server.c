#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>

#include "server.h"

int main() {
  int sockfd, newsockfd, port_no, clilen, n;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    error("ERROR opening socket");
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  port_no = 5000;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port_no);
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR binding");
  }
  listen(sockfd, 5);
  clilen = sizeof(cli_addr);
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);
  if (newsockfd < 0) {
    error("ERROR accepting");
  }
  bzero(buffer, 256);
  n = read(newsockfd, buffer, 255);
  if (n < 0) {
    error("ERROR reading from socket");
  }
  printf("%s", buffer);
}

void error(const char *msg) {
  perror(msg);
  exit(1);
}
