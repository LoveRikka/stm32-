#include "tim.h"
float temp;
extern float adcv2[2000];
extern int count;
void TIM2_Init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʹ��TIM2ʱ��
  

  TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;//����Ϊ���ϼ���
  TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1; //����Ϊ1��Ƶ
  TIM_TimeBaseInitStruct.TIM_Period=0;//����ֵΪ0
  TIM_TimeBaseInitStruct.TIM_RepetitionCounter=1;//���һ�ξͿɴ���
  TIM_TimeBaseInitStruct.TIM_Prescaler=83;//���÷�Ƶ��
  
  
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
    
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//��������ж�
}

