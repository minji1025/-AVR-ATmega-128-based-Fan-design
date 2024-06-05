#include "Model_ButtonFlag.h"

uint8_t ButtonFlagData;	//ON,OFF

uint8_t Model_getbuttonFlagData(){
	return ButtonFlagData;
}
void Model_setbuttonFlagData(uint8_t data){
	ButtonFlagData = data;
}