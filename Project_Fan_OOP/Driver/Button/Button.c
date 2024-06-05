#include "Button.h"

void Button_init(button_t *btn,volatile uint8_t *ddr,volatile uint8_t *pin, uint8_t pinNum){
	btn->DDR = ddr;
	btn->PIN = pin;
	btn->pinNum = pinNum;
	btn->prevState = RELEASED;
	Gpio_initPin(btn->DDR,btn->pinNum,INPUT) ;	//*btn->DDR &= ~(1<<btn->pinNum);
}
uint8_t Button_GetState(button_t *btn){
	uint8_t curState =Gpio_readPin(btn->PIN,btn->pinNum);	//uint8_t curState = *(btn->PIN)&(1<<btn->pinNum);
	if((curState==PUSHED)&&(btn->prevState==RELEASED)){		//curState 눌림 && prevState 안눌림 --> 누르는 순간
		btn->prevState =PUSHED;		//prevState = 눌림
		return ACT_ON;		//즉 눌리면 바로 실행
	}
	if((curState!=PUSHED)&&(btn->prevState==PUSHED)){	//curState 안눌림 && prevState 눌림	--> 때는 순간
		btn->prevState =RELEASED;	//prevState = 안눌림
		return ACT_OFF;		//즉 때는 순간 바로 실행
	}
	return ACT_NONE;	//아무것도 아니면
}
