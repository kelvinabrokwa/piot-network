#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>

#include "client.h"

int main() {
  int sockfd, r;
  sockfd = client();
  client_write(sockfd, "hello", 5);
  return 0;
}
