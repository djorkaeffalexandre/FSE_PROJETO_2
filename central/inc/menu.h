#include "state.h"
#include "server.h"

#ifndef MENU_H_
#define MENU_H_

typedef struct {
  Bme280 bme280;
  State state;
} Data;

void* menu_handler();
void print_data(Data data);

#endif /* MENU_H_ */