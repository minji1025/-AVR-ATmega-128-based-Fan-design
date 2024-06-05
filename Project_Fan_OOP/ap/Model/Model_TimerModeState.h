#ifndef MODEL_TIMERMODESTATE_H_
#define MODEL_TIMERMODESTATE_H_


#include <avr/io.h>


enum{Setting,minUp};
enum{Start,Stop};

uint8_t Model_gettimermodeStateData();
void Model_settimermodeStateData(uint8_t data);
uint8_t Model_gettimermodeFlagData();
void Model_settimermodeFlagData(uint8_t data);

#endif /* MODEL_TIMERMODESTATE_H_ */