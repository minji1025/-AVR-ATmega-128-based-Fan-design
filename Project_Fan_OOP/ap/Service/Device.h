#ifndef DEVICE_H_
#define DEVICE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../../Driver/Motor/Motor.h"
#include "../Model/Model_DeviceState.h"
#include "../Model/Model_ModeState.h"
#include "../Model/Model_ManualModeState.h"
#include "../Model/Model_TimerModeState.h"
#include "../Model/Model_TimeClock.h"

#include "Ultrasonic.h"
#include "Mode.h"

void Fan_Sevice_init();
void Fan_device_Sevice();
void Fan_reset();
#endif /* DEVICE_H_ */