#include "Model_TimeClock.h"

uint8_t TimeClockDatahour,TimeClockDatamin,TimeClockDatasec;	//LCD출력을 위한 시간
uint16_t TimeClockDataFND;		//FND출력을 위한 시간

uint8_t Model_getTimeClockDatahour()
{
	return TimeClockDatahour;
}
uint8_t Model_getTimeClockDatamin()
{
	return TimeClockDatamin;
}
uint8_t Model_getTimeClockDatasec()
{
	return TimeClockDatasec;
}

uint16_t Model_getTimeClockDataFND()
{
	return TimeClockDataFND;
}

void Model_setTimeClockData(uint8_t TimeClockhour, uint8_t TimeClockmin,uint8_t TimeClocksec)
{	
	TimeClockDatahour = TimeClockhour;
	TimeClockDatamin = TimeClockmin;
	TimeClockDatasec = TimeClocksec;
}

void Model_setTimeClockDataFND(uint16_t TimeClockFND)
{
	TimeClockDataFND = TimeClockFND;
}