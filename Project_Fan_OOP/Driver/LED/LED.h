#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void LED_init(volatile uint8_t *DDR);
void LED_Allon(volatile uint8_t *PORT);
void LED_Alloff(volatile uint8_t *PORT);
void LED_outPutData(volatile uint8_t *PORT, uint8_t data);

#endif /* LED_H_ */