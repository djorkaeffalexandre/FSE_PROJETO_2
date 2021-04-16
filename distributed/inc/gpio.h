#include <wiringPi.h>
#include <stdio.h>    
#include <softPwm.h>

// 17 -> 0 -> Lâmpada 01
// 18 -> 1 -> Lâmpada 02
// 27 -> 2 -> Lâmpada 03
// 22 -> 3 -> Lâmpada 04
// 13 -> 23 -> Ar-condicionado 01
// 19 -> 24 -> Ar-condicionado 02
// 25 -> 6 -> Sensor de Presença 01 (Sala)
// 26 -> 25 -> Sensor de Presença 02 (Cozinha)
// 05 -> 21 -> Sensor Abertura 01 (Porta Cozinha)
// 06 -> 22 -> Sensor Abertura 02 (Janela Cozinha)
// 12 -> 26 -> Sensor Abertura 03 (Porta Sala)
// 16 -> 27 -> Sensor Abertura 04 (Janela Sala)
// 20 -> 28 -> Sensor Abertura 05 (Janela Quarto 01)
// 21 -> 29 -> Sensor Abertura 06 (Janela Quarto 02)

#define LAMP1 0
#define LAMP2 1
#define LAMP3 2
#define LAMP4 3
#define AC1 23
#define AC2 24

#define PRES1 6
#define PRES2 25
#define ABR1 21
#define ABR2 22
#define ABR3 26
#define ABR4 27
#define ABR5 28
#define ABR6 29

#ifndef GPIO_H_
#define GPIO_H_

void gpio_init();
void toggle(int item, int status);
void all_off();
void* gpio_handler();

#endif /* GPIO_H_ */