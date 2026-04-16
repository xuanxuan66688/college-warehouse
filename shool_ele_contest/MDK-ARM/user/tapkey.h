#ifndef __TAPKEY_H
#define __TAPKEY_H

#include "main.h"
#include "gpio.h"


// 读取按键状态（0=未按下，1=按下/触摸）
uint8_t tapkey(void);


#endif