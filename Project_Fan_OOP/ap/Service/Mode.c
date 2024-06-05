#include "Mode.h"

void Fan_Mode_Sevice()
{
	uint8_t ModeState,TimerModeFlag, UltraSonicFlag;
	ModeState = Model_getmodeStateData();
	TimerModeFlag = Model_gettimermodeFlagData();
	
	switch(ModeState)
	{
		case ManualState:
		if(TimerModeFlag == Start)
		{
			timercounter();
		}
		Fan_ManualMode_Sevice();
		break;
		
		case AutoState:
		if(TimerModeFlag == Start)
		{
			timercounter();
		}
		Fan_AutoMode_Service();
		break;
		
		case TimerState:
		if(TimerModeFlag == Start)
		{
			timercounter();
		}
		Fan_TimerMode_Sevice();
		break;
		
		case WarningState:
		if(TimerModeFlag == Start)
		{
			timercounter();
		}
		Motor_Off();
		Fan_ultrasonic_distance();
		break;
	}
}

