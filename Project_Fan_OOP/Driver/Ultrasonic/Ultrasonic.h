#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "../../peripheral/Gpio/Gpio.h"

#define USONIC_DDR		DDRD
#define USONIC_PORT		PORTD
#define USONIC_PIN		PIND
#define USONIC_TRIG	3
#define USONIC_ECHO		2
#define USONIC_TCNT		TCNT1
#define USONIC_EICR		EICRA
#define USONIC_EIMSK	EIMSK
#define USONIC_TCCR		TCCR1B
#define USONIC_ISCN1	ISC21
#define USONIC_ISCN0	ISC20
#define USONIC_EIMSK_INT	INT2
enum{FALLING_EDGE,RISING_EDGE};
uint8_t UltrasonicDistanceFlag;

void Ultrasonic_ISR_Process();
void Ultrasonic_init();
void Ultrasonic_trigger();
void Ultrasonic_timerStart();
void Ultrasonic_timerStop();
void Ultrasonic_switchInterrupt(uint8_t mode);
uint16_t Ultrasoinc_getDistance();
uint8_t Ultrasonic_getComplitFlag();
void Ultrasonic_setComplitFlag();
void Ultrasonic_clearComplitFlag();


#endif /* ULTRASONIC_H_ */