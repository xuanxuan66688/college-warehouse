#include "tapkey.h"
uint8_t tapkey(void)
{
	//如果拿走电池
	if(HAL_GPIO_ReadPin(TapKey1_GPIO_Port,TapKey1_Pin)==1)
	{
		return 1;
	}
	else if(HAL_GPIO_ReadPin(TapKey2_GPIO_Port,TapKey2_Pin)==1)
	{
		return 1;
	}
	else if(HAL_GPIO_ReadPin(TapKey3_GPIO_Port,TapKey3_Pin)==1)
	{
		return 1;
	}
	return 0;
}