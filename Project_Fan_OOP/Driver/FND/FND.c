#include "FND.h"

uint16_t fndData = 0;
uint8_t fndColonFlag;

void FND_init(){
	//GPIO 초기화
	Gpio_initPin(&FND_DIGIT_DDR,FND_DIGIT_0,OUTPUT);
	Gpio_initPin(&FND_DIGIT_DDR,FND_DIGIT_1,OUTPUT);
	Gpio_initPin(&FND_DIGIT_DDR,FND_DIGIT_2,OUTPUT);
	Gpio_initPin(&FND_DIGIT_DDR,FND_DIGIT_3,OUTPUT);
	Gpio_initPort(&FND_DATA_DDR,OUTPUT);
}

void FND_colonOn(){
	 fndColonFlag = 1;
}
void FND_colonOff(){
	 fndColonFlag = 0;
}

void FND_display(uint16_t fndNum){
	static uint8_t fndDigitState = 0;
	uint8_t fndFont[11] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67,0x80};
	
	fndDigitState = (fndDigitState+1)%5;
	//FND off
	Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_0, GPIO_PIN_SET);
	Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_1, GPIO_PIN_SET);
	Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_2, GPIO_PIN_SET);
	Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_3, GPIO_PIN_SET);

	switch(fndDigitState){
		case 0:
		Gpio_writePort(&FND_DATA_PORT,fndFont[fndNum/1000%10]);
		Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_3,GPIO_PIN_RESET);//천의 자리 FND on
		break;
		
		case 1:
		Gpio_writePort(&FND_DATA_PORT,fndFont[fndNum/100%10]);
		Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_2,GPIO_PIN_RESET);	//백의 자리 FND on
		break;
		
		case 2:
		Gpio_writePort(&FND_DATA_PORT,fndFont[fndNum/10%10]);
		Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_1,GPIO_PIN_RESET);//십의 자리 FND on
		break;
		
		case 3:
		Gpio_writePort(&FND_DATA_PORT,fndFont[fndNum%10]);
		Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_0,GPIO_PIN_RESET);	//일의 자리 FND on
		break;
		
		case 4:
		if (fndColonFlag) Gpio_writePort(&FND_DATA_PORT,fndFont[FND_DP]);	//colon을 킴
		else Gpio_writePort(&FND_DATA_PORT,0x00);	//colon을 끔
		Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_2,GPIO_PIN_RESET);	//백의 자리 FND on
		break;
	}
}

void FND_setFndData(uint16_t data){
	fndData = data;
}

void FND_ISR_Process(){
	FND_display(fndData);
}
void FND_displayoff(){
	Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_0, GPIO_PIN_RESET);
	Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_1, GPIO_PIN_RESET);
	Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_2, GPIO_PIN_RESET);
	Gpio_writePin(&FND_DIGIT_PORT,FND_DIGIT_3, GPIO_PIN_RESET);
}