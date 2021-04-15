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
#include <gpio.h>

#define SERVER_CENTRAL_IP "192.168.0.52"
#define SERVER_CENTRAL_PORT 10112
#define SERVER_DISTRIBUTED_PORT 10012

void* server_handler() {
  struct sockaddr_in server, client;

	int serverid = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server, '0', sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(SERVER_DISTRIBUTED_PORT);

	bind(serverid, (struct sockaddr*) &server, sizeof(server));

	if (listen(serverid, 10) == -1) {
		printf("ERROR");
		exit(1);
	}

  while (1) {
	  unsigned int len = sizeof(client);
	  int clientid = accept(serverid, (struct sockaddr*) &client, &len);

    char buffer[16];
	  int size = recv(clientid, buffer, 16, 0);

    if (size < 0) {
      printf("ERROR");
      exit(1);
    }
    
    buffer[15] = '\0';
		
		int item;
		int status;
		sscanf(buffer, "%d %d", &item, &status);
		toggle(item, status);
		
		close(clientid);
  }

	close(serverid);
}

void server_send(char *message) {
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

  int size = strlen(message);
  if (send(socketid, message, size, 0) != size) {
		printf("Error: Send failed\n");
    exit(1);
  }

  close(socketid);
}
