/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h> //printf头文件
#include <string.h>  //计算数组长度函数
#include <String.h> //判断接收缓冲区头文件
#include "motor.h"
#include "encoder.h"
#include "pid.h"
#include "struct_typedef.h"
#include "Tracking.h"
#include "tapkey.h"
#include "OLED.h"
#include "Buzzer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define LENGTH  1 //定义接收缓冲区一大小
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t RxBuff[LENGTH]={0};//接收缓冲区一
uint8_t RxCount;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//获取实际速度
int16_t Actual_Speed_0;
int16_t Actual_Speed_1;

//定义目标速度
int16_t target_speed_0=-10;
int16_t target_speed_1=-10;
//定义循迹标志位
uint8_t Trflag=0;
uint8_t State_T=0;//开启循迹标志位
//定义串口标志位
uint8_t Rxflag=0;
//定义接收字符串
uint8_t lastchar=0;
uint8_t lastchar_3=0;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
/*
	标志位定义
*/
uint8_t Mode_3=0;//开启模式标志位
//定义处理转弯标志位。完成两次转弯后取消转弯标志位
uint8_t Left=0;
uint8_t Right=0;
//定义转弯标志位（判断发挥题从左转入还是从右转入）
uint8_t Judge_1=0; //1为左2为右
//轻触开关标志位
uint8_t tapkey=0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
	
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_TIM4_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_UART5_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  //开启定时器中断
  HAL_TIM_Base_Start_IT(&htim4);
    //PWM初始化
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
  //编码器初始化
   encoder_init();
  //串口接受函数一中断使能
  HAL_UART_Receive_IT(&huart5,RxBuff,LENGTH);
 //硬件IIC初始化
  MX_I2C1_Init();
  //OLED初始化并清屏
  OLED_Init();
  
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
 while(1)
 {
//	State_T=0; 
//	 printf("%d,%d\r\n",Trflag,lastchar);//测试代码
	 if(HAL_GPIO_ReadPin(GPIOA,KEY_Pin)==1)//按键按下
	 {
		 break;
	 }
	 
 }
  while (1)
  {
	  
		State_T=1;//开启循迹
	  OLED_ShowNum(1, 1, lastchar);//测试代码 
	  OLED_ShowNum(1, 4, Trflag);//测试代码 
	  
	  /*
	  逻辑处理区
	  */
			
			 //转弯传值函数
			 if(Trflag==1&&lastchar==48)//lastchar=48置直行标志位(处理发挥第一问)
			 {
				 OLED_ShowNum(1, 1, lastchar);
					State_T=1;
					HAL_Delay(2000);
					State_T=0;
					Turn_Back();
					State_T=1;
					lastchar=100;//进入发挥第一问掉头标志位
				 OLED_ShowNum(1, 1, lastchar);
			}
			//处理中病房走入远端病房
			 else if(Trflag==1&&lastchar==57&&Judge_1==1)//左转进入中端病房
			 {
				 State_T=0;
				Turn_Left(); //左转出中端病房
				set_speed(-15,0);
				set_speed(-15,0);
				 State_T=1; 
				 OLED_ShowNum(1, 1, lastchar);
			 }
			 else if(Trflag==1&&lastchar==57&&Judge_1==2)//右转进入中端病房
			 {
				 State_T=0;
				Turn_Right(); //右转出中端病房
				set_speed(-15,0);
				set_speed(-15,0);
				 State_T=1; 
				 OLED_ShowNum(1, 1, lastchar);
			 }
			if(Trflag==1&&lastchar==49)
			{
				OLED_ShowNum(1, 1, lastchar);
				State_T=0;
				Turn_Left();
				set_speed(-15,0);
				set_speed(-15,0);
				//HAL_Delay(500);
				//printf("%d,%d\r\n",Trflag,lastchar);//测试代码
				State_T=1;
				HAL_Delay(2000);
				State_T=0;
				Turn_Back();
//				State_T=1;
				Judge_1=1;  //表示先是左转转入
				lastchar=81;//进入右转掉头回去的标志位
				OLED_ShowNum(1, 1, lastchar);
			}
			else if(Trflag==1&&lastchar==50)
			{
				OLED_ShowNum(1, 1, lastchar);
				State_T=0;
				Turn_Right();
				set_speed(-15,0);
				set_speed(-15,0);
				//HAL_Delay(500);
				printf("%d,%d\r\n",Trflag,lastchar);//测试代码
				State_T=1;
				HAL_Delay(2000);
				State_T=0;
				Turn_Back();
				State_T=1;
				Judge_1=2;
				lastchar=80;//进入左转掉头回去的标志位
				OLED_ShowNum(1, 1, lastchar);
			}
			//特殊处理基础第三问，四个字母时
			else if (Trflag==1&&lastchar==51)
			{
				State_T=0;
				Turn_Left();
				State_T=1;
				Mode_3=49;//置第三问特殊处理标志位
				printf("%d,%d,%d\r\n",Trflag,lastchar,Mode_3);//测试代码
				HAL_Delay(200);
				OLED_ShowNum(1, 1, lastchar);
			}
			else if (Trflag==1&&lastchar==52)
			{
				State_T=0;
				Turn_Right();
				State_T=1;
				Mode_3=49;//置第三问特殊处理标志位
				printf("%d,%d,%d\r\n",Trflag,lastchar,Mode_3);//测试代码
				HAL_Delay(200);
				lastchar=0;//转弯完成之后清零标志位
				OLED_ShowNum(1, 1, lastchar);
			}
			//掉头返回处理
			if(Trflag==1&&lastchar==80)//全黑以及在左转弯向右掉头
			{
				//Buzzer();
				State_T=0;
				Turn_Left();
	//			printf("%d,%d\r\n",Trflag,lastchar);//测试代码
	//			HAL_Delay(200);
				State_T=1;
				lastchar=0;
				OLED_ShowNum(1, 1, lastchar);
			}
			else if (Trflag==1&&lastchar==81)
			{
				//Buzzer();
				State_T=0;
				Turn_Right();
	//			printf("%d,%d\r\n",Trflag,lastchar);//测试代码
	//			HAL_Delay(200);
				State_T=1;
				lastchar=0;
				OLED_ShowNum(1, 1, lastchar);
			}
			//第三问掉头返回处理
			if((Trflag==2&&Mode_3==49&&lastchar==80)||(Trflag==2&&Mode_3==49&&lastchar_3==80))
			{
				Buzzer();
				State_T=0;
				Turn_Left();
				HAL_Delay(200);
	//			printf("%d,%d\r\n",Trflag,lastchar);//测试代码
	//			HAL_Delay(200);
				lastchar=81;
				
				Left+=1;
				State_T=1;
				HAL_Delay(500);
				OLED_ShowNum(1, 1, lastchar);
			}
			else if((Trflag==3&&Mode_3==49&&lastchar==81)||(Trflag==3&&Mode_3==49&&lastchar_3==81))
			{
				Buzzer();
				State_T=0;
				Turn_Right();
				HAL_Delay(200);
	//			printf("%d,%d\r\n",Trflag,lastchar);//测试代码
	//			HAL_Delay(200);
				lastchar=80;
				Right+=1;
				State_T=1;
				HAL_Delay(500);
				lastchar_3=81;
				OLED_ShowNum(1, 1, lastchar);
			}
			//清除左右转标志位
			if((Left==1&&Right==1)||Left==2||Right==2)
			{
				lastchar=0;//转弯完成后关掉转弯标注位防止再次转弯
				Mode_3=0;
			}
			//判断发挥第一问
			if(lastchar==100&&Judge_1==1)
			{
				lastchar=80;
			}
			else if(lastchar==100&&Judge_1==2)
			{
				lastchar=81;
			}
	/* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* USER CODE BEGIN 4 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==UART5)
	{
		if(RxBuff[0] == 0x0D || RxBuff[0] == 0x0A)
		
		{
			HAL_UART_Receive_IT(&huart5, RxBuff, LENGTH);
			return;
		}
		lastchar = RxBuff[0];
		//重新开启接收函数一
		HAL_UART_Receive_IT(&huart5, RxBuff, LENGTH);
	}
}
/**
  * @brief   重定义printf函数
*/
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,HAL_MAX_DELAY);
	return ch;
}
/**
	* @brief  定时器中断回流函数
	* @param  htim定时器指针
	* @retval 无

*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(State_T==1)
		{
			Trflag=Tracking();
		}

	static int count=0;
	if(htim->Instance == TIM4)
	{
		
		count++;
		if(count==80)
		{
			count=0;
			Actual_Speed_0=-get_speed_0();
			Actual_Speed_1=get_speed_1();
			// HAL_GPIO_TogglePin(GPIOB,LED_Pin);
		}
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
