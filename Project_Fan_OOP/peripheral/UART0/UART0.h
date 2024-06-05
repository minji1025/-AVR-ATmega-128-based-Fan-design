#ifndef UART0_H_
#define UART0_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void UART0_ISR_Process();
void UART0_init();
void UART0_Transmit( unsigned char data );
unsigned char UART0_Receive( void );
uint8_t UART0_avail();
void UART0_Print(char *str);
uint8_t UART0_getRxFlag();
void UART0_clearRxFlag();
void UART0_setRxFlag();
char *UART0_getRxBuff();



#endif /* UART0_H_ */