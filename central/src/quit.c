#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>
#include <string.h>

void quit_handler(char *message) {
  refresh();
  endwin();
  int len = strlen(message);
  if (len > 0) {
    printf("%s\n", message);
  }
  exit(0);
}

void quit_init() {
  signal(SIGINT, quit_handler);
}
