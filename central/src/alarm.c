#include <stdio.h>
#include <stdlib.h>
#include <state.h>

void alarm_handler() {
  State state = retrieve_state_data();

  // Alarme acionado
  if (state.alarm == 1) {
    printf("beep\n");
    return;
  }

  printf("nothing to do...");
}
