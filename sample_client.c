#include <stdlib.h>
#include "client.h"

int main() {
  client_id *id = NULL;
  id->id = 1;
  id->descr = "sample device";
  id->connected = 0;
}
