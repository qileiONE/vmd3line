//////////////////////////////////////////////////////////////////////////////////	           
//All rights reserved
//******************************************************************************/
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "exti.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_dma.h"
#include "string.h"
#include "led.h"
#include "vmddir.h"
#include "comm.h"
#include "gpio.h"
#include "adc.h"
#include "fram.h"


#define Device_Id "0001"

BYTE LightCheckFlag = 1;
BYTE HeatFlag = 0;
BYTE CompreFlag = 0;
BYTE LightStripFlag = 0;

DWORD ReshidianCnt = 0;

BYTE TempAutoFlag = 0;

BYTE ReShiDianFlag = 0;
BYTE DateSaveFlag = 0;
unsigned int TempValue  = 0;

BYTE SaleAndLightFlag = 0; //出货后光检状态
BYTE SaleAndLightCheckOverFlag = 0;

u8 MCU_SN[6] = {0};

void GetLockCode(void) 
{
    u32 stm32Id[3]={0};
	u32 stm32_id_data = 0;
    stm32Id[0]=*(vu32*)(0x1ffff7e8);
    stm32Id[1]=*(vu32*)(0x1ffff7ec);
    stm32Id[2]=*(vu32*)(0x1ffff7f0);
    //return (stm32Id[0]>>1)+(stm32Id[1]>>2)+(stm32Id[2]>>3);
	stm32_id_data = (stm32Id[0]>>1)+(stm32Id[1]>>2)+(stm32Id[2]>>3);
	MCU_SN[0] = 0x07;
	MCU_SN[1] = 0x24;
	MCU_SN[2] = stm32_id_data ; 
	MCU_SN[3] = stm32_id_data >> 8 ;
	MCU_SN[4] = stm32_id_data >> 16 ;
	MCU_SN[5] = stm32_id_data >> 24 ;
}


int main(void)
{
	u8 res=1;
	delay_init();	    	 //延时函数初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 	LED_Init();			     //LED端口初始化
	TIM2_NVIC_Configuration(); /* TIM2 定时配置 */
	TIM2_Configuration(); 		
	uart2_init(9600);  
	uart3_init(2400);
	LED_GPIO_Config();
	VMD_GPIO_Init();
	ADC1_Init();
	GPIO_INIT_Fram();
	VMD_MotorReset();
	GetLockCode();
	LED(ON);

	Read_Config_Data();
	Output_Init();
	bVmdRunningFlag = FALSE;
	dwVmdTimeRunCnt = 0;
	bVmdTimeRunFlag = FALSE;
	bVmdTimeRunCntFlag = FALSE;
	dwVmdTimeStartCnt = 0;
	bVmdTimeStartFlag = FALSE;
	bVmdTimeStartCntFlag = FALSE;
	bVmdBusyFlag = FALSE;

	bLightCheck = 1;
	while(res)
	{	 
		VMD_CommProcess();
		TEMP_CommProcess();
		if(wRuncnt > (HORNUM_MAX*VERNUM_MAX))
		{
			bVmdCheckEnd = TURE;
			bVmdResetEnd = TURE;
			wRuncnt = 0;	
		}
//		if((bVmdCheckEnd == TURE)||(bVmdResetEnd == TURE))
//		{	
			VMD_ErrCheck();
			VMD_LightCheck();
//		}
		if(bVmdCheckEnd == FALSE)
		{
			VMD_AllCheck(wRuncnt); 
		//	VMD_SalesControl(wRuncnt);
		}
		else if(bVmdResetEnd == FALSE)
		{
			VMD_AllReset(wRuncnt);
		//	 VMD_ResetControl(wRuncnt);
		}
		wRuncnt ++;


		if(DateSaveFlag == 1)		//定时存数据
		{
			DateSaveFlag = 0;
			Write_config_Data();
		}

	
		if(TempAutoFlag == 1)
		{
			if(CompreFlag == 1)
			{
			   	if(TempValue > 1000)
				{
					if(Get_temp1()>1000)
					{
						if(TempValue > Get_temp1())	
						{
							Compressor_Set();
						}
						else 
						{
							Compressor_Reset();
						}
					}
					else 
					{
						Compressor_Set();
					}	
				}
				else 
				{
					if(Get_temp1()<1000)
					{
						if(TempValue > Get_temp1())	
						{
							Compressor_Reset();
						}
						else 
						{
							Compressor_Set();
						}
					}
					else 
					{
						Compressor_Reset();
					}		
				}
			}
		}
	//	else 
//		if(HeatFlag == 1)
//		{
//			if(TempValue > 1000)
//			{
//				Lightstrip_Set();
//			}	
//		}		   
	}	
}

