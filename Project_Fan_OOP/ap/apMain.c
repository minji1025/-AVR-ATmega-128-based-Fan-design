#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "Service/Device.h"
#include "Service/Timer.h"
#include "Listener/Listener.h"
#include "Presenter/Presenter.h"
#include "../peripheral/TIM/TIM.h"
#include "../peripheral/UART0/UART0.h"
#include "../Driver/FND/FND.h"
#include "../Driver/Ultrasonic/Ultrasonic.h"

//AVR은 printf를 UART0_Transmit 함수를 통해 사용
//사용자가 정의한 버퍼(buffer)를 stdio(standard input output) stream으로 바꿔주는 역할
FILE UART0_OUTPUT = FDEV_SETUP_STREAM(UART0_Transmit, NULL,_FDEV_SETUP_WRITE);

ISR(TIMER0_OVF_vect){
	FND_ISR_Process();
	incTick();
	TCNT0 =130;
}

ISR(TIMER2_COMP_vect){
	timer_incmilisec();
}

ISR(INT2_vect){
	Ultrasonic_ISR_Process();
}

ISR(USART0_RX_vect){
	UART0_ISR_Process();
}

void ap_init(){
	Listener_UART0_init();
	Listener_Button_init();
	Fan_Sevice_init();
	Time_init();
	presenter_init();
	TIM0_init();
	TIM2_init();
	stdout = &UART0_OUTPUT;
	sei();
};/
	
void ap_excute(){
	Listener_Button_eventCheck();
	Listener_UART0_eventCheck();
	Fan_device_Sevice();
	Fan_presenter();
	Fan_UART0_presenter();
}
		


