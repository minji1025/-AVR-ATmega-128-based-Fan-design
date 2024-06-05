#include "UART0.h"

char UART0RxBuff[100];
uint8_t uart0RxFlag;

void UART0_ISR_Process(){
	//computer -> AVR 문자를 buff에 저장
	static uint8_t uart0RxTail = 0;
	uint8_t rx0Data = UDR0;
	if(rx0Data == '\n'){	//개행 문자까지 받아 드린다.
		UART0RxBuff[uart0RxTail] = rx0Data;
		uart0RxTail++;
		UART0RxBuff[uart0RxTail] = 0;	//'\n'도 buff에 추가
		uart0RxTail = 0;
		uart0RxFlag = 1; //수신이 완료를 했다는 flag
	}
	else {
		UART0RxBuff[uart0RxTail] = rx0Data;
		uart0RxTail++;
	}
}

void UART0_init(){
	uart0RxFlag = 0;
	//UART0, TxD, RxD: x2 Mode, BaudRate: 9600
	//8Bit Data, 1Bit Stop, parity None(default)
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	UCSR0A |= (1<<U2X0);
	UCSR0B |= (1<<RXCIE0);  //1Btye Data Rx interrupt enable
	UBRR0L = 207;
}

void UART0_Transmit( unsigned char data ){
	// Wait for empty transmit buffer, UDRE0의 값이 1(버퍼가 비어있음)이면 빠져나옴
	while ( !( UCSR0A & (1<<UDRE0)) );
	//Put data into buffer, sends the data
	UDR0 = data;
}
unsigned char UART0_Receive( void ){
	// Wait for data to be received
	while ( !(UCSR0A & (1<<RXC0)));
	//Get and return received data from buffer
	return UDR0;
}

uint8_t UART0_avail(){
	if (!(UCSR0A & (1<<RXC0))){
		return 0;	//Rx data 없다
	}
	return 1;		//Rx data 있다
}

void UART0_Print(char *str){	//문자열 출력
	for(int i = 0; str[i] ;i++){
		UART0_Transmit(str[i]);
	}
}

uint8_t UART0_getRxFlag(){	//get
	return uart0RxFlag;
}
void UART0_clearRxFlag(){	//set 0
	uart0RxFlag = 0;
}
void UART0_setRxFlag(){		//set 1
	uart0RxFlag = 1;
}
char *UART0_getRxBuff(){
	return UART0RxBuff;		//배열명(주소값)
}