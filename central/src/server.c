#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#define SERVER_CENTRAL_IP "192.168.0.53"
#define SERVER_CENTRAL_PORT 10012

void* recv_message() {
  return NULL;
}

void send_message(int item, int status) {
  struct sockaddr_in client;

  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1) {
    printf("Could not create a socket!\n");
    exit(1);
  }

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(SERVER_CENTRAL_IP);
  client.sin_port = htons(SERVER_CENTRAL_PORT);

  if (connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0) {
    printf("Error: Connection failed\n");
    exit(1);
  }

  char buf[4];
  snprintf(buf, 4, "%d %d", item, status);
  int size = strlen(buf);
  if (send(socketid, buf, size, 0) != size) {
		printf("Error: Send failed\n");
    exit(1);
  }

  close(socketid);
}
