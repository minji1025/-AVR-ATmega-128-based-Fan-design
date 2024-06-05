#include "Model_TimerModeState.h"

uint8_t timerModeStateData;		//Setting,minUP(30분 증가)
uint8_t timerModeFlagData;		//Start(timer 시작),Stop

uint8_t Model_gettimermodeStateData()
{
	return timerModeStateData;
}

void Model_settimermodeStateData(uint8_t data)
{
	timerModeStateData = data;
}

uint8_t Model_gettimermodeFlagData()
{
	return timerModeFlagData;
}

void Model_settimermodeFlagData(uint8_t data)
{
	timerModeFlagData = data;
}