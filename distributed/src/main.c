#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <server.h>
#include <gpio.h>
#include <quit.h>

int main() {
	gpio_init();
	quit_init();
	bme280_init();

	pthread_t server;

	pthread_create(&server, NULL, server_handler, NULL);

	pthread_join(server, NULL);
	
	return 0;
}
