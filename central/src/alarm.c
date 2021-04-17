#include <stdio.h>
#include <stdlib.h>
#include <state.h>
#include <pthread.h>
#include "alarm.h"

int playing = 0;

void alarm_handler() {
  State state = retrieve_state_data();

  // Alarme acionado
  if (state.alarm == 1) {
    state.playing = 1;
    playing = 1;
    pthread_t alarm;
    pthread_create(&alarm, NULL, play, NULL);
    store_state_update(state);
  }
}

void alarm_off() {
  playing = 0;
}

void* play() {
  while (playing == 1) {
    printf("to tocando..\n");
    system("cd ..; omxplayer beep.mp3 > /dev/null");
  }

  return NULL;
}
