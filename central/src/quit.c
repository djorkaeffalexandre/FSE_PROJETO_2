#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <ncurses.h>

void quit_handler() {
  refresh();
  endwin();
  exit(0);
}

void quit_init() {
  signal(SIGINT, quit_handler);
}
