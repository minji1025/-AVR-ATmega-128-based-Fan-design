#ifndef AUTOMODE_H_
#define AUTOMODE_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "../../common/TimeTick/timeTick.h"
#include "../../Driver/Motor/Motor.h"

void Fan_AutoMode_Service();

#endif /* AUTOMODE_H_ */