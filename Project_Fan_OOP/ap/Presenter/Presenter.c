#include "Presenter.h"

char buff_NAME[30];
char buff_MODE[30];
char buff_TIMER[30];
char buff_POWER[30];
uint8_t DeviceState, ModeState, ManualModeState, TimerModeState;
uint8_t ButttonFlag, UltraSonicOnOffFlag;

void presenter_init(){
	FND_init();
	LCD_init(); //GPIO
	LCD_I2C_init();
	Buzzer_init();
}

void Button_buzzer(){
	ButttonFlag =  Model_getbuttonFlagData();
	static uint32_t prevTime = 0;
	uint32_t curTime = getTick();
	if(ButttonFlag==On){
		Buzzer_soundOn();
		Buzzer_makeduty(2);
		if(curTime-prevTime < 300) return;		//0.3초동안 소리
		prevTime = curTime;
		ButttonFlag = Off;
		Model_setbuttonFlagData(ButttonFlag);
	}
	if(ButttonFlag==Off){
		prevTime = curTime;
		Buzzer_soundOff();
	}
}

void Fan_presenter()
{
	uint16_t TimeClockFND = Model_getTimeClockDataFND();	//FND
	uint8_t TimeClockhour = Model_getTimeClockDatahour();	//hour
	uint8_t TimeClockmin = Model_getTimeClockDatamin();		//min
	uint8_t TimeClocksec = Model_getTimeClockDatasec();		//sec
	DeviceState = Model_getdeviceStateData();	//ON,OFF
	UltraSonicOnOffFlag = Model_getUltraSonicOnOffFlagData(); //초음파 센서 On, Off
	
	Button_buzzer();
	
	if(UltraSonicOnOffFlag == NONAPPLY)
	{
		if(strcmp(buff_NAME, "Smart IOT Fan"))
		{
			LCD_I2C_displayClear();
			LCD_displayClear();
		}
		sprintf(buff_NAME,"Smart IOT Fan");	//LCD_I2C 첫번째 줄 제품명
		LCD_I2C_writeStringXY(0,1,buff_NAME);
		FND_setFndData(TimeClockFND);	//FND 출력
	}
	if(UltraSonicOnOffFlag == APPLY)
	{
		if(strcmp(buff_NAME, "*Smart IOT Fan*"))
		{
			LCD_I2C_displayClear();
			LCD_displayClear();
		}
		sprintf(buff_NAME,"*Smart IOT Fan*");	//LCD_I2C 첫번째 줄 제품명
		LCD_I2C_writeStringXY(0,1,buff_NAME);
		FND_setFndData(TimeClockFND);	//FND 출력
	}
	
	switch(DeviceState){
		case OFFState:
		if(strcmp(buff_MODE,"OFF"))		//출력이 OFF와 다를때 LCD Clear
		{
			LCD_I2C_displayClear();
			LCD_displayClear();
		}
		sprintf(buff_MODE,"OFF");
		LCD_I2C_writeStringXY(1,7,buff_MODE);	//LCD_I2C 두번째 줄 OFF-Mode(ON)
		LED_Alloff(&LED_PORT);
		break;
		
		case OnState:
		sprintf(buff_TIMER,"%02d:%02d:%02d",TimeClockhour,TimeClockmin,TimeClocksec);	//LCD 두번째 줄 Timer시간
		LCD_writeStringXY(1,4,buff_TIMER);
		Fan_Mode_presenter();
		break;
	}
}

