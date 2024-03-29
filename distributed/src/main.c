#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <server.h>
#include <gpio.h>
#include <quit.h>
#include <bme280.h>

int main() {
	gpio_init();
	quit_init();
	bme280_init();

	// ALL OUTPUT PIN OFF
	all_off();

	pthread_t server, gpio;

	pthread_create(&server, NULL, server_handler, NULL);
	pthread_create(&gpio, NULL, gpio_handler, NULL);

	pthread_join(server, NULL);
	pthread_join(gpio, NULL);
	
	return 0;
}
