
#ifndef APMAIN_H_
#define APMAIN_H_
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>

#include "../ap/Service/Device.h"
#include "../ap/Service/Timer.h"
#include "../ap/Listener/Listener.h"
#include "../ap/Presenter/Presenter.h"
#include "../peripheral/TIM/TIM.h"
#include "../peripheral/UART0/UART0.h"
#include "../Driver/FND/FND.h"
#include "../Driver/Ultrasonic/Ultrasonic.h"

void ap_init();
void ap_excute();







#endif /* APMAIN_H_ */