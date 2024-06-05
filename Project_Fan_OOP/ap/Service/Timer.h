#ifndef TIMER_H_
#define TIMER_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>


#include "../Model/Model_TimerModeState.h"
#include "../Model/Model_TimeClock.h"
#include "../Model/Model_DeviceState.h"
#include "../Presenter/Presenter.h"

void Time_init();
void Fan_TimerMode_Sevice();
void timercounter();
void timer_incmilisec();

#endif /* TIMER_H_ */