#include "Buzzer.h"
void Buzzer(void)
{
	HAL_GPIO_WritePin(GPIOB,Buzzer_Pin,GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(GPIOB,Buzzer_Pin,GPIO_PIN_RESET);
}