#include "Gpio.h"

//GPIO 기능,동작
//N PORT의 N PIN에 대한 입출력 설정 -->DDR
//출력 MODE PIN에 대한 출력(0 or 1)	-->PORT
//입력 MODE PIN에 대한 입력	-->PIN

//DDR
//8개 pin 한번에 초기화 (DDRA = 0x00 or DDRD = 0xff)
void Gpio_initPort(volatile uint8_t *DDR, uint8_t dir){		//dir은 방향성(출력,입력)
	if(dir == OUTPUT){
		*DDR = 0xff;	//DDR은 주소 --> *DDR 사용
	}
	else{
		*DDR = 0x00;
	}
}

//1개 pin 초기화 (DDRA & =~(1<<0) or DDAD |= (1<<0))
void Gpio_initPin(volatile uint8_t *DDR, uint8_t pinNum, uint8_t dir){	
	if(dir == OUTPUT){
		*DDR |= (1<<pinNum);	//if pinNum=0, DDRD = DDRD| 0000 0001
	}
	else {
		*DDR &= ~(1<<pinNum);	//if pinNum=0, DDRD = DDRD & 1111 1110
	}
}

//PORT
//8개 제어
void Gpio_writePort(volatile uint8_t *PORT, uint8_t data){	
	*PORT =data;
}

//1개 제어
void Gpio_writePin(volatile uint8_t *PORT, uint8_t pinNum, uint8_t state){	
	if(state == GPIO_PIN_SET){
		*PORT |= (1<<pinNum);
	}
	else{
		*PORT &= ~(1<<pinNum);
	}
}

//PIN
//8개 읽음
uint8_t Gpio_readPort(volatile uint8_t *PIN){	
	return *PIN;
}
//1개 읽음
uint8_t Gpio_readPin(volatile uint8_t *PIN, uint8_t pinNum){
	return ((*PIN&(1<<pinNum)) !=0);	//읽은 값이 그대로 반환 되어야 함 
}