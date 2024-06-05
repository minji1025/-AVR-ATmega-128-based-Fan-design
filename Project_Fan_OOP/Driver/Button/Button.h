#ifndef BUTTON_H_
#define BUTTON_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../peripheral/Gpio/Gpio.h"

enum{PUSHED,RELEASED};
enum{ACT_NONE,ACT_OFF,ACT_ON};

typedef struct _button{		//변수이므로 GPIO함수 사용x
	volatile uint8_t *DDR;
	volatile uint8_t *PIN;
	uint8_t pinNum;
	uint8_t	prevState;
}button_t;

void Button_init(button_t *btn,volatile uint8_t *ddr,volatile uint8_t *pin, uint8_t pinNum);
uint8_t Button_GetState(button_t *btn);

#endif /* BUTTON_H_ */