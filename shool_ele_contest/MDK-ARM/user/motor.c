#include "motor.h"
/**
 * @brief 电机方向控制函数
 * @param wheel 选择电机 0:左电机 1:右电机
 * @param dir  方向选择 0:正转 1:反转
 * @retval 无
 */
void set_dir(bool wheel,bool dir)
{
	if(wheel==0)
	{
		if(dir==0)
		{
			//设置电机方向
			HAL_GPIO_WritePin(GPIOA,AIN1_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA,AIN2_Pin,GPIO_PIN_RESET);
		}
		else
		{
			//设置电机方向
			HAL_GPIO_WritePin(GPIOA,AIN1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA,AIN2_Pin,GPIO_PIN_SET);
		}
	}

if(wheel==1)
{
    if(dir==0)
    {
        HAL_GPIO_WritePin(GPIOB,BIN1_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB,BIN2_Pin,GPIO_PIN_RESET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB,BIN1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB,BIN2_Pin,GPIO_PIN_SET);
    }
}
}
/**
 * @brief 电机速度设置函数
 * @param speed  电机速度值（正负表示方向，绝对值表示大小）
 * @param wheel  选择电机 0:左电机 1:右电机
 * @retval 无
 */
void set_speed(int speed,bool wheel)
{
	//将速度转化为占空比
	int duty=speed*100;
	if(wheel==0)
	{
		if(speed>=0)
		{
			set_dir(0,0);
			//设置PWM
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,duty);
		}
		else
		{
			set_dir(0,1);
			//设置PWM
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,-duty);
		}
		}
	if(wheel==1)
	{
		if(speed>=0)
		{
			set_dir(1,1);
			//设置PWM
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,duty);
		}
		else
		{
			set_dir(1,0);
			//设置PWM
			__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,-duty);
		}
	}
}