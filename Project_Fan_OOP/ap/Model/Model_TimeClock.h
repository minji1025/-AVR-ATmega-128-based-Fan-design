#ifndef MODEL_TIMECLOCK_H_
#define MODEL_TIMECLOCK_H_

#include <avr/io.h>

uint8_t Model_getTimeClockDatahour();
uint8_t Model_getTimeClockDatamin();
uint8_t Model_getTimeClockDatasec();
uint16_t Model_getTimeClockDataFND();
void Model_setTimeClockData(uint8_t TimeClockhour, uint8_t TimeClockmin,uint8_t TimeClocksec);
void Model_setTimeClockDataFND(uint16_t TimeClockFND);

#endif /* MODEL_TIMECLOCK_H_ */