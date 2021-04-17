#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <app.h>
#include <quit.h>
#include <menu.h>
#include <state.h>
#include <server.h>
#include <csv.h>

int main() {
	quit_init();
	state_init();
	csv_init();
	app_init();

	pthread_t app, menu, server;

	pthread_create(&app, NULL, app_handler, NULL);
	pthread_create(&menu, NULL, menu_handler, NULL);
	pthread_create(&server, NULL, recv_message, NULL);

	pthread_join(app, NULL);
	pthread_join(menu, NULL);
	pthread_join(server, NULL);

	return 0;
}
