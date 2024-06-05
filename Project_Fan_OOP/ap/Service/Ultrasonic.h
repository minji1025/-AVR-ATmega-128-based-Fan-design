#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "../../Driver/Ultrasonic/Ultrasonic.h"
#include "../../Driver/LED/LED.h"
#include "../../common/TimeTick/timeTick.h"
#include "../Model/Model_ModeState.h"
#include "../Model/Model_UltraSonicState.h"


#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

void Fan_ultrasonic_init();
void Fan_ultrasonic_distance();

#endif /* ULTRASONIC_H_ */