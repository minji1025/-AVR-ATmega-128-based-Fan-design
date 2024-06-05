#ifndef LCD_H_
#define LCD_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "../../peripheral/I2C/I2C.h"

#define LCD_CONTROL_PORT PORTB
#define LCD_CONTROL_DDR DDRB
#define LCD_DATA_PORT PORTC
#define LCD_DATA_DDR DDRC
#define LCD_RS	0
#define LCD_RW	1
#define LCD_E	2
#define LCD_BACKLIGHT 3
#define LCD_SLA	0x27
#define LCD_SLA_W	LCD_SLA<<1
#define LCD_SLA_R	((LCD_SLA<<1)|0x01)

#define LCD_Function_SET_8BIT	0x38
#define LCD_Function_SET_4BIT	0x28
#define LCD_Display_Off	0x08
#define LCD_Display_Clear 0x01
#define LCD_Entry_Mode_Set	0x06	 //(I/D(1): 방향(왼->오))
#define LCD_Display_On	0x0C

void LCD_I2C_init();
void LCD_I2C_BackLightOn();
void LCD_I2C_BackLightOff();
void LCD_sendToI2C(uint8_t sla_w,uint8_t data);
void LCD_I2C_writeNibble(uint8_t data);

void LCD_I2C_cmdMode();
void LCD_I2C_charMode();
void LCD_I2C_writeMode();
void LCD_I2C_enableHigh();
void LCD_I2C_writeByte(uint8_t data);
void LCD_I2C_enableLow();

// LCD Write Mode(Instruction),명령어 쓰기 동작
void LCD_I2C_WriteCmdData(uint8_t data);
// LCD Write Mode(Data), 문자 쓰기 동작
void LCD_I2C_WriteCharData(uint8_t data);

void LCD_writeString(char *str);
void LCD_gotoXY(uint8_t row, uint8_t col);
void LCD_writeStringXY(uint8_t row, uint8_t col,char *str);
void LCD_displayClear();
void LCD_I2C_displayOff();
#endif /* LCD_H_ */