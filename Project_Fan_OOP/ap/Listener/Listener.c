#include "Listener.h"

button_t btnOnOff, btnManual, btnAuto, btnTimer;
uint8_t DeviceState, ModeState, ManualModeState, TimerModeState, TimerModeFlag;
uint8_t ButttonFlag, UltraSonicOnOffFlag;

void Listener_Button_init()
{
	Button_init(&btnOnOff,&Button_DDR,&Button_PIN,0);		//on,off 0번
	Button_init(&btnManual,&Button_DDR,&Button_PIN,1);		//Manual (Slow->Middle->Fast)
	Button_init(&btnAuto,&Button_DDR,&Button_PIN,2);		//Auto
	Button_init(&btnTimer,&Button_DDR,&Button_PIN,3);		//Timer (30분++,자동으로 감소)
	Model_setdeviceStateData(OFFState);		//DeviceState = OFFState
	Model_setmodeStateData(ManualState);		//ModeState = ManualState
	Model_setmanualModeStateData(SlowState);	//ManualModeState = SlowState
	Model_settimermodeStateData(Setting);		//TimerModeState = Setting
	Model_settimermodeFlagData(Stop);	//TimerModeFlag = Stop
	Model_setUltraSonicOnOffFlagData(NONAPPLY); // 초음파모드 초기 OFF
	Model_setbuttonFlagData(Off); // ButttonFlag = OFF
}



