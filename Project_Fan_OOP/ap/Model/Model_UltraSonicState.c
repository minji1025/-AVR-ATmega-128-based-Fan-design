#include "Model_UltraSonicState.h"

uint8_t ultraSonicFlagData, UltraSonicOnOffFlag;		//Detecting (감지중) StandBy (준비중)

uint8_t Model_getUltraSonicFlagData()
{
	return ultraSonicFlagData;
}

void Model_setUltraSonicFlagData(uint8_t data)
{
	ultraSonicFlagData = data;
}

uint8_t Model_getUltraSonicOnOffFlagData()
{
	return UltraSonicOnOffFlag;
}

void Model_setUltraSonicOnOffFlagData(uint8_t data)
{
	UltraSonicOnOffFlag = data;
}