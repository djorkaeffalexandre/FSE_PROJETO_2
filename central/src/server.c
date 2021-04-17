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
#include <quit.h>
#include <alarm.h>
#include "server.h"

#define SERVER_DISTRIBUTED_IP "192.168.0.52"
#define SERVER_DISTRIBUTED_PORT 10112
#define SERVER_CENTRAL_PORT 10012

void* recv_message() {
  struct sockaddr_in server, client;

	int serverid = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server, '0', sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(SERVER_CENTRAL_PORT);

	bind(serverid, (struct sockaddr*) &server, sizeof(server));

	if (listen(serverid, 10) == -1) {
    char *message = "ERROR: Listening messages..";
		quit_handler(message);
	}

  while (1) {
	  unsigned int len = sizeof(client);
	  int clientid = accept(serverid, (struct sockaddr*) &client, &len);

    char buffer[16];
	  int size = recv(clientid, buffer, 16, 0);

    if (size < 0) {
      char *message = "ERROR: Message received with len less than expected..";
      quit_handler(message);
    }
    
    buffer[15] = '\0';

		int command;
		sscanf(buffer, "%d", &command);
    if (command == 1) {
      alarm_handler();
    }
		
		close(clientid);
  }

	close(serverid);
}

int send_command(int item, int status) {
  struct sockaddr_in client;

  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1) {
    char *message = "ERROR: Você deve inicializar o sistema distribuído!";
    quit_handler(message);
  }

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(SERVER_DISTRIBUTED_IP);
  client.sin_port = htons(SERVER_DISTRIBUTED_PORT);

  if (connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0) {
    char *message = "ERROR: Você deve inicializar o sistema distribuído!";
    quit_handler(message);
  }

  char buf[6];
  snprintf(buf, 6, "%d %d %d", 1, item, status);
  int size = strlen(buf);
  if (send(socketid, buf, size, 0) != size) {
		char *message = "ERROR: Você deve inicializar o sistema distribuído!";
    quit_handler(message);
  }

  char buffer[16];
  int size_rec = recv(socketid, buffer, 16, 0);
  if (size_rec < 0) {
    char *message = "ERROR: Você deve inicializar o sistema distribuído!";
    quit_handler(message);
  }

  buffer[15] = '\0';

  int res;
  sscanf(buffer, "%d", &res);

  close(socketid);

  return res;
}

Bme280 request_sensor() {
  struct sockaddr_in client;

  Bme280 bme280;
  bme280.temperature = 0;
  bme280.humidity = 0;

  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1) {
    return bme280;
  }

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(SERVER_DISTRIBUTED_IP);
  client.sin_port = htons(SERVER_DISTRIBUTED_PORT);

  if (connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0) {
    return bme280;
  }

  char buf[2];
  snprintf(buf, 2, "%d", 2);
  int size = strlen(buf);
  if (send(socketid, buf, size, 0) != size) {
    close(socketid);
    return bme280;
  }

  char buffer[16];
  int size_rec = recv(socketid, buffer, 16, 0);
  if (size_rec < 0) {
    close(socketid);
    return bme280;
  }
    
  buffer[15] = '\0';
	
  int command;
  double temperature;
  double humidity;
  sscanf(buffer, "%d %lf %lf", &command, &temperature, &humidity);
  bme280.temperature = temperature;
  bme280.humidity = humidity;

  close(socketid);

  return bme280;
}
