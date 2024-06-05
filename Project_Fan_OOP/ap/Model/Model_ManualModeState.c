#include "Model_ManualModeState.h"

uint8_t manualModeStateData;	//SlowState,MiddleState,FastState 구분

uint8_t Model_getmanualModeStateData()
{
	return manualModeStateData;
}

void Model_setmanualModeStateData(uint8_t data)
{
	manualModeStateData = data;
}