#include "LCD_I2C.h"
uint8_t lcdControlData;

void LCD_I2C_init(){
	lcdControlData = 0;
	I2C_init();
	
	_delay_ms(15);
	LCD_I2C_cmdMode();
	LCD_I2C_writeMode();
	LCD_I2C_writeNibble(LCD_Function_SET_8BIT);	//0011 짤림
	_delay_ms(5);
	LCD_I2C_writeNibble(LCD_Function_SET_8BIT);	//0011 짤림
	_delay_ms(1);
	LCD_I2C_writeNibble(LCD_Function_SET_8BIT);	//0011 짤림
	LCD_I2C_writeNibble(LCD_Function_SET_4BIT);	//0010 짤림
	LCD_I2C_WriteCmdData(LCD_Function_SET_4BIT);	
	LCD_I2C_WriteCmdData(LCD_Display_Off);	//LCD_Display_Off:0x08
	LCD_I2C_WriteCmdData(LCD_Display_Clear);	//LCD_Display_Clear:0x01
	LCD_I2C_WriteCmdData(LCD_Entry_Mode_Set);	//LCD_Entry_Mode_Set:0x06 (I/D(1): 방향(왼->오))
	LCD_I2C_WriteCmdData(LCD_Display_On);	//LCD_Display_On:0x0C
	LCD_I2C_BackLightOn();
}

void LCD_I2C_BackLightOn(){
	lcdControlData |= (1<<LCD_BACKLIGHT);
	LCD_sendToI2C(LCD_SLA_W,lcdControlData);
}
void LCD_I2C_BackLightOff(){
	lcdControlData &= ~(1<<LCD_BACKLIGHT);
	LCD_sendToI2C(LCD_SLA_W,lcdControlData);
}
void LCD_sendToI2C(uint8_t sla_w,uint8_t data){
	I2C_txByte(sla_w,data);
}

void LCD_I2C_writeNibble(uint8_t data){
	LCD_I2C_enableHigh();
	data = ((lcdControlData& 0x0f)|(data & 0xf0)); //상위 4bit를 data로 변경
	LCD_sendToI2C(LCD_SLA_W, data);
	LCD_I2C_enableLow();
}

void LCD_I2C_cmdMode(){
	//RS -> LOW (0)
	lcdControlData &= ~(1<<LCD_RS);
	LCD_sendToI2C(LCD_SLA_W,lcdControlData);
}
void LCD_I2C_charMode(){
	//RS -> HIGH (1)
	lcdControlData |= (1<<LCD_RS);
	LCD_sendToI2C(LCD_SLA_W,lcdControlData);	//gpio_writeControlData(lcdControlData);
}
void LCD_I2C_writeMode(){
	//RW -> LOW (0)
	lcdControlData &= ~(1<<LCD_RW);
	LCD_sendToI2C(LCD_SLA_W,lcdControlData);	//gpio_writeControlData(lcdControlData);
}
void LCD_I2C_enableHigh(){
	//enable -> HIGH (1)
	lcdControlData |= (1<<LCD_E);
	LCD_sendToI2C(LCD_SLA_W,lcdControlData);	//gpio_writeControlData(lcdControlData);
	_delay_ms(1);
}
void LCD_I2C_writeByte(uint8_t data){
	//8bit 전달 : gpio_writeData(data);
	//4bit -> 4개씩 2번 송신
	LCD_I2C_writeNibble(data);
	data<<= 4;
	LCD_I2C_writeNibble(data);
}
void LCD_I2C_enableLow(){
	//enable -> LOW (0)
	lcdControlData &= ~(1<<LCD_E);
	LCD_sendToI2C(LCD_SLA_W,lcdControlData);	//gpio_writeControlData(lcdControlData);
	_delay_ms(1);
}

// LCD Write Mode(Instruction),명령어 쓰기 동작
void LCD_I2C_WriteCmdData(uint8_t data){
	LCD_I2C_cmdMode();
	LCD_I2C_writeMode();
	//LCD_enableHigh();
	LCD_I2C_writeByte(data);
	//LCD_enableLow();
}

// LCD Write Mode(Data), 문자 쓰기 동작
void LCD_I2C_WriteCharData(uint8_t data){
	LCD_I2C_charMode();
	LCD_I2C_writeMode();
	//LCD_enableHigh();
	LCD_I2C_writeByte(data);
	//LCD_enableLow();
}

void LCD_I2C_writeString(char *str){
	for(int i = 0; str[i] ; i++){
		LCD_I2C_WriteCharData(str[i]);
	}
}
void LCD_I2C_gotoXY(uint8_t row, uint8_t col){
	col %= 16;
	row %= 2;
	uint8_t lcdRegisterAddress =(0x40 *row ) +col;
	uint8_t command = 0x80 + lcdRegisterAddress;
	LCD_I2C_WriteCmdData(command);
}
void LCD_I2C_writeStringXY(uint8_t row, uint8_t col,char *str){
	LCD_I2C_gotoXY(row,col);
	LCD_I2C_writeString(str);
}
void LCD_I2C_displayClear(){
	LCD_I2C_WriteCmdData(LCD_Display_Clear);
}
void LCD_I2C_displayOff(){
	LCD_I2C_WriteCmdData(LCD_Display_Off);
}

