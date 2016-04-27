#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "server.h"
#include "error.h"

int start_server(int portno)
{
  int server_fd;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;
  server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd < 0) {
    error("ERROR opening socket");
  }
  bzero((char *) &serv_addr, sizeof(serv_addr));
  portno = 5000;
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(server_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    error("ERROR on binding");
  }
  printf("Listening on port: %d\n", portno);
  listen(server_fd, 5);
  clilen = sizeof(cli_addr);
  while (1) {
    int session_fd = accept(server_fd, (struct sockaddr *) &cli_addr, &clilen);
    if (session_fd < 0) error("ERROR on accept");
    pid_t pid = fork();
    if (pid == -1) {
      error("Could not create child process.");
    } else if (pid == 0) {
      // child process
      close(server_fd);
      while (1) {
        // handle client disconnect
        bzero(buffer, 256);
        n = read(session_fd, buffer, 255);
        if (n < 0) error("ERROR reading from socket");
        printf("%s\n", buffer);
      }
      printf("Connection closed\n");
    } else {
      // parent process
      close(session_fd);
    }
  }
  return 0;
}
