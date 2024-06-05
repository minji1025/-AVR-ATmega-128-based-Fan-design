#ifndef MODEL_MODESTATE_H_
#define MODEL_MODESTATE_H_


#include <avr/io.h>


enum{ManualState,AutoState,TimerState,WarningState};


uint8_t Model_getmodeStateData();
void Model_setmodeStateData(uint8_t data);

#endif /* MODEL_MODESTATE_H_ */