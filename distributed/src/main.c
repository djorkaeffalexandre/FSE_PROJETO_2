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

	struct bme280_data data = bme280_read();
	printf("%4.2f %4.2f\n", data.temperature, data.humidity);

	pthread_t server;

	pthread_create(&server, NULL, server_handler, NULL);

	pthread_join(server, NULL);
	
	return 0;
}
