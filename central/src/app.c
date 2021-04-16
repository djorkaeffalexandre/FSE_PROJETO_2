#include <stdio.h>
#include <unistd.h>

#include "app.h"
#include "menu.h"
#include "state.h"
#include "server.h"

#define SECOND 1000000

void* app_handler() {
  while (1) {
    Bme280 bme280 = request_sensor();

    Data data;
    data.bme280 = bme280;

    State state;
    state = retrieve_state_data();
    data.state = state;

    print_data(data);
    usleep(SECOND);
  }

  return NULL;
}
