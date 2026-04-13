#include "Tracking.h"
int8_t Tracking(void)
{
	if(HAL_GPIO_ReadPin(GPIOC,TRA1_Pin)==1
		  &&HAL_GPIO_ReadPin(GPIOC,TRA3_Pin)==1
	  &&HAL_GPIO_ReadPin(GPIOC,TRA2_Pin)==1
	  &&HAL_GPIO_ReadPin(GPIOC,TRA4_Pin)==1)//全黑到十字路口
	  {
		  return 1;
	  }
	  else if(HAL_GPIO_ReadPin(GPIOC,TRA1_Pin)==1
		  &&HAL_GPIO_ReadPin(GPIOC,TRA2_Pin)==1)
	  {
		  return 2;
		  
	  }
	  else if(HAL_GPIO_ReadPin(GPIOC,TRA3_Pin)==1
		  &&HAL_GPIO_ReadPin(GPIOC,TRA4_Pin)==1)
	  {
		 return 3;
	  }
	  else if(HAL_GPIO_ReadPin(GPIOC,TRA1_Pin)==1)//如果1检测黑线
	  {
		    set_speed(-30,0);
			set_speed(-20,1);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOC,TRA2_Pin)==1)//如果2检测到黑线
	  {
		    set_speed(-30,0);
			set_speed(-15,1);
	  }
	  else if(HAL_GPIO_ReadPin(GPIOC,TRA3_Pin)==1)//如果3检测黑线
	  {
			set_speed(-20,0);
			set_speed(-30,1);
	  }
	   else if(HAL_GPIO_ReadPin(GPIOC,TRA4_Pin)==1)//如果4检测到黑线
	  {
		    set_speed(-15,0);
			set_speed(-30,1);  
	  }
	  else if (HAL_GPIO_ReadPin(GPIOC,TRA1_Pin)==1&&HAL_GPIO_ReadPin(GPIOC,TRA3_Pin)==1)//如果1，3全为黑直行
	  {
			set_speed(-30,0);
			set_speed(-30,1);
	  }
	  
	  return 0;
}
void Go(void)
{
	set_speed(-30,0);
	set_speed(-30,1);
}	
void Stop(void)
{
	set_speed(0,0);
	set_speed(0,1);
	HAL_Delay(200);
}
void Turn_Left(void)
{
	Go();
	HAL_Delay(200);
	Stop();
	
	set_speed(-30,0);
	set_speed(20,1);
	HAL_Delay(1100);
	Stop();
}
void Turn_Right(void)
{
	Go();
	HAL_Delay(200);
	Stop();
	
	set_speed(20,0);
	set_speed(-30,1);
	HAL_Delay(1100);
 	Stop();
}
void Turn_Back(void)
{
	Go();         
	HAL_Delay(200);
	Stop();        
	
	set_speed(-30, 0);   
	set_speed(30, 1);    
	HAL_Delay(1600);     
	Stop();
	HAL_Delay(1000);
}