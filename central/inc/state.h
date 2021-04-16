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

void state_init();
void store_state_update(State state);
State retrieve_state_data();

#endif /* STATE_H_ */