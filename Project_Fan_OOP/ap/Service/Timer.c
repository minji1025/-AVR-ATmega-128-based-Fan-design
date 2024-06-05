#include "Timer.h"

uint16_t milisec;
uint8_t sec,TimeClocksec;
uint8_t min,TimeClockmin;
uint8_t hour,TimeClockhour;

void Time_init(){
	TimeClocksec = 0;
	TimeClockmin = 0;
	TimeClockhour =0;
	milisec = 0;
	sec = 0;
	min = 0;
	hour = 0;
	Model_settimermodeFlagData(Stop); //timermodeFlag = Stop으로 초기화
	Model_setTimeClockData(0,0,0);	//TimeClockDatahour = 0,TimeClockDatamin = 0, TimeClockDatasec = 0로 초기화
	Model_setTimeClockDataFND(0);	//TimeClockDataFND = 0로 초기화
}

void Fan_TimerMode_Sevice()
{
	uint8_t TimerModeState;
	uint16_t TimeClockFND;
	
	TimerModeState = Model_gettimermodeStateData();
	
	switch(TimerModeState)
	{
		case minUp:
		TimeClockmin = (TimeClockmin+30)%60;	//30분씩 증가
		if(TimeClockmin < 30)
		{
			TimeClockhour = (TimeClockhour+1)%24;
		}
		TimeClockFND = (TimeClockmin*100)+TimeClocksec;		//분:초 삽입
		Model_setTimeClockData(TimeClockhour,TimeClockmin,TimeClocksec); //LCD 출력을 위한 Model
		Model_setTimeClockDataFND(TimeClockFND);	//FND 출력을 위한 Model
		break;
	}
}

void timercounter()
{
	uint16_t TimeClockFND;

	if(((TimeClockhour-hour)==0)&&((TimeClockmin-min)==0)&&((TimeClocksec-sec)==0)){	//0시0분0초 = OFF
		Model_setdeviceStateData(OFFState);
		return;
	}
	if((TimeClockmin<= 0)&&(TimeClockhour)){		//시간이 있고 0분보다 작아지면
		TimeClockmin = 59;
		TimeClockhour--;
		return;
	}
	if(TimeClocksec<= 0){	//0초보다 작아지면
		TimeClocksec = 59;
		TimeClockmin--;
		return;
	}
	if(TimeClockhour>7)		//8시간보다 커지면 타이머 종료 
	{
		Model_settimermodeFlagData(Stop);
		TimeClocksec = 0;
		TimeClockmin = 0;
		TimeClockhour =0;
		hour = 0;
		min = 0;
		sec = 0;
		return;
	}
	if(milisec <= 500)
	{
		FND_colonOn();
	}
	else
	{
		FND_colonOff();
	}
	TimeClockFND = ((TimeClockmin-min)*100)+(TimeClocksec-sec);	//분:초 삽입
	Model_setTimeClockData((TimeClockhour-hour),(TimeClockmin-min),(TimeClocksec-sec));	//LCD 출력을 위한 Model
	Model_setTimeClockDataFND(TimeClockFND);	//FND 출력을 위한 Model
}

void timer_incmilisec()
{
	uint8_t TimerModeFlag;
	TimerModeFlag = Model_gettimermodeFlagData();
	if(TimerModeFlag == Start)	//minUp이 된 순간
	{
		milisec = (milisec+1)%1000; // 0 ~ 999
		if(milisec) return;         //milisec:1~999 일때 return
		sec = (sec+1)%60;         //milisec:0 일때 sec 증가
		if(sec) return;            //sec:1~60 일때 return
		min = (min+1)%60;         //sec:0 일때 min 증가
		if(min) return;            //min:1~60 일때 return
		hour = (hour+1)%24;         //min:0 일때 hour 증가
	}
}