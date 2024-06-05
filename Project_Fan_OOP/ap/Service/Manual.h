#ifndef MANUAL_H_
#define MANUAL_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../Model/Model_ManualModeState.h"
#include "../../Driver/Motor/Motor.h"
#include "../Presenter/Presenter.h"

void Fan_ManualMode_Sevice();

#endif /* MANUAL_H_ */