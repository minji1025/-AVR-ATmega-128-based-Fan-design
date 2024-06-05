#include "AutoMode.h"

static uint32_t prevTime = 0;
uint8_t i = 2;
uint32_t curTime;

void Fan_AutoMode_Service()
{
	curTime = getTick();
	Motor_makeHerzDuty(1000,(0.5*i));
	if(curTime-prevTime < 1000) return;		//1초마다 세기 변화
	prevTime = curTime;
	i++;
	if(i>8) i = 2;
}