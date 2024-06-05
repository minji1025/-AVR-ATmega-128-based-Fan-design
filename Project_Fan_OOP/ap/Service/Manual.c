#include "Manual.h"

void Fan_ManualMode_Sevice()
{
	uint8_t ManualModeState;
	ManualModeState = Model_getmanualModeStateData();
	
	switch(ManualModeState){
		case SlowState:
		Motor_makeHerzDuty(1000,4.5);
		break;
		
		case MiddleState:
		Motor_makeHerzDuty(1000,3);
		break;
		
		case FastState:
		Motor_makeHerzDuty(1000,1.5);
		break;
	}
}