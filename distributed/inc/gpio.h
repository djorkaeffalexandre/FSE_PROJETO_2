#include <wiringPi.h>
#include <stdio.h>    
#include <softPwm.h>

// 17 -> 0 -> Lâmpada 01
// 18 -> 1 -> Lâmpada 02
// 27 -> 2 -> Lâmpada 03
// 22 -> 3 -> Lâmpada 04
// 13 -> 23 -> Ar-condicionado 01
// 19 -> 24 -> Ar-condicionado 02

#define LAMP1 0
#define LAMP2 1
#define LAMP3 2
#define LAMP4 3
#define AC1 23
#define AC2 24

#ifndef GPIO_H_
#define GPIO_H_

void gpio_init();
void toggle(int item, int status);
void all_off();

#endif /* GPIO_H_ */