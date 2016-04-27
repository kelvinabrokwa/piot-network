#ifndef CLIENT_H
#define CLIENT_H

typedef struct {
  int id;
  char *descr;
  int connected;
} client_id;

int client(client_id *id);

#endif
