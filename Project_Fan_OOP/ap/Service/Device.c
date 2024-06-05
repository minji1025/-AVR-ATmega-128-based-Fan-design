#include "Device.h"

void Fan_Sevice_init(){
	Motor_init();
	Fan_ultrasonic_init();
}

void Fan_device_Sevice()
{
	
	uint8_t deviceState;
	deviceState = Model_getdeviceStateData();
	
	switch(deviceState)
	{
		case OFFState:	
		Fan_reset();
		break;
		
		case OnState:
		Fan_ultrasonic_distance();
		Motor_On();
		Fan_Mode_Sevice();
		break;
	}
}

void Fan_reset()
{
	Motor_Off();
	Model_setmodeStateData(ManualState);		//ModeState = ManualState;
	Model_setmanualModeStateData(SlowState);	//ManualModeState = SlowState;
	Model_settimermodeStateData(Setting);		//TimerModeState = Setting;
	Model_settimermodeFlagData(Stop);			//TimerModeFlag = Stop;
	Time_init();	//TimeClockDatahour = 0,TimeClockDatamin = 0, TimeClockDatasec = 0, TimeClockDataFND = 0
}