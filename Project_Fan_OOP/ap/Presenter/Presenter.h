#ifndef PRESENTER_H_
#define PRESENTER_H_
#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#include "../../Driver/FND/FND.h"
#include "../../Driver/LCD_GPIO/LCD_GPIO.h"
#include "../../Driver/LCD_I2C/LCD_I2C.h"
#include "../../Driver/LED/LED.h"
#include "../../Driver/Buzzer/Buzzer.h"
#include "../../peripheral/UART0/UART0.h"
#include "../Model/Model_DeviceState.h"
#include "../Model/Model_ModeState.h"
#include "../Model/Model_ManualModeState.h"
#include "../Model/Model_TimerModeState.h"
#include "../Model/Model_TimeClock.h"
#include "../Model/Model_UltraSonicState.h"
#include "../Model/Model_ButtonFlag.h"
#include "../../common/TimeTick/timeTick.h"

void presenter_init();
void Fan_presenter();
void Fan_Mode_presenter();
void Fan_ManualMode_presenter();
void Fan_UART0_presenter();

#endif /* PRESENTER_H_ */