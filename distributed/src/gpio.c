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

void handle_pres1(void) {
  char* message = "1";
  printf("Alteração em: Sensor de Presença 01 (Sala)...\n");
  server_send(message);
}

void handle_pres2(void) {
  char* message = "2";
  printf("Alteração em: Sensor de Presença 02 (Cozinha)...\n");
  server_send(message);
}

void handle_abr1(void) {
  char* message = "3";
  printf("Alteração em: Sensor Abertura 01 (Porta Cozinha)...\n");
  server_send(message);
}

void handle_abr2(void) {
  char* message = "4";
  printf("Alteração em: Sensor Abertura 02 (Janela Cozinha)...\n");
  server_send(message);
}

void handle_abr3(void) {
  char* message = "5";
  printf("Alteração em: Sensor Abertura 03 (Porta Sala)...\n");
  server_send(message);
}

void handle_abr4(void) {
  char* message = "6";
  printf("Alteração em: Sensor Abertura 04 (Janela Sala)...\n");
  server_send(message);
}

void handle_abr5(void) {
  char* message = "7";
  printf("Alteração em: Sensor Abertura 05 (Janela Quarto 01)...\n");
  server_send(message);
}

void handle_abr6(void) {
  char* message = "8";
  printf("Alteração em: Sensor Abertura 06 (Janela Quarto 02)...\n");
  server_send(message);
}

void* gpio_handler() {
  // Sensor de Presença 01 (Sala)
  pinMode(PRES1, OUTPUT);
  wiringPiISR(PRES1, INT_EDGE_BOTH, &handle_pres1);

  // Sensor de Presença 02 (Cozinha)
  pinMode(PRES2, OUTPUT);
  wiringPiISR(PRES2, INT_EDGE_BOTH, &handle_pres2);

  // Sensor Abertura 01 (Porta Cozinha)
  pinMode(ABR1, OUTPUT);
  wiringPiISR(ABR1, INT_EDGE_BOTH, &handle_abr1);

  // Sensor Abertura 02 (Janela Cozinha)
  pinMode(ABR2, OUTPUT);
  wiringPiISR(ABR2, INT_EDGE_BOTH, &handle_abr2);
  
  // Sensor Abertura 03 (Porta Sala)
  pinMode(ABR3, OUTPUT);
  wiringPiISR(ABR3, INT_EDGE_BOTH, &handle_abr3);

  // Sensor Abertura 04 (Janela Sala)
  pinMode(ABR4, OUTPUT);
  wiringPiISR(ABR4, INT_EDGE_BOTH, &handle_abr4);

  // Sensor Abertura 05 (Janela Quarto 01)
  pinMode(ABR5, OUTPUT);
  wiringPiISR(ABR5, INT_EDGE_BOTH, &handle_abr5);

  // Sensor Abertura 06 (Janela Quarto 02)
  pinMode(ABR6, OUTPUT);
  wiringPiISR(ABR6, INT_EDGE_BOTH, &handle_abr6);

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
