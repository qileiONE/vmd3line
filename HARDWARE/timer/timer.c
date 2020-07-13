//#include "stm32f10x.h"
#include "timer.h"
#include "usart.h"
#include "exti.h"
u32 time_count=0;
u8 Rev_end_flag = FALSE;
/* TIM2中断优先级配置 */
void TIM2_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*中断周期为1ms*/
void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
    TIM_DeInit(TIM2);
    TIM_TimeBaseStructure.TIM_Period=1000;	//自动重装载寄存器周期的值(计数值) 
    /* 累计 TIM_Period个频率后产生一个更新或者中断 */
    TIM_TimeBaseStructure.TIM_Prescaler= (72 - 1);	//时钟预分频数 72M/72      
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式 
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);	// 清除溢出中断标志 
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    TIM_Cmd(TIM2, ENABLE);	// 开启时钟    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);	//先关闭等待使用  
	START_TIME;
}	 
void TIM2_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)//是更新中断
	{	 			   
		//USART_RX_STA|=1<<15;	//标记接收完成
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIM7更新中断标志    
		//TIM_Cmd(TIM2, DISABLE);  //关闭TIM7 

		if(bVmdTimeStartCntFlag == TURE)
		{
			dwVmdTimeStartCnt ++ ;
			if(dwVmdTimeStartCnt > START_TIME_MAX)
			{
				bVmdTimeStartCntFlag = FALSE;
				dwVmdTimeStartCnt = 0;
				bVmdTimeStartFlag = TURE;	
			}
		}
		if(bVmdTimeRunCntFlag == TURE)
		{
			dwVmdTimeRunCnt ++ ;
			if(dwVmdTimeRunCnt > RUN_TIME_MAX)
			{
				bVmdTimeRunCntFlag = FALSE;
				dwVmdTimeRunCnt = 0;
				bVmdTimeRunFlag = TURE;
			}
		}

		if(SaleAndLightFlag == 1)
		{
			dwSaleAndlightCnt ++;
			if(dwSaleAndlightCnt > RUN_TIME_MAX/20)
			{
				if(LightCheck_Read() == 1)
				{
					SaleAndLightCheckOverFlag = 1;
					
					SaleAndLightFlag = 0;
					dwSaleAndlightCnt = 0;
				}
				else
				{
					bLightCheck = 0;
				}
			}
			if(dwSaleAndlightCnt > RUN_TIME_MAX)	
			{	
				bLightCheck = 1;
				SaleAndLightCheckOverFlag = 1;
				SaleAndLightFlag = 0;
				dwSaleAndlightCnt = 0;
				
			}
		}

		time_count++;
		if(time_count>30000)
		{
			time_count = 0;
			DateSaveFlag = 1;
		}
//		{
//			USART_RX_STA|=1<<15;	
////			STOP_TIME;
//			Flag_Send_data|=1<<15;	//标记接收完成			
////			//TIM_Cmd(TIM2, DISABLE);  //关闭TIM7 
//			time_count=0;
//		}
	}	    
}