void Fan_Mode_presenter()
{
	uint16_t TimeClockFND = Model_getTimeClockDataFND();	//FND
	uint8_t TimeClockhour = Model_getTimeClockDatahour();	//hour
	uint8_t TimeClockmin = Model_getTimeClockDatamin();		//min
	uint8_t TimeClocksec = Model_getTimeClockDatasec();		//sec
	DeviceState = Model_getdeviceStateData();	//ON,OFF
	
	ModeState = Model_getmodeStateData();	//Mode
	
	switch(ModeState)
	{
		case ManualState:
		if(strcmp(buff_MODE,"Manual"))	//출력이 Manual 다를때 LCD Clear
		{
			LCD_I2C_displayClear();
		}
		sprintf(buff_MODE,"Manual");
		LCD_I2C_writeStringXY(1,5,buff_MODE);
		Fan_ManualMode_presenter();
		break;
		
		case AutoState:
		if(strcmp(buff_MODE,"Auto"))	//출력이 Auto와 다를때 LCD Clear
		{
			LCD_I2C_displayClear();
			LCD_displayClear();
		}
		sprintf(buff_MODE,"Auto");
		LCD_I2C_writeStringXY(1,6,buff_MODE);
		break;
		
		case TimerState:
		if(strcmp(buff_MODE,"Timer"))	//출력이 Timer와 다를때 LCD Clear
		{
			LCD_I2C_displayClear();
			LCD_displayClear();
		}
		sprintf(buff_MODE,"Timer");
		LCD_I2C_writeStringXY(1,5,buff_MODE);
		break;
		
		case WarningState:
		if(strcmp(buff_MODE,"Warning"))	//출력이 Auto와 다를때 LCD Clear
		{
			LCD_I2C_displayClear();
			LCD_displayClear();
		}
		sprintf(buff_MODE,"Warning");
		LCD_I2C_writeStringXY(1,6,buff_MODE);
		break;
	}
}
void Fan_ManualMode_presenter()
{
	ManualModeState = Model_getmanualModeStateData();
	
	switch(ManualModeState)
	{
		case SlowState:
		if(strcmp(buff_POWER,"Slow Speed"))
		{
			LCD_displayClear();
		}
		sprintf(buff_POWER,"Slow Speed");
		LCD_writeStringXY(0,3,buff_POWER);
		break;
		
		case MiddleState:
		if(strcmp(buff_POWER,"Middle Speed"))
		{
			LCD_displayClear();
		}
		sprintf(buff_POWER,"Middle Speed");
		LCD_writeStringXY(0,2,buff_POWER);
		break;
		
		case FastState:
		if(strcmp(buff_POWER,"Fast Speed"))
		{
			LCD_displayClear();
		}
		sprintf(buff_POWER,"Fast Speed");
		LCD_writeStringXY(0,3,buff_POWER);
		break;
	}
}

void Fan_UART0_presenter()
{
	DeviceState = Model_getdeviceStateData();
	ModeState = Model_getmodeStateData();
	ManualModeState = Model_getmanualModeStateData();
	TimerModeState = Model_gettimermodeStateData();
	
	char * Rxstring = UART0_getRxBuff();
	
	if(!(strcmp(Rxstring,"Smart IOT Fan ON\n"))){
		if(DeviceState==OnState){
			printf("Smart IOT Fan ON\n");
		}
		return;
	}
	if(!(strcmp(Rxstring,"Smart IOT Fan OFF\n"))){
		if(DeviceState==OFFState){
			printf("Smart IOT Fan OFF\n");
		}
		return;
	}
	
	if(!(strcmp(Rxstring,"Manual Mode Slow Speed\n"))){
		if(ManualModeState == SlowState){
			printf("Manual Mode Slow Speed\n");
		}
		return;
	}
	if(!(strcmp(Rxstring,"Manual Mode Middle Speed\n"))){
		if(ManualModeState == MiddleState){
			printf("Manual Mode Middle Speed\n");
		}
		return;
	}
	if(!(strcmp(Rxstring,"Manual Mode Fast Speed\n"))){
		if(ManualModeState == FastState){
			printf("Manual Mode Fast Speed\n");
		}
		return;
	}
	if(!(strcmp(Rxstring,"Auto Mode\n"))){
		if(ModeState == AutoState){
			printf("Auto Mode\n");
		}
		return;
	}
	if(!(strcmp(Rxstring,"Timer Mode\n"))){
		if((ModeState == TimerState)){
			printf("Timer Mode\n");		
		}
		return;
	}
	if(!(strcmp(Rxstring,"Timer Thirty Min Up\n"))){
		if((TimerModeState == minUp))
		{
			printf("Timer Thirty Min Up\n");	
		}
		return;
	}
}
