#ifndef MOTOR_H_
#define MOTOR_H_

#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "../../peripheral/GPIO/Gpio.h"

#define MOTOR_ICR	ICR3
#define MOTOR_OCR	OCR3A
#define MOTOR_DDR   DDRE
#define MOTOR_DDR_NUM    3

void Motor_init();
void Motor_makeHerzDuty(uint16_t herz,uint8_t duty);
void Motor_On();
void Motor_Off();

#endif /* MOTOR_H_ */