#include "Buzzer.h"

void Buzzer_init()
{
	//PWM, Timer/Counter 3
	//PreScaler 1/64
	//TOP ICR3
	//DUTY CYCLE OCR3
	//1kHz의 주파수 --> Top 값이 250이 되어야 1ms --> 1kHz를 정확히 주파수로 나타낼 수 있다.
	//Non-inverting Mode
	
	Gpio_initPin(&Buzzer_DDR, Buzzer_DDR_NUM, OUTPUT); //Buzzer_DDR |= (1<<Buzzer_DDR_NUM);
	TCCR0 |= ((1<<CS02)|(0<<CS01)|(0<<CS00));
	TCCR0 |= ((1<<WGM01)|(1<<WGM00)); //FAST PWM MODE 설정 위, 아래 줄 두줄해서
	
}

void Buzzer_makeduty(uint8_t duty)
{
	//   if(herz < 100) herz = 100;
	//   else if(herz >8000) herz = 8000;
	//   Buzzer_ICR = (250000/herz) - 1; //herz가 저만큼
	Buzzer_OCR = 255/duty; //duty 비 50% --> ICR이 없어 TOP, BOTTOM 고정이고 이에 따라 herz값은 OCR(기준선)을 변경하는 정도용 그에 따른 듀티비 조정, 고정 freq = 1kHz
}

void Buzzer_soundOn() //켜지는 것
{
	TCCR0 |= ((1<<COM01)|(0<<COM00));
}

void Buzzer_soundOff() // 꺼지는 것
{
	TCCR0 &= ~((1<<COM01)|(1<<COM00));
}