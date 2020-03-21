#ifndef __TIM_H
#define __TIM_H
#include "sys.h"
#include "stm32f4xx_tim.h"
void TIM_Init(void);
void TIMx_IRQHandler(void);
#endif