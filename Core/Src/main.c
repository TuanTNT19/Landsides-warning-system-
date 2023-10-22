
#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "Timer.h"
#include "ADC.h"
#include "GPIOP.h"
#include "UART.h"
uint16_t adc_value[2];
uint8_t channel[2]={1,0};
char str[10];


int main()
{
	  USART2_Init();
		TIM2_config();
		ADC1_Config_Multi(2,channel);
		DMA_Init();
  	ADC1_Read_DMA((uint32_t)&ADC1->DR, (uint32_t)adc_value, 2);
	  USART2_Config(9600);
	while(1)
	{
	int len1 = sprintf(str,"%4d %4d",adc_value[0],adc_value[1]);
	USART2_Send_String((char *)(str));
	delay_ms(100);	
	}
	
}