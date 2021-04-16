#include <stdio.h>
#include <unistd.h>

#include "app.h"
#include "menu.h"
#include "state.h"
#include "server.h"

#define SECOND 1000000

Data _data;

Data current_data() {
  return _data;
}

void* app_handler() {
  while (1) {
    Bme280 bme280 = request_sensor();

    _data.bme280 = bme280;

    State state;
    state = retrieve_state_data();
    _data.state = state;

    print_data(_data);
    usleep(SECOND);
  }

  return NULL;
}
