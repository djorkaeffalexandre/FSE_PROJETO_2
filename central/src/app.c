#include <stdio.h>
#include <unistd.h>

#include "app.h"
#include "menu.h"
#include "state.h"
#include "server.h"

#define SECOND 1000000

Data _data;

void app_init() {
  Bme280 bme280;
  bme280.temperature = 0;
  bme280.humidity = 0;
  _data.bme280 = bme280;
}

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

    system("cd ..; omxplayer beep.mp3 > /dev/null");

    print_data(_data);
    usleep(SECOND);
  }

  return NULL;
}
