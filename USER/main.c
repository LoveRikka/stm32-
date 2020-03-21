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
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);    //初始化延时函数
	MYDMA_Config(DMA2_Stream0,DMA_Channel_0,(u32)&ADC1->DR,(u32)adcconvert_local,2);
	Adc_Init();         //初始化ADC
	Dac1_Init();        //初始化DAC
	TIM2_Init();        //初始化定时器
	

	
	while(1)
	{ 
		adc_1=adcconvert_local[0];//获取通道5的转换值
		adc_2=adcconvert_local[1];//获取通道0
		adc_1=(float)adc_1*(3.3/4096);          //获取计算后的带小数的实际电压值，比如3.1111
		adc_2=(float)adc_2*(3.3/4096);
		//temp-=adcx;                           //把已经显示的整数部分去掉，留下小数部分，比如3.1111-3=0.1111
		adc_1*=1000;		//小数部分乘以1000，例如：0.1111就转换为111.1，相当于保留三位小数。
		adc_2*=1000;
	  delay_us(phase_diffrence());
		//adcval=adcv2[count%2000];//获取原波形特征值
		DAC_SetChannel1Data(DAC_Align_12b_R,adc_1);//输出正弦波
		
	}
}
int phase_diffrence()
{
	if(adc_1==0)
	{
		TIM_Cmd(TIM2,ENABLE);//开启定时器
		while(adc_2!=0);//当第二道正弦波不为0时持续计时
		TIM_Cmd(TIM2,DISABLE);//关闭定时器
	}
	return TIM_GetCounter(TIM2);
}
	


