#ifndef LCD_H_
#define LCD_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "../../peripheral/Gpio/Gpio.h"

#define LCD_CONTROL_PORT PORTB
#define LCD_CONTROL_DDR DDRB
#define LCD_DATA_PORT PORTC
#define LCD_DATA_DDR DDRC
#define LCD_RS	5
#define LCD_RW	6
#define LCD_E	7
#define LCD_Function_set	0x38
#define LCD_Display_Off	0x08
#define LCD_Display_Clear 0x01
#define LCD_Entry_Mode_Set	0x06	 //(I/D(1): 방향(왼->오))
#define LCD_Display_On	0x0C
void GPIO_LCD_init();
void LCD_init();

void gpio_writeControlData(uint8_t data);
void gpio_writeData(uint8_t data);

void LCD_cmdMode();
void LCD_charMode();
void LCD_writeMode();
void LCD_enableHigh();
void LCD_writeByte(uint8_t data);
void LCD_enableLow();

// LCD Write Mode(Instruction),명령어 쓰기 동작
void LCD_WriteCmdData(uint8_t data);
// LCD Write Mode(Data), 문자 쓰기 동작
void LCD_WriteCharData(uint8_t data);

void LCD_writeString(char *str);
void LCD_gotoXY(uint8_t row, uint8_t col);
void LCD_writeStringXY(uint8_t row, uint8_t col,char *str);
void LCD_displayClear();
void LCD_displayOff();
#endif /* LCD_H_ */