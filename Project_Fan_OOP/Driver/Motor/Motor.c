#include "Motor.h"

void Motor_init()
{
	
	// PWM 제어, Timer/Counter3 사용.
	// Prescaler 1/64
	// Top 값 : freq 1Khz (ICR3)
	// Duty Cycle : 50% (OCR3)
	// Non-inverting Mode : 기준점보다 낮을때를 High로 하겠다.
	Gpio_initPin(&MOTOR_DDR, MOTOR_DDR_NUM, OUTPUT);
	
	TCCR3B |= ((0<<CS32) | (1<<CS31) | (1<<CS30));			// prescaler 1/64 설정
	TCCR3A |= ((1<<WGM31) | (0<<WGM30));					// Fast PWM 설정
	TCCR3B |= ((1<<WGM33) | (1<<WGM32));					// Fast PWM 설정
}

void Motor_makeHerzDuty(uint16_t herz,uint8_t duty){
	MOTOR_ICR = (250000/ herz) - 1;
	MOTOR_OCR = MOTOR_ICR / duty; //2^16 = 65536;
}
void Motor_On()
{
	TCCR3A |= (1<<COM3A1) | (0<<COM3A0);					// Non-inverting Mode
}

void Motor_Off()
{
	TCCR3A &= ~((1<<COM3A1) | (1<<COM3A0));
}