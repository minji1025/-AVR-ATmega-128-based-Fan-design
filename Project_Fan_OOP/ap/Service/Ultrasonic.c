#include "Ultrasonic.h"

uint8_t distance, UltraSonicFlag, UltraSonicOnOffFlag;

void Fan_ultrasonic_init()
{
	Ultrasonic_init();
	distance = 0;
	UltraSonicFlag = Detecting;
	UltraSonicOnOffFlag = NONAPPLY;
	LED_DDR &= ~(1<<LED_GOOD_GREEN)|(1<<LED_WARING_YELLOW)|(1<<LED_WARING_RED);
}

void Fan_ultrasonic_distance()
{
	Ultrasonic_trigger();
	
	//초음파 수신을 기달려 줘야함
	static uint32_t prevTime = 0;
	uint32_t curTime = getTick();
	if(curTime-prevTime < 100) return;
	prevTime = curTime;	
	
	if(Ultrasonic_getComplitFlag())      // 만약 Ultrasonic_getcompltFlag() 함수가 참이면(거리 측정이 완료되면) 실행
	{
		// 거리 계산을 하겠다.
		Ultrasonic_clearComplitFlag();   // 다음에 또 써야되니까 초기화
		distance = Ultrasoinc_getDistance();
		UltraSonicFlag = Model_getUltraSonicFlagData();
		
		if((distance<=10)&&(UltraSonicFlag == Detecting)&&(UltraSonicOnOffFlag == APPLY)) //10 이하시 WarningState로 감.
		{
			Model_setmodeStateData(WarningState);
			UltraSonicFlag = StandBy;
			Model_setUltraSonicFlagData(UltraSonicFlag);
			LED_outPutData(&LED_PORT, 0x40); //빨간불 나옴		
			return;
		}
		if((distance>10)&&(UltraSonicFlag == StandBy)&&(UltraSonicOnOffFlag == APPLY)) // 10 이상이면 다시 재동작
		{
			Model_setmodeStateData(ManualState);
			UltraSonicFlag = Detecting;
			Model_setUltraSonicFlagData(UltraSonicFlag);
			return;
		}
		if((distance>10)&&(distance<=30)&&(UltraSonicFlag == Detecting)&&(UltraSonicOnOffFlag == APPLY)) // 경고등 노란불
		{
			LED_outPutData(&LED_PORT, 0x20);
			return;
		}
		if((distance>30)) // 이땐 정상 가동
		{
			LED_outPutData(&LED_PORT, 0x10);
		}
	}
	
	
}