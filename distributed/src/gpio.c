#include <gpio.h>

void gpio_init() {
  wiringPiSetup();
}

void toggle(int item, int status) {
  pinMode(item, OUTPUT);
  softPwmCreate(item, 1, ON);
  softPwmWrite(item, status);
}

void all_off() {
  // LAMP1
  pinMode(LAMP1, OUTPUT);
  softPwmWrite(LAMP1, OFF);

  // LAMP2
  pinMode(LAMP2, OUTPUT);
  softPwmWrite(LAMP2, OFF);

  // LAMP3
  pinMode(LAMP3, OUTPUT);
  softPwmWrite(LAMP3, OFF);

  // LAMP4
  pinMode(LAMP4, OUTPUT);
  softPwmWrite(LAMP4, OFF);

  // AC1
  pinMode(AC1, OUTPUT);
  softPwmWrite(AC1, OFF);

  // AC2
  pinMode(AC2, OUTPUT);
  softPwmWrite(AC2, OFF);
}
