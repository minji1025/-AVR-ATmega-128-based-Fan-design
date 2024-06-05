#ifndef MODEL_BUTTONFLAG_H_
#define MODEL_BUTTONFLAG_H_

#include <avr/io.h>

enum{On,Off};
	
#define Button_DDR			DDRA
#define Button_PIN			PINA

uint8_t Model_getbuttonFlagData();
void Model_setbuttonFlagData(uint8_t data);



#endif /* MODEL_BUTTONFLAG_H_ */