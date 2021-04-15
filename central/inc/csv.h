#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef CSV_H_
#define CSV_H_

typedef struct {
  char* item;
  int state;
} Command;

void csv_init();
void write_data(Command command);

#endif /* CSV_H_ */
