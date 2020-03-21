#include "tim.h"
float temp;
extern float adcv2[2000];
extern int count;
void TIM2_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能TIM2时钟
  

  TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//设置为向上计数
  TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1; //设置为1分频
  TIM_TimeBaseInitStruct.TIM_Period=0;//计数值为0
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter=1;//溢出一次就可触发
  TIM_TimeBaseInitStruct.TIM_Prescaler=83;//设置分频数
  
  
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
    
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//允许更新中断
}

