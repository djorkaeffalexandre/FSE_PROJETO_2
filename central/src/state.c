#include "state.h"
#include <server.h>
#include <menu.h>
#include <app.h>
#include <alarm.h>

#define LAMP1 0
#define LAMP2 1
#define LAMP3 2
#define LAMP4 3
#define AC1 23
#define AC2 24

State _state;
Entry _entry;

void state_init() {
  _state.lamp1 = 0;
  _state.lamp2 = 0;
  _state.lamp3 = 0;
  _state.lamp4 = 0;
  _state.ac1 = 0;
  _state.ac2 = 0;
  _state.alarm = 0;
  _state.playing = 0;

  _entry.pres1 = 0;
  _entry.pres2 = 0;
  _entry.abr1 = 0;
  _entry.abr2 = 0;
  _entry.abr3 = 0;
  _entry.abr4 = 0;
  _entry.abr5 = 0;
  _entry.abr6 = 0;

  Data data = current_data();
  data.state = _state;
  print_data(data);
  print_entry(_entry);
}

void state_entry_handler(int command) {
  if (command == 1) {
    _entry.pres1 = _entry.pres1 == 1 ? 0 : 1;
  }
  if (command == 2) {
    _entry.pres2 = _entry.pres2 == 1 ? 0 : 1;
  }
  if (command == 3) {
    _entry.abr1 = _entry.abr1 == 1 ? 0 : 1;
  }
  if (command == 4) {
    _entry.abr2 = _entry.abr2 == 1 ? 0 : 1;
  }
  if (command == 5) {
    _entry.abr3 = _entry.abr3 == 1 ? 0 : 1;
  }
  if (command == 6) {
    _entry.abr4 = _entry.abr4 == 1 ? 0 : 1;
  }
  if (command == 7) {
    _entry.abr5 = _entry.abr5 == 1 ? 0 : 1;
  }
  if (command == 8) {
    _entry.abr6 = _entry.abr6 == 1 ? 0 : 1;
  }

  if (
    _entry.pres1 == 1
    || _entry.pres2 == 1
    || _entry.abr1 == 1
    || _entry.abr2 == 1
    || _entry.abr3 == 1
    || _entry.abr4 == 1
    || _entry.abr5 == 1
    || _entry.abr6 == 1
  ) {
    alarm_handler();
  } else {
    _state.playing = 0;
    print_data(_state);
  }

  print_entry(_entry);
}

void store_state_update(State state) {
  if (state.alarm == 0) {
    state.playing = 0;
  }
  if (state.alarm == 1 && (
    _entry.pres1 == 1
    || _entry.pres2 == 1
    || _entry.abr1 == 1
    || _entry.abr2 == 1
    || _entry.abr3 == 1
    || _entry.abr4 == 1
    || _entry.abr5 == 1
    || _entry.abr6 == 1)) {
    state.playing = 1;
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
