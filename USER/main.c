#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "dac.h"
#include "tim.h"
#include "dma.h"




float adcconvert_local[2];
float adc_1;
float adc_2;
int count;
int main(void)
{ 
 	u16 adc_1,adc_2;
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);    //��ʼ����ʱ����
	MYDMA_Config(DMA2_Stream0,DMA_Channel_0,(u32)&ADC1->DR,(u32)adcconvert_local,2);
	Adc_Init();         //��ʼ��ADC
	Dac1_Init();        //��ʼ��DAC
	TIM2_Init();        //��ʼ����ʱ��
	

	
	while(1)
	{ 
		adc_1=adcconvert_local[0];//��ȡͨ��5��ת��ֵ
		adc_2=adcconvert_local[1];//��ȡͨ��0
		adc_1=(float)adc_1*(3.3/4096);          //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111
		adc_2=(float)adc_2*(3.3/4096);
		//temp-=adcx;                           //���Ѿ���ʾ����������ȥ��������С�����֣�����3.1111-3=0.1111
		adc_1*=1000;		//С�����ֳ���1000�����磺0.1111��ת��Ϊ111.1���൱�ڱ�����λС����
		adc_2*=1000;
	  delay_us(phase_diffrence());
		//adcval=adcv2[count%2000];//��ȡԭ��������ֵ
		DAC_SetChannel1Data(DAC_Align_12b_R,adc_1);//������Ҳ�
		
	}
}
int phase_diffrence()
{
	if(adc_1==0)
	{
		TIM_Cmd(TIM2,ENABLE);//������ʱ��
		while(adc_2!=0);//���ڶ������Ҳ���Ϊ0ʱ������ʱ
		TIM_Cmd(TIM2,DISABLE);//�رն�ʱ��
	}
	return TIM_GetCounter(TIM2);
}
	


