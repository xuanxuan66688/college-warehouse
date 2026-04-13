#include "element_handle.h"
void element_one(uint8_t lastchar)
{
	if(lastchar==49)
		{
			Turn_Left();
		}
	else if(lastchar==50)
		{
			HAL_GPIO_WritePin(GPIOB,LED_Pin,GPIO_PIN_SET);
			Turn_Right();
		}
}
