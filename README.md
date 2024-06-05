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

