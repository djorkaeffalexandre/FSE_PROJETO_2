#include "state.h"
#include <server.h>

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
}

void store_state_update(State state) {
  if (state.lamp1 != _state.lamp1) {
    send_message(LAMP1, state.lamp1);
  }
  if (state.lamp2 != _state.lamp2) {
    send_message(LAMP2, state.lamp2);
  }
  if (state.lamp3 != _state.lamp3) {
    send_message(LAMP3, state.lamp3);
  }
  if (state.lamp4 != _state.lamp4) {
    send_message(LAMP4, state.lamp4);
  }
  if (state.ac1 != _state.ac1) {
    send_message(AC1, state.ac1);
  }
  if (state.ac2 != _state.ac2) {
    send_message(AC2, state.ac2);
  }
  _state = state;
}

State retrieve_state_data() {
  return _state;
}
