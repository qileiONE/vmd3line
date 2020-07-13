#include "gpio.h"
#include "sys.h"

void VMD_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	// Enable GPIO clock
	RCC_GPIOA_CLK_ENABLE();
	RCC_GPIOB_CLK_ENABLE();
	RCC_GPIOC_CLK_ENABLE();
	RCC_GPIOD_CLK_ENBALE();
	RCC_GPIOE_CLK_ENABLE();	

   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	//**********************horizontal*************************
	//hor1 
	GPIO_InitStructure.GPIO_Pin = Hor_1_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_1_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_1_GPIO_Port, Hor_1_Pin);

	//hor2
	GPIO_InitStructure.GPIO_Pin = Hor_2_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_2_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_2_GPIO_Port, Hor_2_Pin);	
	
	//hor3
	GPIO_InitStructure.GPIO_Pin = Hor_3_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_3_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_3_GPIO_Port, Hor_3_Pin); 

	//hor4
	GPIO_InitStructure.GPIO_Pin = Hor_4_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_4_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_4_GPIO_Port, Hor_4_Pin); 

	//hor5
	GPIO_InitStructure.GPIO_Pin = Hor_5_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_5_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_5_GPIO_Port, Hor_5_Pin); 

	//hor6
	GPIO_InitStructure.GPIO_Pin = Hor_6_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_6_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_6_GPIO_Port, Hor_6_Pin); 

	//hor7
	GPIO_InitStructure.GPIO_Pin = Hor_7_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_7_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_7_GPIO_Port, Hor_7_Pin); 

   	//hor8
	GPIO_InitStructure.GPIO_Pin = Hor_8_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_8_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_8_GPIO_Port, Hor_8_Pin); 

	//hor9
	GPIO_InitStructure.GPIO_Pin = Hor_9_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_9_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_9_GPIO_Port, Hor_9_Pin); 

	//hor10
	GPIO_InitStructure.GPIO_Pin = Hor_10_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Hor_10_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(Hor_10_GPIO_Port, Hor_10_Pin); 

	//**********************vertical*************************
	//ver1 
	GPIO_InitStructure.GPIO_Pin = ver_1_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ver_1_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(ver_1_GPIO_Port, ver_1_Pin);

	//ver2 
	GPIO_InitStructure.GPIO_Pin = ver_2_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ver_2_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(ver_2_GPIO_Port, ver_2_Pin);

	//ver3 
	GPIO_InitStructure.GPIO_Pin = ver_3_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ver_3_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(ver_3_GPIO_Port, ver_3_Pin);

	//ver4 
	GPIO_InitStructure.GPIO_Pin = ver_4_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ver_4_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(ver_4_GPIO_Port, ver_4_Pin);

	//ver5 
	GPIO_InitStructure.GPIO_Pin = ver_5_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ver_5_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(ver_5_GPIO_Port, ver_5_Pin);

	//ver6 
	GPIO_InitStructure.GPIO_Pin = ver_6_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ver_6_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(ver_6_GPIO_Port, ver_6_Pin);

	//ver7 
	GPIO_InitStructure.GPIO_Pin = ver_7_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ver_7_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(ver_7_GPIO_Port, ver_7_Pin);

	//ver8 
	GPIO_InitStructure.GPIO_Pin = ver_8_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(ver_8_GPIO_Port, &GPIO_InitStructure);  
	GPIO_ResetBits(ver_8_GPIO_Port, ver_8_Pin);

	//**********************sigle return*************************
	//sigReturn1 
	GPIO_InitStructure.GPIO_Pin = sigReturn_1_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(sigReturn_1_GPIO_Port, &GPIO_InitStructure);  

	//sigReturn2 
	GPIO_InitStructure.GPIO_Pin = sigReturn_2_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(sigReturn_2_GPIO_Port, &GPIO_InitStructure); 
	
	//sigReturn3 
	GPIO_InitStructure.GPIO_Pin = sigReturn_3_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(sigReturn_3_GPIO_Port, &GPIO_InitStructure);   

	//sigReturn4 
	GPIO_InitStructure.GPIO_Pin = sigReturn_4_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(sigReturn_4_GPIO_Port, &GPIO_InitStructure);  

	//sigReturn5 
	GPIO_InitStructure.GPIO_Pin = sigReturn_5_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(sigReturn_5_GPIO_Port, &GPIO_InitStructure);  

	//sigReturn6 
	GPIO_InitStructure.GPIO_Pin = sigReturn_6_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(sigReturn_6_GPIO_Port, &GPIO_InitStructure);  

	//sigReturn7 
	GPIO_InitStructure.GPIO_Pin = sigReturn_7_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(sigReturn_7_GPIO_Port, &GPIO_InitStructure);  

	//sigReturn8 
	GPIO_InitStructure.GPIO_Pin = sigReturn_8_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(sigReturn_8_GPIO_Port, &GPIO_InitStructure);  

	//**********************GND check*************************
	//gedCheck1 
	GPIO_InitStructure.GPIO_Pin = gndCheck_1_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gndCheck_1_GPIO_Port, &GPIO_InitStructure);  

	//gedCheck2 
	GPIO_InitStructure.GPIO_Pin = gndCheck_2_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gndCheck_2_GPIO_Port, &GPIO_InitStructure);  

	//gedCheck3 
	GPIO_InitStructure.GPIO_Pin = gndCheck_3_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gndCheck_3_GPIO_Port, &GPIO_InitStructure);  

	//gedCheck4 
	GPIO_InitStructure.GPIO_Pin = gndCheck_4_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gndCheck_4_GPIO_Port, &GPIO_InitStructure);  

	//gedCheck5 
	GPIO_InitStructure.GPIO_Pin = gndCheck_5_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gndCheck_5_GPIO_Port, &GPIO_InitStructure);  

	//gedCheck6 
	GPIO_InitStructure.GPIO_Pin = gndCheck_6_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gndCheck_6_GPIO_Port, &GPIO_InitStructure);  

	//gedCheck7 
	GPIO_InitStructure.GPIO_Pin = gndCheck_7_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gndCheck_7_GPIO_Port, &GPIO_InitStructure);  

	//gedCheck8 
	GPIO_InitStructure.GPIO_Pin = gndCheck_8_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(gndCheck_8_GPIO_Port, &GPIO_InitStructure);  	

	//********************** output *************************
	//compressor
	GPIO_InitStructure.GPIO_Pin = compressor_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(compressor_GPIO_Port, &GPIO_InitStructure);  
	GPIO_SetBits(compressor_GPIO_Port, compressor_Pin);
	
	//lightstrip
	GPIO_InitStructure.GPIO_Pin = lightstrip_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(lightstrip_GPIO_Port, &GPIO_InitStructure);  
	GPIO_SetBits(lightstrip_GPIO_Port, lightstrip_Pin);

	//doorlock
	GPIO_InitStructure.GPIO_Pin = doorlock_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(doorlock_GPIO_Port, &GPIO_InitStructure);  
	GPIO_SetBits(doorlock_GPIO_Port, doorlock_Pin);

	//yuliu1
	GPIO_InitStructure.GPIO_Pin = yuliu_1_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(yuliu_1_GPIO_Port, &GPIO_InitStructure);  
	GPIO_SetBits(yuliu_1_GPIO_Port, yuliu_1_Pin);

	//yuliu2
	GPIO_InitStructure.GPIO_Pin = yuliu_2_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(yuliu_2_GPIO_Port, &GPIO_InitStructure);  
	GPIO_SetBits(yuliu_2_GPIO_Port, yuliu_2_Pin);

	//********************** intput *************************
	//lightcheck
	GPIO_InitStructure.GPIO_Pin = lightcheck_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(lightcheck_GPIO_Port, &GPIO_InitStructure);  	

	//reshidian
	GPIO_InitStructure.GPIO_Pin = reshidian_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(reshidian_GPIO_Port, &GPIO_InitStructure);  

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
	/* Configure EXTI3 line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI3 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
	
	//doorswitch
	GPIO_InitStructure.GPIO_Pin = doorswitch_Pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;       
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(doorswitch_GPIO_Port, &GPIO_InitStructure);
}

void HorState_Set(IN WORD wHorNum)
{
	switch(wHorNum)
	{
		case HORNum_1:
			{
				GPIO_SetBits(Hor_1_GPIO_Port, Hor_1_Pin);		
			}
			break;
		case HORNum_2:
			{
				GPIO_SetBits(Hor_2_GPIO_Port, Hor_2_Pin);		
			}
			break; 
		case HORNum_3:
			{
				GPIO_SetBits(Hor_3_GPIO_Port, Hor_3_Pin);		
			}
			break;
		case HORNum_4:
			{
				GPIO_SetBits(Hor_4_GPIO_Port, Hor_4_Pin);		
			}
			break;
		case HORNum_5:
			{
				GPIO_SetBits(Hor_5_GPIO_Port, Hor_5_Pin);		
			}
			break;
		case HORNum_6:
			{
				GPIO_SetBits(Hor_6_GPIO_Port, Hor_6_Pin);		
			}
			break;
		case HORNum_7:
			{
				GPIO_SetBits(Hor_7_GPIO_Port, Hor_7_Pin);		
			}
			break;
		case HORNum_8:
			{
				GPIO_SetBits(Hor_8_GPIO_Port, Hor_8_Pin);		
			}
			break;
		case HORNum_9:
			{
				GPIO_SetBits(Hor_9_GPIO_Port, Hor_9_Pin);		
			}
			break;
		case HORNum_10:
			{
				GPIO_SetBits(Hor_10_GPIO_Port, Hor_10_Pin);		
			}
			break;
		default :
			break;
	}
}

void HorState_Reset(IN WORD wHorNum)
{
	switch(wHorNum)
	{
		case HORNum_1:
			{
				GPIO_ResetBits(Hor_1_GPIO_Port, Hor_1_Pin);		
			}
			break;
		case HORNum_2:
			{
				GPIO_ResetBits(Hor_2_GPIO_Port, Hor_2_Pin);		
			}
			break; 
		case HORNum_3:
			{
				GPIO_ResetBits(Hor_3_GPIO_Port, Hor_3_Pin);		
			}
			break;
		case HORNum_4:
			{
				GPIO_ResetBits(Hor_4_GPIO_Port, Hor_4_Pin);		
			}
			break;
		case HORNum_5:
			{
				GPIO_ResetBits(Hor_5_GPIO_Port, Hor_5_Pin);		
			}
			break;
		case HORNum_6:
			{
				GPIO_ResetBits(Hor_6_GPIO_Port, Hor_6_Pin);		
			}
			break;
		case HORNum_7:
			{
				GPIO_ResetBits(Hor_7_GPIO_Port, Hor_7_Pin);		
			}
			break;
		case HORNum_8:
			{
				GPIO_ResetBits(Hor_8_GPIO_Port, Hor_8_Pin);		
			}
			break;
		case HORNum_9:
			{
				GPIO_ResetBits(Hor_9_GPIO_Port, Hor_9_Pin);		
			}
			break;
		case HORNum_10:
			{
				GPIO_ResetBits(Hor_10_GPIO_Port, Hor_10_Pin);		
			}
			break;
		default :
			break;
	}
}

void VerState_Set(IN WORD wVerNum)
{
	switch(wVerNum)
	{
		case VERNum_1:
		{
			GPIO_SetBits(ver_1_GPIO_Port, ver_1_Pin);		
		}
		break;
		case VERNum_2:
		{
			GPIO_SetBits(ver_2_GPIO_Port, ver_2_Pin);		
		}
		break;
		case VERNum_3:
		{
			GPIO_SetBits(ver_3_GPIO_Port, ver_3_Pin);		
		}
		break;
		case VERNum_4:
		{
			GPIO_SetBits(ver_4_GPIO_Port, ver_4_Pin);		
		}
		break;
		case VERNum_5:
		{
			GPIO_SetBits(ver_5_GPIO_Port, ver_5_Pin);		
		}
		break;
		case VERNum_6:
		{
			GPIO_SetBits(ver_6_GPIO_Port, ver_6_Pin);		
		}
		break;
		case VERNum_7:
		{
			GPIO_SetBits(ver_7_GPIO_Port, ver_7_Pin);		
		}
		break;
		case VERNum_8:
		{
			GPIO_SetBits(ver_8_GPIO_Port, ver_8_Pin);		
		}
		break;
		default:
			break;
	}
}

void VerState_Reset(IN WORD wVerNum)
{
	switch(wVerNum)
	{
		case VERNum_1:
		{
			GPIO_ResetBits(ver_1_GPIO_Port, ver_1_Pin);		
		}
		break;
		case VERNum_2:
		{
			GPIO_ResetBits(ver_2_GPIO_Port, ver_2_Pin);		
		}
		break;
		case VERNum_3:
		{
			GPIO_ResetBits(ver_3_GPIO_Port, ver_3_Pin);		
		}
		break;
		case VERNum_4:
		{
			GPIO_ResetBits(ver_4_GPIO_Port, ver_4_Pin);		
		}
		break;
		case VERNum_5:
		{
			GPIO_ResetBits(ver_5_GPIO_Port, ver_5_Pin);		
		}
		break;
		case VERNum_6:
		{
			GPIO_ResetBits(ver_6_GPIO_Port, ver_6_Pin);		
		}
		break;
		case VERNum_7:
		{
			GPIO_ResetBits(ver_7_GPIO_Port, ver_7_Pin);		
		}
		break;
		case VERNum_8:
		{
			GPIO_ResetBits(ver_8_GPIO_Port, ver_8_Pin);		
		}
		break;
		default:
			break;
	}
}

BYTE SigReturn_Read(IN WORD wSigRetNum)
{
	BYTE bSigRetValue;
	switch(wSigRetNum)
	{
		case SIGRETNUM_1:
		{
			//bSigRetValue = READ_SIGRETURN_1();
			if(GPIO_ReadInputDataBit(sigReturn_1_GPIO_Port,sigReturn_1_Pin)== 1)
			 	bSigRetValue = 1;
			else
				bSigRetValue = 0;
		}
		break;
	   	case SIGRETNUM_2:
		{
			//bSigRetValue = READ_SIGRETURN_2();
			if(GPIO_ReadInputDataBit(sigReturn_2_GPIO_Port,sigReturn_2_Pin)== 1)
			 	bSigRetValue = 1;
			else
				bSigRetValue = 0;
		}
		break;
		case SIGRETNUM_3:
		{
			//bSigRetValue = READ_SIGRETURN_3();
			if(GPIO_ReadInputDataBit(sigReturn_3_GPIO_Port,sigReturn_3_Pin)== 1)
			 	bSigRetValue = 1;
			else
				bSigRetValue = 0;
		}
		break;
		case SIGRETNUM_4:
		{
			//bSigRetValue = READ_SIGRETURN_4();
			if(GPIO_ReadInputDataBit(sigReturn_4_GPIO_Port,sigReturn_4_Pin)== 1)
			 	bSigRetValue = 1;
			else
				bSigRetValue = 0;
		}
		break;
		case SIGRETNUM_5:
		{
			//bSigRetValue = READ_SIGRETURN_5();
			if(GPIO_ReadInputDataBit(sigReturn_5_GPIO_Port,sigReturn_5_Pin)== 1)
			 	bSigRetValue = 1;
			else
				bSigRetValue = 0;
		}
		break;
		case SIGRETNUM_6:
		{
			//bSigRetValue = READ_SIGRETURN_6();
			if(GPIO_ReadInputDataBit(sigReturn_6_GPIO_Port,sigReturn_6_Pin)== 1)
			 	bSigRetValue = 1;
			else
				bSigRetValue = 0;
		}
		break;
		case SIGRETNUM_7:
		{
			//bSigRetValue = READ_SIGRETURN_7();
			if(GPIO_ReadInputDataBit(sigReturn_7_GPIO_Port,sigReturn_7_Pin)== 1)
			 	bSigRetValue = 1;
			else
				bSigRetValue = 0;
		}
		break;
		case SIGRETNUM_8:
		{
			//bSigRetValue = READ_SIGRETURN_8();
			if(GPIO_ReadInputDataBit(sigReturn_8_GPIO_Port,sigReturn_8_Pin)== 1)
			 	bSigRetValue = 1;
			else
				bSigRetValue = 0;
		}
		break;
		default:
			break;

	}
	return bSigRetValue;
}

BYTE GndCheck_Read(IN WORD wGndCheckNum) 
{
	BYTE bGndCheckValue;
	switch(wGndCheckNum)
	{
		case GNDCHECKNUM_1:
		{
		 //	bGndCheckValue = READ_GNDCHECK_1();
			if(GPIO_ReadInputDataBit(gndCheck_1_GPIO_Port,gndCheck_1_Pin)== 1)
			 	bGndCheckValue = 1;
			else
				bGndCheckValue = 0;
		}
		break;
		case GNDCHECKNUM_2:
		{
		 	//bGndCheckValue = READ_GNDCHECK_2();
			if(GPIO_ReadInputDataBit(gndCheck_2_GPIO_Port,gndCheck_2_Pin)== 1)
			 	bGndCheckValue = 1;
			else
				bGndCheckValue = 0;
		}
		break;
		case GNDCHECKNUM_3:
		{
		 	//bGndCheckValue = READ_GNDCHECK_3();
			if(GPIO_ReadInputDataBit(gndCheck_3_GPIO_Port,gndCheck_3_Pin)== 1)
			 	bGndCheckValue = 1;
			else
				bGndCheckValue = 0;
		}
		break;
		case GNDCHECKNUM_4:
		{
		 	//bGndCheckValue = READ_GNDCHECK_4();
			if(GPIO_ReadInputDataBit(gndCheck_4_GPIO_Port,gndCheck_4_Pin)== 1)
			 	bGndCheckValue = 1;
			else
				bGndCheckValue = 0;
		}
		break;
		case GNDCHECKNUM_5:
		{
		 	//bGndCheckValue = READ_GNDCHECK_5();
			if(GPIO_ReadInputDataBit(gndCheck_5_GPIO_Port,gndCheck_5_Pin)== 1)
			 	bGndCheckValue = 1;
			else
				bGndCheckValue = 0;
		}
		break;
		case GNDCHECKNUM_6:
		{
		 	//bGndCheckValue = READ_GNDCHECK_6();
			if(GPIO_ReadInputDataBit(gndCheck_6_GPIO_Port,gndCheck_6_Pin)== 1)
			 	bGndCheckValue = 1;
			else
				bGndCheckValue = 0;
		}
		break;
		case GNDCHECKNUM_7:
		{
		 	//bGndCheckValue = READ_GNDCHECK_7();
			if(GPIO_ReadInputDataBit(gndCheck_6_GPIO_Port,gndCheck_6_Pin)== 1)
			 	bGndCheckValue = 1;
			else
				bGndCheckValue = 0;
		}
		break;
		case GNDCHECKNUM_8:
		{
		 	//bGndCheckValue = READ_GNDCHECK_8();
			if(GPIO_ReadInputDataBit(gndCheck_6_GPIO_Port,gndCheck_6_Pin)== 1)
			 	bGndCheckValue = 1;
			else
				bGndCheckValue = 0;
		}
		break;
		default:
			break;
	}
	return bGndCheckValue;
}

BYTE LightCheck_Read(void)
{
	if(GPIO_ReadInputDataBit(lightcheck_GPIO_Port,lightcheck_Pin)== 1)
		return 0;
	else
		return  1;
}

BYTE ReShiDian_Read(void)
{
	if(GPIO_ReadInputDataBit(reshidian_GPIO_Port,reshidian_Pin)== 1)
		return 1;
	else
		return  0;
}

BYTE DoorSwitch_Read(void)
{
	if(GPIO_ReadInputDataBit(doorswitch_GPIO_Port,doorswitch_Pin)== 1)
		return 1;
	else
		return  0;
}
void Compressor_Set(void)
{
	GPIO_ResetBits(compressor_GPIO_Port, compressor_Pin);	
}

void Compressor_Reset(void)
{
	GPIO_SetBits(compressor_GPIO_Port, compressor_Pin);	
}

void Heatbb_Set(void)
{
//	HeatFlag = 1;
	GPIO_ResetBits(yuliu_1_GPIO_Port, yuliu_1_Pin);	
}

void Heatbb_Reset(void)
{
//	HeatFlag = 0;
	GPIO_SetBits(yuliu_1_GPIO_Port, yuliu_1_Pin);	
}

void Lightstrip_Set(void)
{
//	LightStripFlag = 1;
	GPIO_ResetBits(lightstrip_GPIO_Port, lightstrip_Pin);	
}
void Lightstrip_Reset(void)
{
//	LightStripFlag = 0;
	GPIO_SetBits(lightstrip_GPIO_Port, lightstrip_Pin);
}

void Doorlock_Set(void)
{
	GPIO_ResetBits(doorlock_GPIO_Port, doorlock_Pin);	
}
void Doorlock_Reset(void)
{
	GPIO_SetBits(doorlock_GPIO_Port, doorlock_Pin);
}
