#ifndef MODEL_ULTRASONICSTATE_H_
#define MODEL_ULTRASONICSTATE_H_

#include <avr/io.h>

#include "../Model/Model_ModeState.h"

enum {StandBy, Detecting};
enum {APPLY, NONAPPLY};
	
#define LED_WARING_YELLOW		5
#define LED_WARING_RED			6
#define LED_GOOD_GREEN			4

#define LED_DDR					DDRD
#define LED_PORT				PORTD

uint8_t Model_getUltraSonicFlagData();
void Model_setUltraSonicFlagData(uint8_t data);
uint8_t Model_getUltraSonicOnOffFlagData();
void Model_setUltraSonicOnOffFlagData(uint8_t data);



#endif /* MODEL_ULTRASONICSTATE_H_ */