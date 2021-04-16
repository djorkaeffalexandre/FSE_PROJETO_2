#include <unistd.h>
#include <gpio.h>
#include <server.h>

void gpio_init() {
  wiringPiSetup();
}

void toggle(int item, int status) {
  pinMode(item, OUTPUT);
  digitalWrite(item, status);
}

void handle(void) {
  char* message = "1";
  server_send(message);
}

void* gpio_handler() {
  // Sensor de Presença 01 (Sala)
  pinMode(PRES1, OUTPUT);
  wiringPiISR(PRES1, INT_EDGE_RISING, &handle);

  // Sensor de Presença 02 (Cozinha)
  pinMode(PRES2, OUTPUT);
  wiringPiISR(PRES2, INT_EDGE_RISING, &handle);

  // Sensor Abertura 01 (Porta Cozinha)
  pinMode(ABR1, OUTPUT);
  wiringPiISR(ABR1, INT_EDGE_RISING, &handle);

  // Sensor Abertura 02 (Janela Cozinha)
  pinMode(ABR2, OUTPUT);
  wiringPiISR(ABR2, INT_EDGE_RISING, &handle);
  
  // Sensor Abertura 03 (Porta Sala)
  pinMode(ABR3, OUTPUT);
  wiringPiISR(ABR3, INT_EDGE_RISING, &handle);

  // Sensor Abertura 04 (Janela Sala)
  pinMode(ABR4, OUTPUT);
  wiringPiISR(ABR4, INT_EDGE_RISING, &handle);

  // Sensor Abertura 05 (Janela Quarto 01)
  pinMode(ABR5, OUTPUT);
  wiringPiISR(ABR5, INT_EDGE_RISING, &handle);

  // Sensor Abertura 06 (Janela Quarto 02)
  pinMode(ABR6, OUTPUT);
  wiringPiISR(ABR6, INT_EDGE_RISING, &handle);

  for(;;) {
    sleep(1);
  }
}

void all_off() {
  // Lâmpada 01
  pinMode(LAMP1, OUTPUT);
  digitalWrite(LAMP1, LOW);

  // Lâmpada 02
  pinMode(LAMP2, OUTPUT);
  digitalWrite(LAMP2, LOW);

  // Lâmpada 03
  pinMode(LAMP3, OUTPUT);
  digitalWrite(LAMP3, LOW);

  // Lâmpada 04
  pinMode(LAMP4, OUTPUT);
  digitalWrite(LAMP4, LOW);

  // Ar-condicionado 01
  pinMode(AC1, OUTPUT);
  digitalWrite(AC1, LOW);

  // Ar-condicionado 02
  pinMode(AC2, OUTPUT);
  digitalWrite(AC2, LOW);
}
