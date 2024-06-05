# AVR(ATmega128) based Fan Design
## Design Environment
 - MCU ATMEGA 128A(JMOD - 128 - 1 Module)
<img src="https://github.com/minji1025/AVR_ATmega128_based_Fan_design/assets/163821451/5a67cdcf-8e2b-4dcd-b401-34577b32f2f1" width="20%" height="30%">

- Tool[Atmel Studio] Visual Studio 기반 C
<img src="https://github.com/minji1025/AVR_ATmega128_based_Fan_design/assets/163821451/0d2291a2-6d16-45ae-88e6-7385e00be5e3" width="20%" height="30%">

## 사용자 요구사항
1. Mode - Auto, Manual(slow, Middle, Fast), Timer
    -> 속도 조정 가능
2. FND - Timer 동작 시 잔여시간 표시
3. LCD - 제품명, Mode, 풍량, Timer 잔여시간 등을 표시
4. UltraSonic - 어린이 사용자를 위하여 일정 거리 이하 일때 OFF
5. Buzzer - Button을 눌를 때 소리 출력
6. UART -PC에서 선풍기의 Mode,풍량을 제어
   
## FSM
![image](https://github.com/minji1025/AVR_ATmega128_based_Fan_design/assets/163821451/b999f382-a978-40ff-a1e7-5b1d801391ef)

## 동작 영상
<img src="https://github.com/minji1025/AVR_ATmega128_based_Fan_design/assets/163821451/82606b28-b32d-4a5e-a1fa-6906a6cfa106" width="20%" height="30%">

1. Mode 변경 : OFF -> ON -> Manual Mode (Slow -> Middle -> Fast) -> Auto Mode
2. Timer reset : 8시간 이상 시 Timer 초기화
3. Timer OFF : Timer 시간이 0시 0분 0초가 되면 FAN OFF
4. Ultra Sonic FAN OFF : 30 이상 시 초록불&FAN ON, 10~30 시 노란불&FAN ON, 10이하시 빨간불&FAN OFF
5. Ultra Sonic OFF : 거리 상관 없이 동작
6. UART : Button과 동일하게 동작