void Listener_Button_eventCheck()
{
	DeviceState = Model_getdeviceStateData();
	UltraSonicOnOffFlag = Model_getUltraSonicOnOffFlagData();
	switch(DeviceState)
	{
		case OFFState :
		if(Button_GetState(&btnOnOff)==ACT_ON)
		{
			DeviceState=OnState;
			Model_setdeviceStateData(DeviceState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
			UltraSonicOnOffFlag = APPLY;
			Model_setUltraSonicOnOffFlagData(UltraSonicOnOffFlag);
		}
		break;
		
		case OnState :
		Fan_Mode_Button_eventCheck();	//Manual,Auto,Timer Mode eventCheck
		if(Button_GetState(&btnOnOff)==ACT_ON)
		{
			DeviceState=OFFState;
			Model_setdeviceStateData(DeviceState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
			UltraSonicOnOffFlag = NONAPPLY;
			Model_setUltraSonicOnOffFlagData(UltraSonicOnOffFlag);
		}
		break;
		
	}
}

void Fan_Mode_Button_eventCheck()
{
	ModeState = Model_getmodeStateData();
	UltraSonicOnOffFlag = Model_getUltraSonicOnOffFlagData();

	switch(ModeState)
	{
		case ManualState:
		Fan_ManualMode_Button_eventCheck();	//slow,middle,fast eventCheck
		if(Button_GetState(&btnAuto) == ACT_ON)
		{
			ModeState = AutoState;
			Model_setmodeStateData(ModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
			UltraSonicOnOffFlag = APPLY;
			Model_setUltraSonicOnOffFlagData(UltraSonicOnOffFlag);
		}
		if(Button_GetState(&btnTimer) == ACT_ON){
			ModeState = TimerState;
			Model_setmodeStateData(ModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		if(Button_GetState(&btnOnOff) == ACT_ON){
			DeviceState = OFFState;
			Model_setdeviceStateData(DeviceState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		break;
		
		case AutoState:
		if(Button_GetState(&btnManual) == ACT_ON)
		{
			ModeState = ManualState;
			Model_setmodeStateData(ModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		if(Button_GetState(&btnTimer) == ACT_ON)
		{
			ModeState = TimerState;
			Model_setmodeStateData(ModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		if(Button_GetState(&btnAuto) == ACT_ON)
		{
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
			UltraSonicOnOffFlag = (UltraSonicOnOffFlag+1)%2;
			Model_setUltraSonicOnOffFlagData(UltraSonicOnOffFlag); // auto 모드에서 한 번 더 누르면 초음파 센서 모드 꺼지도록
		}
		if(Button_GetState(&btnOnOff) == ACT_ON)
		{
			DeviceState = OFFState;
			Model_setdeviceStateData(DeviceState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		break;
		
		case TimerState:
		Fan_TimerMode_Button_eventCheck();		//Timer 시간 설정(setting -> minup ->setting)
		if(Button_GetState(&btnManual) == ACT_ON)
		{
			ModeState = ManualState;
			Model_setmodeStateData(ModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		if(Button_GetState(&btnAuto) == ACT_ON)
		{
			ModeState = AutoState;
			Model_setmodeStateData(ModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
			UltraSonicOnOffFlag = APPLY;
			Model_setUltraSonicOnOffFlagData(UltraSonicOnOffFlag);
		}
		if(Button_GetState(&btnOnOff) == ACT_ON)
		{
			DeviceState = OFFState;
			Model_setdeviceStateData(DeviceState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		break;
	}
}

void Fan_ManualMode_Button_eventCheck()
{	//slow -> middle -> fast 순으로 반복
	ManualModeState = Model_getmanualModeStateData();
	
	switch(ManualModeState){
		case SlowState:
		if(Button_GetState(&btnManual) == ACT_ON)
		{
			ManualModeState = MiddleState;
			Model_setmanualModeStateData(ManualModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		if(Button_GetState(&btnOnOff) == ACT_ON)
		{
			DeviceState=OFFState;
			Model_setdeviceStateData(DeviceState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		break;
		
		case MiddleState:
		if(Button_GetState(&btnManual) == ACT_ON)
		{
			ManualModeState = FastState;
			Model_setmanualModeStateData(ManualModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		if(Button_GetState(&btnOnOff) == ACT_ON)
		{
			DeviceState=OFFState;
			Model_setdeviceStateData(DeviceState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		break;
		
		case FastState:
		if(Button_GetState(&btnManual) == ACT_ON)
		{
			ManualModeState = SlowState;
			Model_setmanualModeStateData(ManualModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		if(Button_GetState(&btnOnOff) == ACT_ON)
		{
			DeviceState=OFFState;
			Model_setdeviceStateData(DeviceState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		break;
	}
}

void Fan_TimerMode_Button_eventCheck()
{
	TimerModeState = Model_gettimermodeStateData();
	
	switch(TimerModeState)
	{
		case Setting:
		if(Button_GetState(&btnTimer)==ACT_ON)
		{
			TimerModeState = minUp;
			Model_settimermodeStateData(TimerModeState);
			ButttonFlag = On;
			Model_setbuttonFlagData(ButttonFlag);
		}
		break;
		
		case minUp:
		TimerModeState = Setting;
		Model_settimermodeStateData(TimerModeState);
		TimerModeFlag = Start;		//timer 시작
		Model_settimermodeFlagData(TimerModeFlag);
		break;
	}
}


void Listener_UART0_init()
{
	UART0_init();
}

void Listener_UART0_eventCheck()
{
	DeviceState = Model_getdeviceStateData();
	ModeState = Model_getmodeStateData();
	ManualModeState = Model_getmanualModeStateData();
	TimerModeState = Model_gettimermodeStateData();
	UltraSonicOnOffFlag = Model_getUltraSonicOnOffFlagData();
	
	if(UART0_getRxFlag()){
		UART0_clearRxFlag();
		char * Rxstring = UART0_getRxBuff();
		
		if(!(strcmp(Rxstring,"Smart IOT Fan ON\n"))){
			DeviceState = OnState;
			Model_setdeviceStateData(DeviceState);
			UltraSonicOnOffFlag = APPLY;
			Model_setUltraSonicOnOffFlagData(UltraSonicOnOffFlag);
			return;
		}
		if(!(strcmp(Rxstring,"Smart IOT Fan OFF\n"))){
			DeviceState = OFFState;
			Model_setdeviceStateData(DeviceState);
			UltraSonicOnOffFlag = NONAPPLY;
			Model_setUltraSonicOnOffFlagData(UltraSonicOnOffFlag);
			return;
		}
		if(!(strcmp(Rxstring,"Manual Mode Slow Speed\n"))){
			ModeState = ManualState;
			ManualModeState = SlowState;
			Model_setmodeStateData(ModeState);
			Model_setmanualModeStateData(ManualModeState);
			return;
		}
		if(!(strcmp(Rxstring,"Manual Mode Middle Speed\n"))){
			ModeState = ManualState;
			ManualModeState = MiddleState;
			Model_setmodeStateData(ModeState);
			Model_setmanualModeStateData(ManualModeState);
			return;
		}
		if(!(strcmp(Rxstring,"Manual Mode Fast Speed\n"))){
			ModeState = ManualState;
			ManualModeState = FastState;
			Model_setmodeStateData(ModeState);
			Model_setmanualModeStateData(ManualModeState);
			return;
		}
		if(!(strcmp(Rxstring,"Auto Mode\n"))){
			ModeState = AutoState;
			Model_setmodeStateData(ModeState);
			UltraSonicOnOffFlag = (UltraSonicOnOffFlag+1)%2;
			Model_setUltraSonicOnOffFlagData(UltraSonicOnOffFlag);
			return;
		}
		if(!(strcmp(Rxstring,"Timer Mode\n"))){
			ModeState = TimerState;
			TimerModeState = Setting;
			Model_setmodeStateData(ModeState);
			Model_settimermodeStateData(TimerModeState);
			return;
		}
		if(!(strcmp(Rxstring,"Timer Thirty Min Up\n"))){
			TimerModeState = minUp;
			Model_settimermodeStateData(TimerModeState);
			return;
		}
	}
}