#ifndef BUZZER_H_
#define BUZZER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../peripheral/GPIO/Gpio.h"

//#define Buzzer_ICR         ICR1 // 설정 불가능
#define Buzzer_OCR         OCR0
#define Buzzer_DDR         DDRB
#define Buzzer_DDR_NUM      4

void Buzzer_init();
void Buzzer_makeduty(uint8_t duty);
void Buzzer_soundOn();//켜지는 것
void Buzzer_soundOff();// 꺼지는 것




#endif /* BUZZER_H_ */