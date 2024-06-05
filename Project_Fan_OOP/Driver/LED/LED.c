#include "LED.h" // LED.h를 참조하것다.
#include "../../peripheral/GPIO/Gpio.h"

void LED_init(volatile uint8_t *DDR) // 포트도 꼭 PORTD DDRD만 쓰는 것은 아니니까 이것도 선택을 할 수 있도록 하자(포인터), 초기값 설정을 위한 것으로 DDR 몇일지를 선택 그리고 LED니 output
{
	Gpio_initPort(DDR, OUTPUT);
}

void LED_Allon(volatile uint8_t *PORT) // 모든 것이 다 켜지도록 함.
{
	Gpio_writePort(PORT, 0xff);
}

void LED_Alloff(volatile uint8_t *PORT) // 모든 것이 다 꺼지도록 함.
{
	Gpio_writePort(PORT, 0x00);
}

void LED_outPutData(volatile uint8_t *PORT, uint8_t data) // 임의로 지정한 값에 대해서만 켜지도록 함.
{
	Gpio_writePort(PORT, data);
}