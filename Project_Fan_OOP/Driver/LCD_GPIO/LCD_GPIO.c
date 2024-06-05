#include "LCD_GPIO.h"
uint8_t lcdControlData;
void GPIO_LCD_init(){
	Gpio_initPin(&LCD_CONTROL_DDR,LCD_RS,OUTPUT);
	Gpio_initPin(&LCD_CONTROL_DDR,LCD_RW,OUTPUT);
	Gpio_initPin(&LCD_CONTROL_DDR,LCD_E,OUTPUT);
	Gpio_initPort(&LCD_DATA_DDR,OUTPUT);
}

void LCD_init(){
	GPIO_LCD_init();
	_delay_ms(15);
	LCD_WriteCmdData(LCD_Function_set);	//LCD_Function_set:0x38
	_delay_ms(5);
	LCD_WriteCmdData(LCD_Function_set);	//LCD_Function_set:0x38
	_delay_ms(1);
	LCD_WriteCmdData(LCD_Function_set);	//LCD_Function_set:0x38
	LCD_WriteCmdData(LCD_Function_set);	//LCD_Function_set:0x38
	LCD_WriteCmdData(LCD_Display_Off);	//LCD_Display_Off:0x08
	LCD_WriteCmdData(LCD_Display_Clear);	//LCD_Display_Clear:0x01
	LCD_WriteCmdData(LCD_Entry_Mode_Set);	//LCD_Entry_Mode_Set:0x06 (I/D(1): 방향(왼->오))
	LCD_WriteCmdData(LCD_Display_On);	//LCD_Display_On:0x0C
}

void gpio_writeControlData(uint8_t data){
	Gpio_writePort(&LCD_CONTROL_PORT,data);
}
void gpio_writeData(uint8_t data){
	Gpio_writePort(&LCD_DATA_PORT,data);
}

void LCD_cmdMode(){
	//RS -> LOW (0)
	lcdControlData &= ~(1<<LCD_RS);
	gpio_writeControlData(lcdControlData);
}

void LCD_charMode(){
	//RS -> HIGH (1)
	lcdControlData |= (1<<LCD_RS);
	gpio_writeControlData(lcdControlData);
}

void LCD_writeMode(){
	//RW -> LOW (0)
	lcdControlData &= ~(1<<LCD_RW);
	gpio_writeControlData(lcdControlData);
}

void LCD_enableHigh(){
	//enable -> HIGH (1)
	lcdControlData |= (1<<LCD_E);
	gpio_writeControlData(lcdControlData);
	_delay_ms(1);
}
void LCD_writeByte(uint8_t data){
	gpio_writeData(data);
}

void LCD_enableLow(){
	//enable -> LOW (0)
	lcdControlData &= ~(1<<LCD_E);
	gpio_writeControlData(lcdControlData);
	_delay_ms(1);
}

// LCD Write Mode(Instruction),명령어 쓰기 동작
void LCD_WriteCmdData(uint8_t data){
	LCD_cmdMode();
	LCD_writeMode();
	LCD_enableHigh();
	LCD_writeByte(data);
	LCD_enableLow();
}

// LCD Write Mode(Data), 문자 쓰기 동작
void LCD_WriteCharData(uint8_t data){
	LCD_charMode();
	LCD_writeMode();
	LCD_enableHigh();
	LCD_writeByte(data);
	LCD_enableLow();
}

void LCD_writeString(char *str){
	for(int i = 0; str[i] ; i++){
		LCD_WriteCharData(str[i]);
	}
}
void LCD_gotoXY(uint8_t row, uint8_t col){
	col %= 16;
	row %= 2;
	uint8_t lcdRegisterAddress =(0x40 *row ) +col;
	uint8_t command = 0x80 + lcdRegisterAddress;
	LCD_WriteCmdData(command);
}
void LCD_writeStringXY(uint8_t row, uint8_t col,char *str){
	LCD_gotoXY(row,col);
	LCD_writeString(str);
}
void LCD_displayClear(){
	LCD_WriteCmdData(LCD_Display_Clear);
}
void LCD_displayOff(){
	LCD_WriteCmdData(LCD_Display_Off);
}