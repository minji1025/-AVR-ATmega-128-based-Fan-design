#ifndef MODEL_DEVICESTATE_H_
#define MODEL_DEVICESTATE_H_
#include <avr/io.h>

enum{OFFState,OnState};

uint8_t Model_getdeviceStateData();

void Model_setdeviceStateData(uint8_t data);

#endif 