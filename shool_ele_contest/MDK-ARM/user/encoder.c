#include "encoder.h"
/**
  * @brief  编码器初始化函数
  * @param  无
  * @retval 无
  */
void encoder_init()
{
	HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
	HAL_TIM_Encoder_Start(&htim8,TIM_CHANNEL_ALL);
}
/**
  * @brief  获取编码器速度值
  * @param  无
  * @retval Actual_Speed 编码器采集到的速度值
  */
int16_t get_speed_0(void)
{
	int16_t Actual_Speed_1;
	Actual_Speed_1=__HAL_TIM_GET_COUNTER(&htim3);
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	//溢出处理
	if(Actual_Speed_1 >  10000) Actual_Speed_1 -= 20000;
	if(Actual_Speed_1 < -10000) Actual_Speed_1 += 20000;
	return Actual_Speed_1;
}
int16_t get_speed_1(void)
{
	int16_t Actual_Speed_2;
	Actual_Speed_2=__HAL_TIM_GET_COUNTER(&htim8);
	__HAL_TIM_SET_COUNTER(&htim8, 0);
	//溢出处理
	if(Actual_Speed_2 >  10000) Actual_Speed_2 -= 20000;
	if(Actual_Speed_2 < -10000) Actual_Speed_2 += 20000;
	return Actual_Speed_2;
}