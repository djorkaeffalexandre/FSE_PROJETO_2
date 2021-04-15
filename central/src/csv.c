#include "csv.h"

char buffer[10];

void time_generate() {
  time_t current_time;
  struct tm* time_info;

  time(&current_time);
  time_info = localtime(&current_time);

  strftime(buffer, 10, "%H:%M:%S", time_info);
}

void csv_init() {
  FILE *file = fopen("data.csv", "w");
  fprintf(file, "DATETIME, ITEM, STATE\n");
  fclose(file);
}

void write_data(Command command) {
  // Update Datetime
  time_generate();

  // Write file
  FILE *file = fopen("data.csv", "a");
  fprintf(
    file,
    "%s,%s,%d\r\n",
    buffer,
    command.item,
    command.state
  );
  fclose(file);
}
