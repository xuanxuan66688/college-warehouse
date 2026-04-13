#ifndef __TRACKING_H
#define __TRACKING_H

#include "main.h"
#include "gpio.h"
#include "motor.h"
// 2. 支持bool类型
#include <stdbool.h>
#include <stdio.h>
int8_t Tracking(void);
void Go(void);
void Stop(void);
void Turn_Left(void);
void Turn_Right(void);
void Turn_Back(void);
#endif