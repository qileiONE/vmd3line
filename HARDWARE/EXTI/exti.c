#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "stm32f10x_exti.h"
//////////////////////////////////////////////////////////////////////////////////	 								  
//////////////////////////////////////////////////////////////////////////////////   

u32 Flag_Send_data=0;

//外部中断0服务程序
void EXTIX_Init(void)
{
		

}

 //外部中断0服务程序 
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{
	   EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位 
	}
	 
}
