#include "TIM.h"

void TIM0_init(){
	TCCR0 |= ((1<<CS02)|(0<<CS01)|(1<<CS00));
	TIMSK |= (1<<TOIE0);
	TCNT0 =130;
}

void TIM2_init(){
	//timer/counter 2 , CTC Mode , 1ms period Interrupt(1/64 Prescaler)
	TCCR2 |= ((0<<CS22)|(1<<CS21)|(1<<CS20));
	TCCR2 |= ((1<<WGM21)|(0<<WGM20));		//CTC Mode 설정
	TIMSK |= (1<<OCIE2);
	OCR2 = 250-1; //0부터 카운트
}