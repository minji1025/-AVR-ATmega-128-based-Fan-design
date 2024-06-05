#ifndef MODE_H_
#define MODE_H_


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../Model/Model_ModeState.h"
#include "../Model/Model_UltraSonicState.h"
#include "../../Driver/Motor/Motor.h"
#include "AutoMode.h"
#include "Manual.h"
#include "Timer.h"

void Fan_Mode_Sevice();




#endif /* MODE_H_ */