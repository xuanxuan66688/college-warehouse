#ifndef __MOTOR_H
#define __MOTOR_H

// 1. 全局必备：承接HAL库所有定义（tim、gpio、uart都在这里）
#include "main.h"
// 2. 支持bool类型
#include <stdbool.h>
#include "tim.h"
void set_dir(bool wheel,bool dir);
void set_speed(int speed,bool wheel);

#endif