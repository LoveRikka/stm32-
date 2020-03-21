#include "tim.h"
float temp;
extern float adcv2[2000];
extern int count;
void TIM2_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  NVIC_InitTypeDef NVIC_InitStructure;

  TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//?¨¨?????¨°??????
  TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV2; //?¨¨??????¡¤???
  TIM_TimeBaseInitStruct.TIM_Period=9;//????????0
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;//??????????????¡¤?
  TIM_TimeBaseInitStruct.TIM_Prescaler=719;//?¨¨??¡¤?????
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//????TIM2?¡À??
  
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
    
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//???¨ª?¨¹??????
    
  NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //?¡§?¡À?¡Â2????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01; //??????????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //¡Á???????3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM2,ENABLE);//?????¡§?¡À?¡Â2
}
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//??¡¤?????
    {
        adcv2[count%2000]=temp;//???¨´???¡Â??
        count++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//?¨¹??????
    }
}
