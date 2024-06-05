#ifndef LISTENER_H_
#define LISTENER_H_

#include <avr/io.h>
#include <stdio.h>
#include <string.h>

#include "../../Driver/Button/Button.h"
#include "../../Driver/Buzzer/Buzzer.h"
#include "../../peripheral/UART0/UART0.h"
#include "../Model/Model_DeviceState.h"	
#include "../Model/Model_ManualModeState.h"
#include "../Model/Model_ModeState.h"
#include "../Model/Model_TimerModeState.h"
#include "../Model/Model_UltraSonicState.h"
#include "../Model/Model_ButtonFlag.h"
#include "../Service/Ultrasonic.h"

void Listener_Button_init();
void Listener_Button_eventCheck();
void Fan_Mode_Button_eventCheck();
void Fan_ManualMode_Button_eventCheck();
void Fan_TimerMode_Button_eventCheck();

void Listener_UART0_init();
void Listener_UART0_eventCheck();
#endif /* LISTENER_H_ */