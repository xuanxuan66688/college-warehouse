#ifndef __ENCODER_H
#define __ENCODER_H

#include "main.h"
// 2. 支持bool类型
#include <stdbool.h>
#include "tim.h"
void encoder_init(void);
int16_t get_speed_0(void);
int16_t get_speed_1(void);

#endif