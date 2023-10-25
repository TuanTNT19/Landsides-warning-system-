<<<<<<< HEAD


#include "stdio.h"
#include "main.h"
#include "cmsis_os.h"
#include "ADC.h"
#include "UART.h"
#include "GPIOP.h"
TaskHandle_t task1Handle;
TaskHandle_t task2Handle;
TaskHandle_t task3Handle;
QueueHandle_t QueuexHandle;
QueueHandle_t QueueyHandle;
void Task1(void * para1);
void Task2(void *para2);
void Task3(void *para3);
uint8_t channels[2]={1,0};

uint16_t adc_value[2];
uint16_t data_receive[2];
char str1[10];
char str2[10];
int main(void)
{
  ADC1_Init();
	ADC1_Config_Multi(2,channels);
	DMA_Init();
	USART2_Init();
	USART2_Config(9600);
	xTaskCreate(Task1, "Task01", 128, NULL, 0, &task1Handle);
  xTaskCreate(Task2, "Task02", 128, NULL, 2, &task2Handle);
	xTaskCreate(Task3,"Task03",128,NULL,3,&task3Handle);
  QueuexHandle = xQueueCreate(1,2);
	QueueyHandle = xQueueCreate(1,2);
  osKernelStart();


  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void Task1 (void *para1){
	
	ADC1_Read_DMA((uint32_t)&ADC1->DR, (uint32_t)adc_value, 2);
	while(1)
	{
		
	  
		xQueueSend(QueuexHandle,&adc_value[0],NULL);
		xQueueSend(QueueyHandle,&adc_value[1],NULL);
		vTaskDelay(100);
	}
}

void Task2(void *para2)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  while(1)
  {
     xQueueReceive(QueuexHandle,&data_receive[0],osWaitForever);
    /* code here */
		int len1 = sprintf(str1, "%4d",data_receive[0]);
		USART2_Send_String((char *)str1);

  }
  /* USER CODE END 5 */
}
void Task3(void *para3)
{
	while(1)
	{
		xQueueReceive(QueueyHandle,&data_receive[1],osWaitForever);
		/*code here*/
		int len2 = sprintf(str2, "%4d",data_receive[1]);
		USART2_Send_String((char *)str2);
		
	}
	
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}
=======
>>>>>>> Develop
