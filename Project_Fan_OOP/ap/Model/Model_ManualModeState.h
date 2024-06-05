#ifndef MODEL_MANUALMODESTATE_H_
#define MODEL_MANUALMODESTATE_H_


#include <avr/io.h>

enum{SlowState,MiddleState,FastState};


uint8_t Model_getmanualModeStateData();
void Model_setmanualModeStateData(uint8_t data);
#endif /* MODEL_MANUALMODESTATE_H_ */