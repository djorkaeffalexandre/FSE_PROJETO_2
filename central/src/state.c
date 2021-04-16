#include "state.h"
#include <server.h>
#include <menu.h>
#include <app.h>

#define LAMP1 0
#define LAMP2 1
#define LAMP3 2
#define LAMP4 3
#define AC1 23
#define AC2 24

State _state;

void state_init() {
  _state.lamp1 = 0;
  _state.lamp2 = 0;
  _state.lamp3 = 0;
  _state.lamp4 = 0;
  _state.ac1 = 0;
  _state.ac2 = 0;
  _state.alarm = 0;
  _state.playing = 0;
}

void store_state_update(State state) {
  if (state.alarm == 0) {
    state.playing = 0;
  }
  
  Data data = current_data();
  data.state = state;
  print_data(data);

  int res = 1;
  if (state.lamp1 != _state.lamp1) {
    res = send_command(LAMP1, state.lamp1);
  }
  if (state.lamp2 != _state.lamp2) {
    res = send_command(LAMP2, state.lamp2);
  }
  if (state.lamp3 != _state.lamp3) {
    res = send_command(LAMP3, state.lamp3);
  }
  if (state.lamp4 != _state.lamp4) {
    res = send_command(LAMP4, state.lamp4);
  }
  if (state.ac1 != _state.ac1) {
    res = send_command(AC1, state.ac1);
  }
  if (state.ac2 != _state.ac2) {
    res = send_command(AC2, state.ac2);
  }

  if (res == 1) {
    _state = state;
  }
}

State retrieve_state_data() {
  return _state;
}
