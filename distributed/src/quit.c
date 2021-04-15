#include "quit.h"
#include "gpio.h"

void quit_handler() {
  all_off();
  exit(0);
}

void quit_init() {
  signal(SIGINT, quit_handler);
}
