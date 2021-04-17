#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>

#include "menu.h"
#include "quit.h"
#include "state.h"
#include "csv.h"

#define WIDTH 80
#define HEIGHT 17

WINDOW *window;
WINDOW *window2;

char *options[] = {
	"TOGGLE LAMP 1:",
	"TOGGLE LAMP 2:",
	"TOGGLE LAMP 3:",
	"TOGGLE LAMP 4:",
	"TOGGLE AC 1:",
	"TOGGLE AC 2:",
	"TOGGLE ALARM:",
	"EXIT",
};

int startx = 0;
int starty = 0;
int n_options = sizeof(options) / sizeof(char *);

void print_menu(WINDOW *window, int highlight) {
	int x = 2, y = 2, i;

	box(window, 0, 0);
	for(i = 0; i < n_options; i++) {
		if (i == n_options - 1) {
			wattron(window, COLOR_PAIR(2));
		}
		if (highlight == i + 1) {
			wattron(window, A_REVERSE);
			mvwprintw(window, y, x, "%s", options[i]);
			wattroff(window, A_REVERSE);
		} else {
			mvwprintw(window, y, x, "%s", options[i]);
		}
		if (i == n_options - 1) {
			wattroff(window, COLOR_PAIR(2));
		}
		++y;
	}
	wrefresh(window);
}

void clear_menu(WINDOW *window_param) {
	wclear(window_param);
	wborder(window_param, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');  
	wrefresh(window_param);
	delwin(window_param); 
}

void print_data(Data data) {
	wattron(window, COLOR_PAIR(data.state.lamp1 == 1 ? 3 : 2));
	mvwprintw(window, 2, 17, data.state.lamp1 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.state.lamp1 == 1 ? 3 : 2));

	wattron(window, COLOR_PAIR(data.state.lamp2 == 1 ? 3 : 2));
	mvwprintw(window, 3, 17, data.state.lamp2 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.state.lamp2 == 1 ? 3 : 2));

	wattron(window, COLOR_PAIR(data.state.lamp3 == 1 ? 3 : 2));
	mvwprintw(window, 4, 17, data.state.lamp3 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.state.lamp3 == 1 ? 3 : 2));

	wattron(window, COLOR_PAIR(data.state.lamp4 == 1 ? 3 : 2));
	mvwprintw(window, 5, 17, data.state.lamp4 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.state.lamp4 == 1 ? 3 : 2));

	wattron(window, COLOR_PAIR(data.state.ac1 == 1 ? 3 : 2));
	mvwprintw(window, 6, 17, data.state.ac1 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.state.ac1 == 1 ? 3 : 2));

	wattron(window, COLOR_PAIR(data.state.ac2 == 1 ? 3 : 2));
	mvwprintw(window, 7, 17, data.state.ac2 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.state.ac2 == 1 ? 3 : 2));

	wattron(window, COLOR_PAIR(data.state.alarm == 1 ? 3 : 2));
	mvwprintw(window, 8, 17, data.state.alarm == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(data.state.alarm == 1 ? 3 : 2));

	wattron(window, COLOR_PAIR(1));
  mvwprintw(window, 11, 2, "TEMPERATURE: %4.2f", data.bme280.temperature);
  mvwprintw(window, 12, 2, "HUMIDITY: %4.2f", data.bme280.humidity);
	wattroff(window, COLOR_PAIR(1));

	wattron(window, COLOR_PAIR(data.state.playing == 1 ? 3 : 2));
	mvwprintw(window, 14, 2, "ALARM PLAYING: %s", data.state.playing == 1 ? "TRUE " : "FALSE");
	wattroff(window, COLOR_PAIR(data.state.playing == 1 ? 3 : 2));

  wrefresh(window);
}

