#include <gpio.h>

void gpio_init() {
  wiringPiSetup();
}

void toggle(int item, int status) {
  pinMode(item, OUTPUT);
  digitalWrite(item, status);
}

void all_off() {
  // LAMP1
  pinMode(LAMP1, OUTPUT);
  digitalWrite(LAMP1, LOW);

  // LAMP2
  pinMode(LAMP2, OUTPUT);
  digitalWrite(LAMP2, LOW);

  // LAMP3
  pinMode(LAMP3, OUTPUT);
  digitalWrite(LAMP3, LOW);

  // LAMP4
  pinMode(LAMP4, OUTPUT);
  digitalWrite(LAMP4, LOW);

  // AC1
  pinMode(AC1, OUTPUT);
  digitalWrite(AC1, LOW);

  // AC2
  pinMode(AC2, OUTPUT);
  digitalWrite(AC2, LOW);
}
