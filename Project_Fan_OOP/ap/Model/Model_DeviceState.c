#include "Model_DeviceState.h"

uint8_t deviceStateData;	//OFFState,OnState

uint8_t Model_getdeviceStateData()
{
	return deviceStateData;
}

void Model_setdeviceStateData(uint8_t data)
{
	deviceStateData = data;
}