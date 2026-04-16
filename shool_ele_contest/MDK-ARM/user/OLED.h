#ifndef __OLED_H
#define __OLED_H

#include "main.h"
#include <stdint.h>

void OLED_Init(void);
void OLED_CLS(void);
void OLED_ShowNum(uint8_t x, uint8_t page, int num);
#endif