void print_entry(Entry entry) {
	mvwprintw(window, 2, 22, "Sensor de Presença 01 (Sala):");
	wattron(window, COLOR_PAIR(entry.pres1 == 1 ? 3 : 2));
	mvwprintw(window, 2, 61, entry.pres1 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(entry.pres1 == 1 ? 3 : 2));

	mvwprintw(window, 3, 22, "Sensor de Presença 02 (Cozinha):");
	wattron(window, COLOR_PAIR(entry.pres2 == 1 ? 3 : 2));
	mvwprintw(window, 3, 61, entry.pres2 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(entry.pres2 == 1 ? 3 : 2));

	mvwprintw(window, 4, 22, "Sensor Abertura 01 (Porta Cozinha):");
	wattron(window, COLOR_PAIR(entry.abr1 == 1 ? 3 : 2));
	mvwprintw(window, 4, 61, entry.abr1 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(entry.abr1 == 1 ? 3 : 2));

	mvwprintw(window, 5, 22, "Sensor Abertura 02 (Janela Cozinha):");
	wattron(window, COLOR_PAIR(entry.abr2 == 1 ? 3 : 2));
	mvwprintw(window, 5, 61, entry.abr2 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(entry.abr2 == 1 ? 3 : 2));

	mvwprintw(window, 6, 22, "Sensor Abertura 03 (Porta Sala):");
	wattron(window, COLOR_PAIR(entry.abr3 == 1 ? 3 : 2));
	mvwprintw(window, 6, 61, entry.abr3 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(entry.abr3 == 1 ? 3 : 2));

	mvwprintw(window, 7, 22, "Sensor Abertura 04 (Janela Sala):");
	wattron(window, COLOR_PAIR(entry.abr4 == 1 ? 3 : 2));
	mvwprintw(window, 7, 61, entry.abr4 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(entry.abr4 == 1 ? 3 : 2));

	mvwprintw(window, 8, 22, "Sensor Abertura 05 (Janela Quarto 01):");
	wattron(window, COLOR_PAIR(entry.abr5 == 1 ? 3 : 2));
	mvwprintw(window, 8, 61, entry.abr5 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(entry.abr5 == 1 ? 3 : 2));

	mvwprintw(window, 9, 22, "Sensor Abertura 06 (Janela Quarto 02):");
	wattron(window, COLOR_PAIR(entry.abr6 == 1 ? 3 : 2));
	mvwprintw(window, 9, 61, entry.abr6 == 1 ? "ON " : "OFF");
	wattroff(window, COLOR_PAIR(entry.abr6 == 1 ? 3 : 2));

  wrefresh(window);
}

void* menu_handler() {
	int highlight = 1;
	int option = 0;
	int c;

	initscr();
	start_color(); 
	clear();
	noecho();
	cbreak();
	curs_set(0);
	init_pair(1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
     
	window = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(window, TRUE);
	refresh();

	window2 = newwin(HEIGHT, WIDTH, 80, startx);
	box(window2, 0, 0);
	wrefresh(window2);

	state_init();
 
	do {
		print_menu(window, highlight);
		c = wgetch(window);

		switch(c) {
			case KEY_UP:
				if(highlight == 1)
					highlight = n_options;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_options)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:    
				option = highlight;

				State state = retrieve_state_data();

				if (option == 1) {
					state.lamp1 = state.lamp1 == 1 ? 0 : 1;
					char *item = "LAMP1";
					Command command;
					command.item = item;
					command.state = state.lamp1;
					write_data(command);
				}

				if (option == 2) {
					state.lamp2 = state.lamp2 == 1 ? 0 : 1;
					char *item = "LAMP2";
					Command command;
					command.item = item;
					command.state = state.lamp2;
					write_data(command);
				}

				if (option == 3) {
					state.lamp3 = state.lamp3 == 1 ? 0 : 1;
					char *item = "LAMP3";
					Command command;
					command.item = item;
					command.state = state.lamp3;
					write_data(command);
				}

				if (option == 4) {
					state.lamp4 = state.lamp4 == 1 ? 0 : 1;
					char *item = "LAMP4";
					Command command;
					command.item = item;
					command.state = state.lamp4;
					write_data(command);
				}

				if (option == 5) {
					state.ac1 = state.ac1 == 1 ? 0 : 1;
					char *item = "AC1";
					Command command;
					command.item = item;
					command.state = state.ac1;
					write_data(command);
				}

				if (option == 6) {
					state.ac2 = state.ac2 == 1 ? 0 : 1;
					char *item = "AC2";
					Command command;
					command.item = item;
					command.state = state.ac2;
					write_data(command);
				}

				if (option == 7) {
					state.alarm = state.alarm == 1 ? 0 : 1;
					char *item = "ALARM";
					Command command;
					command.item = item;
					command.state = state.alarm;
					write_data(command);
				}

				store_state_update(state);

				if (option == 8) {
					char *message = "Exiting...";
					quit_handler(message);
				}

				break;
			default:
				refresh();
				break;
		}
	} while(1);

	return NULL;
}
