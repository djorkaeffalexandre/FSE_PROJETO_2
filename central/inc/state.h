#ifndef STATE_H_
#define STATE_H_

typedef struct {
  int lamp1;
  int lamp2;
  int lamp3;
  int lamp4;
  int ac1;
  int ac2;
  int alarm;
  int playing;
} State;

typedef struct {
  int pres1;
  int pres2;
  int abr1;
  int abr2;
  int abr3;
  int abr4;
  int abr5;
  int abr6;
} Entry;

void state_init();
void store_state_update(State state);
void state_entry_handler(int command);
State retrieve_state_data();

#endif /* STATE_H_ */