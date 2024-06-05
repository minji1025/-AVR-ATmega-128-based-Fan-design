#include "Ultrasonic.h"

void Ultrasonic_ISR_Process(){
	if(USONIC_PIN & (1<<USONIC_ECHO)){	//시간측정 시작
		Ultrasonic_timerStart();
		Ultrasonic_switchInterrupt(FALLING_EDGE);
	}
	else {	//시간측정 종료
		Ultrasonic_timerStop();
		Ultrasonic_setComplitFlag();
		Ultrasonic_switchInterrupt(RISING_EDGE);
	}
}

void Ultrasonic_init(){
	// 초기화 설정
	Gpio_initPin(&USONIC_DDR,USONIC_ECHO,INPUT); //USONIC_DDR &= ~(1<<USONIC_ECHO);	Echo pin INPUT Mode
	Gpio_initPin(&USONIC_DDR,USONIC_TRIG,OUTPUT);//USONIC_DDR |= (1<<USONIC_TRIGG);	//Trig pin OUTPUT Mode
	
	// INT2, 외부 인터럽트는 상태가 바뀔때 마다 인터럽트 발생 불가
	//Rising Edge,Falling Edge마다 인터럽트 발생하게 끔
	
	USONIC_EICR |= (1<<USONIC_ISCN1)|(1<<USONIC_ISCN0);	//Rising Edge Interrupt
	USONIC_EIMSK |= (1<<USONIC_EIMSK_INT);
	
	UltrasonicDistanceFlag = 0;
}

void Ultrasonic_trigger(){
	Gpio_writePin(&USONIC_PORT,USONIC_TRIG,GPIO_PIN_SET);	//USONIC_PORT |= (1<<USONIC_TRIG);
	_delay_us(15);
	Gpio_writePin(&USONIC_PORT,USONIC_TRIG,GPIO_PIN_RESET);	//USONIC_PORT &= ~(1<<USONIC_TRIG);
}

void Ultrasonic_timerStart(){
	USONIC_TCNT = 0;
	//Timer/Counter1 - 16bit,TCNT1 (prescaler:1/64) p.136
	USONIC_TCCR |=((0<<CS12)|(1<<CS11)|(1<<CS10));
}
void Ultrasonic_timerStop(){
	//No clock source, TCNT++ X
	USONIC_TCCR &= ~((1<<CS12)|(1<<CS11)|(1<<CS10));
}

void Ultrasonic_switchInterrupt(uint8_t mode){
	
	if(mode == FALLING_EDGE){
		USONIC_EICR &= ~((1<<USONIC_ISCN1)|(1<<USONIC_ISCN0));	//ISC를 초기화
		USONIC_EICR |= ((1<<USONIC_ISCN1)|(0<<USONIC_ISCN0));	//Falling Edge Interrupt
	}
	else{
		USONIC_EICR &= ~((1<<USONIC_ISCN1)|(1<<USONIC_ISCN0));	//ISC를 초기화
		USONIC_EICR |= ((1<<USONIC_ISCN1)|(1<<USONIC_ISCN0));	//Rising Edge Interrupt
	}
}

uint16_t Ultrasoinc_getDistance(){
	//거리 계산(1/64 prescaler 설정)
	return (USONIC_TCNT * 0.068);
}

uint8_t Ultrasonic_getComplitFlag(){
	return UltrasonicDistanceFlag;
}
void Ultrasonic_setComplitFlag(){
	UltrasonicDistanceFlag = 1;
}
void Ultrasonic_clearComplitFlag(){
	UltrasonicDistanceFlag = 0;
}
