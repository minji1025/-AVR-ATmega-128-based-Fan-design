#include "Model_ModeState.h"

uint8_t modeStateData;	//ManualState,AutoState,TimerState 구분

uint8_t Model_getmodeStateData()
{
	return modeStateData;
}

void Model_setmodeStateData(uint8_t data)
{
	modeStateData = data;
}