#include "vmddir.h"


DWORD dwVmdTimeStartCnt = 0;
DWORD dwVmdTimeRunCnt = 0;
DWORD dwSaleAndlightCnt = 0;
BYTE bVmdTimeStartCntFlag = 0;
BYTE bVmdTimeRunCntFlag = 0;
BYTE bVmdTimeStartFlag = 0;
BYTE bVmdTimeRunFlag = 0;

BYTE bVmdRunningFlag = 0;
BYTE bVmdBusyFlag = 0;
BYTE bRunEndFlag = 0;

BYTE bLightCheck = 0;

WORD wSaleChannelTemp ;

void HorCom_OFF(IN WORD wHorNum)
{
	int i;
	for(i=0;i<HORNUM_MAX;i++)
	{
		HorState_Set(i);	
	}
//	HorState_Set(wHorNum);
	HorState_Reset(wHorNum);
}

void  HorCom_ON(IN WORD wHorNum)
{
	int i;
	for(i=0;i<HORNUM_MAX;i++)
	{
		HorState_Reset(i);	
	}
//	HorState_Reset(wHorNum);
	HorState_Set(wHorNum);
}

void VerGnd_OFF(IN WORD wHorNum)
{
	int i;
	for(i=0;i<VERNUM_MAX;i++)
	{
		VerState_Reset(i);	
	}
//	VerState_Set(wHorNum);
	VerState_Set(wHorNum);
}

void VerGnd_ON(IN WORD wHorNum)
{
	int i;
	for(i=0;i<VERNUM_MAX;i++)
	{
		VerState_Set(i);	
	}
//	VerState_Reset(wHorNum);
	VerState_Reset(wHorNum);
}

void VMD_MotorInit(void)
{
	WORD i;
	for(i=0;i<HORNUM_MAX;i++)
	{
		HorCom_OFF(i);
		
	}
	for(i=0;i<VERNUM_MAX;i++)
	{
		VerGnd_ON(i);
	}
}

void VMD_MotoAllOff(void)
{
	WORD i;
	for(i=0;i<HORNUM_MAX;i++)
	{
		HorState_Reset(i);
	}
	for(i=0;i<VERNUM_MAX;i++)
	{
		VerState_Set(i);
	}  
	delay_ms(2);	
}

void VMD_MotorReset(void)
{
	VMD_MotoAllOff();	
}

void VMD_MotorRun(IN WORD wMotorNum)
{
	WORD wHorNum,wVerNum;

	if(wMotorNum > (HORNUM_MAX*HORNUM_MAX))
	{
		VMD_MotorReset();
		return;
	}

	wHorNum = wMotorNum % 10;
	wVerNum = wMotorNum / 10;

	VMD_MotorReset();
	HorCom_ON(wHorNum);
	VerGnd_ON(wVerNum);
}

BYTE VMD_SigRetRead(IN WORD wMotorNum)
{
	WORD wVerNum;
	BYTE bRetSigRet;
	bRetSigRet = ERROR_OTHER;
	if(wMotorNum > (HORNUM_MAX*HORNUM_MAX))
	{
		VMD_MotorReset();
		return ERROR_OTHER;
	}

	wVerNum = wMotorNum / 10;
	bRetSigRet = SigReturn_Read(wVerNum);
	return bRetSigRet;
}

BYTE VMD_GndCheckRead(IN WORD wMotorNum)
{
	WORD wVerNum;
	BYTE bRetGndCheck;
	bRetGndCheck = ERROR_OTHER;
	if(wMotorNum > (HORNUM_MAX*HORNUM_MAX))
	{
		VMD_MotorReset();
		return ERROR_OTHER;
	}

	wVerNum = wMotorNum / 10;
	bRetGndCheck = GndCheck_Read(wVerNum);
	return bRetGndCheck;
}

BYTE VMD_MotorIfExit(IN WORD wMotorNum)
{
	WORD wHorNum;// = wMotorNum % 10;
	wHorNum = wMotorNum % 10;
	VMD_MotorReset();
	HorCom_ON(wHorNum);
	delay_ms(1);
	if(VMD_GndCheckRead(wMotorNum) == GNDCHECKMOTOR)
	{
		VMD_MotorReset();
		return TURE;
	}
	VMD_MotorReset();
	return FALSE;	
}

BYTE VMD_SingleIfReset(IN WORD wMotorNum)
{
	WORD wVerNum,wHorNum;// = wMotorNum % 10;
	wVerNum = wMotorNum / 10;
	wHorNum = wMotorNum % 10;
	VMD_MotorReset();
	VerGnd_ON(wVerNum);
	HorCom_ON(wHorNum);
	delay_ms(1);
	 if(VMD_SigRetRead(wMotorNum) == SIGRETRESET)
	 {
	 	VMD_MotorReset();
	 	return TURE;
	 }
	 VMD_MotorReset();
	 return FALSE;
}

void VMD_SalesControl(IN WORD wSaleChannel)
{
//	BYTE bRetCode;
	BYTE SEND_BUFF[USART_REC_LEN];
	WORD wBufNum = 0;
	WORD i;
	unsigned int crcValue = 0;
	bVmdRunningFlag = FALSE;	 
	if(VMD_MotorIfExit(wSaleChannel) != TURE)
	{
		SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
		SEND_BUFF[wBufNum++] = bVerNUM;
		SEND_BUFF[wBufNum++] = bMeciType;

		SEND_BUFF[wBufNum++] = bVmdCmd;	
		SEND_BUFF[wBufNum++] = bVmdData;
		SEND_BUFF[wBufNum++] = ERROR_NOMOTOR;
		crcValue = crc_calc(SEND_BUFF,6);
		SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
		SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
		SEND_BUFF[wBufNum++] = CLIENTTAIL;

		LED(OFF);
		for(i=0;i<wBufNum;i++)
		{
			UART1SendByte(SEND_BUFF[i]);
		}
		LED(ON);
		bVmdRunningFlag = FALSE;
		bVmdTimeStartFlag = FALSE;
		VMD_MotorReset();
		bVmdBusyFlag = FALSE;
		return;				 
	}
	else if(VMD_SingleIfReset(wSaleChannel)!=TURE)
	{
		SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
		SEND_BUFF[wBufNum++] = bVerNUM;
		SEND_BUFF[wBufNum++] = bMeciType;

		SEND_BUFF[wBufNum++] = bVmdCmd;	
		SEND_BUFF[wBufNum++] = bVmdData;
		SEND_BUFF[wBufNum++] = ERROR_NOPALCE;
		crcValue = crc_calc(SEND_BUFF,6);
		SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
		SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
		SEND_BUFF[wBufNum++] = CLIENTTAIL;
		LED(OFF);
		for(i=0;i<wBufNum;i++)
		{
			UART1SendByte(SEND_BUFF[i]);
		}
		LED(ON);
		bVmdRunningFlag = FALSE;
		bVmdTimeStartFlag = FALSE;
		VMD_MotorReset();
		bVmdBusyFlag = FALSE;
		return;	
	}

//	if(bLightCheck == 0)
//	{
//		SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
//		SEND_BUFF[wBufNum++] = bVerNUM;
//		SEND_BUFF[wBufNum++] = bMeciType;
//
//		SEND_BUFF[wBufNum++] = bVmdCmd;	
//		SEND_BUFF[wBufNum++] = bVmdData;
//		SEND_BUFF[wBufNum++] = ERROR_NOLIGHT;
//		crcValue = crc_calc(SEND_BUFF,6);
//		SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
//		SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
//		SEND_BUFF[wBufNum++] = CLIENTTAIL;
//		LED(OFF);
//		for(i=0;i<wBufNum;i++)
//		{
//			UART1SendByte(SEND_BUFF[i]);
//		}
//		LED(ON);
//		bVmdRunningFlag = FALSE;
//		bVmdTimeStartFlag = FALSE;
//		VMD_MotorReset();
//		bVmdBusyFlag = FALSE;
//		return;		
//	}

//	SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
//	SEND_BUFF[wBufNum++] = bVerNUM;
//	SEND_BUFF[wBufNum++] = bMeciType;
//
//	SEND_BUFF[wBufNum++] = bVmdCmd;	
//	SEND_BUFF[wBufNum++] = bVmdData;
//	SEND_BUFF[wBufNum++] = SALE_MOTOR_OK;
//	crcValue = crc_calc(SEND_BUFF,6);
//	SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
//	SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
//	SEND_BUFF[wBufNum++] = CLIENTTAIL;
	if(bVmdCheckEnd == TURE)
	{
		VMD_MotorRun(wSaleChannel);	
	}
	bVmdRunningFlag = TURE;	
	bRunEndFlag = FALSE;
	bVmdTimeStartCntFlag = TURE;
	bVmdTimeStartFlag = FALSE;
	dwVmdTimeStartCnt = 0;
	bVmdTimeRunCntFlag = TURE;
	bVmdTimeRunFlag	= FALSE;
	dwVmdTimeRunCnt = 0;
	wSaleChannelTemp = wSaleChannel;  

	bVmdBusyFlag = TURE;
}

void VMD_ResetControl(IN WORD wSaleChannel)
{
//	BYTE bRetCode;
	BYTE SEND_BUFF[USART_REC_LEN];
	WORD wBufNum = 0;
	WORD i;
	unsigned int crcValue = 0;
	bVmdRunningFlag = FALSE;
	if(VMD_MotorIfExit(wSaleChannel) != TURE)
	{
		SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
		SEND_BUFF[wBufNum++] = bVerNUM;
		SEND_BUFF[wBufNum++] = bMeciType;

		SEND_BUFF[wBufNum++] = bVmdCmd;	
		SEND_BUFF[wBufNum++] = bVmdData;
		SEND_BUFF[wBufNum++] = ERROR_NOMOTOR;
		crcValue = crc_calc(SEND_BUFF,6);
		SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
		SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
		SEND_BUFF[wBufNum++] = CLIENTTAIL;
		LED(OFF);
		for(i=0;i<wBufNum;i++)
		{
			UART1SendByte(SEND_BUFF[i]);
		}
		LED(ON);
		bVmdRunningFlag = FALSE;
		bVmdTimeStartFlag = FALSE;
		VMD_MotorReset();
		bVmdBusyFlag = FALSE;
		return;				 
	}
	else if(VMD_SingleIfReset(wSaleChannel)== TURE)
	{
		bVmdRunningFlag = FALSE;
		dwVmdTimeRunCnt = 0;
		bVmdTimeRunFlag = FALSE;
		bVmdTimeRunCntFlag = FALSE;
		dwVmdTimeStartCnt = 0;
		bVmdTimeStartFlag = FALSE;
		bVmdTimeStartCntFlag = FALSE;
		VMD_MotorReset();	
		SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
		SEND_BUFF[wBufNum++] = bVerNUM;
		SEND_BUFF[wBufNum++] = bMeciType;
	
		SEND_BUFF[wBufNum++] = bVmdCmd;	
		SEND_BUFF[wBufNum++] = bVmdData;
		SEND_BUFF[wBufNum++] = RESET_CHAN_OK;
		crcValue = crc_calc(SEND_BUFF,6);
		SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
		SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
		SEND_BUFF[wBufNum++] = CLIENTTAIL;
		LED(OFF);
		for(i=0;i<wBufNum;i++)
		{
			UART1SendByte(SEND_BUFF[i]);
		}
		LED(ON);
		bVmdBusyFlag = FALSE;
		return;				
	}

//	SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
//	SEND_BUFF[wBufNum++] = bVerNUM;
//	SEND_BUFF[wBufNum++] = bMeciType;
//
//	SEND_BUFF[wBufNum++] = bVmdCmd;	
//	SEND_BUFF[wBufNum++] = bVmdData;
//	SEND_BUFF[wBufNum++] = RESET_MOTOR_OK;
//	crcValue = crc_calc(SEND_BUFF,6);
//	SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
//	SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
//	SEND_BUFF[wBufNum++] = CLIENTTAIL;

	VMD_MotorRun(wSaleChannel);	
	bVmdRunningFlag = TURE;	
	bRunEndFlag = FALSE;
	bVmdTimeStartCntFlag = TURE;
	bVmdTimeStartFlag = FALSE;
	dwVmdTimeStartCnt = 0;
	bVmdTimeRunCntFlag = TURE;
	bVmdTimeRunFlag	= FALSE;
	dwVmdTimeRunCnt = 0;
	wSaleChannelTemp = wSaleChannel; 
	
	bVmdBusyFlag = TURE; 
}

void VMD_ErrCheck(void)
{
	BYTE SEND_BUFF[USART_REC_LEN];
	WORD wBufNum = 0;
	WORD i;
	unsigned int crcValue = 0;
	if(bVmdRunningFlag == TURE)
	{
		if(bVmdTimeStartFlag == TURE)
		{
			if(bVmdTimeRunFlag == TURE)
			{
				SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
				SEND_BUFF[wBufNum++] = bVerNUM;
				SEND_BUFF[wBufNum++] = bMeciType;
		
				SEND_BUFF[wBufNum++] = bVmdCmd;	
				SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
				SEND_BUFF[wBufNum++] = ERROR_TIMEOUT;
				crcValue = crc_calc(SEND_BUFF,6);
				SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
				SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
				SEND_BUFF[wBufNum++] = CLIENTTAIL;
				LED(OFF);
				for(i=0;i<wBufNum;i++)
				{
					UART1SendByte(SEND_BUFF[i]);
				}
				LED(ON);
				bVmdRunningFlag = FALSE;
				dwVmdTimeRunCnt = 0;
				bVmdTimeRunFlag = FALSE;
				bVmdTimeRunCntFlag = FALSE;
				dwVmdTimeStartCnt = 0;
				bVmdTimeStartFlag = FALSE;
				bVmdTimeStartCntFlag = FALSE;
				VMD_MotorReset();
				
				bVmdBusyFlag = FALSE;	
			}
			if((VMD_SigRetRead(wSaleChannelTemp) == SIGRETRESET))
			{
				bVmdRunningFlag = FALSE;
				dwVmdTimeRunCnt = 0;
				bVmdTimeRunFlag = FALSE;
				bVmdTimeRunCntFlag = FALSE;
				dwVmdTimeStartCnt = 0;
				bVmdTimeStartFlag = FALSE;
				bVmdTimeStartCntFlag = FALSE;
				VMD_MotorReset();	

				if((LightCheckFlag == 0)|| (bChannelReset == TURE))
				{
					SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
					SEND_BUFF[wBufNum++] = bVerNUM;
					SEND_BUFF[wBufNum++] = bMeciType;
					
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
				//	SEND_BUFF[wBufNum++] = SALE_MOTOR_OK;
	
//					if(bLightCheck == 0)
//					{
//						SEND_BUFF[wBufNum++] = ERROR_NOLIGHT;	
//					}			
					if(bChannelReset == TURE)
					{
						bChannelReset = FALSE;
						SEND_BUFF[wBufNum++] = RESET_CHAN_OK;
					}
					else
					{	
						SEND_BUFF[wBufNum++] = SALE_MOTOR_OK;
					}
					
					crcValue = crc_calc(SEND_BUFF,6);
					SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
					SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
					SEND_BUFF[wBufNum++] = CLIENTTAIL;
						
					LED(OFF);
					for(i=0;i<wBufNum;i++)
					{
						UART1SendByte(SEND_BUFF[i]);
					}
					LED(ON);
				}	
					bVmdBusyFlag = FALSE;
			//			
			}
			
		}
//		bVmdTimeStartCntFlag = TURE;
//		if((bVmdTimeStartFlag == TURE) && (VMD_SigRetRead(wSaleChannelTemp) == SIGRETRESET))
//		{
//			SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
//			SEND_BUFF[wBufNum++] = bClientNum;
//			SEND_BUFF[wBufNum++] = bCommLen;
//			SEND_BUFF[wBufNum++] = bServerNum;
//			SEND_BUFF[wBufNum++] = RUN_ERR;	
//			SEND_BUFF[wBufNum++] = ERROR_NOMOTOR;
//			for(i=0;i<wBufNum;i++)
//			{
//				UART1SendByte(SEND_BUFF[i]);
//			}
//			bVmdRunningFlag = FALSE;
//			bVmdTimeStartFlag = FALSE;
//			VMD_MotorReset();	
//		}
//		else if(VMD_SigRetRead(wSaleChannelTemp) != SIGRETRESET) 
//		{
////			bVmdTimeRunCntFlag = TURE;
//			bRunEndFlag	= TURE;
//			bVmdTimeStartCntFlag = FALSE;
//			bVmdTimeStartFlag = FALSE;
//			dwVmdTimeStartCnt = 0;
//			if(bVmdTimeRunFlag == TURE)
//			{
//				SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
//				SEND_BUFF[wBufNum++] = bClientNum;
//				SEND_BUFF[wBufNum++] = bCommLen;
//				SEND_BUFF[wBufNum++] = bServerNum;
//				SEND_BUFF[wBufNum++] = RUN_ERR;	
//				SEND_BUFF[wBufNum++] = ERROR_TIMEOUT;
//				for(i=0;i<wBufNum;i++)
//				{
//					UART1SendByte(SEND_BUFF[i]);
//				}
//				bVmdRunningFlag = FALSE;
//				bVmdTimeRunFlag = FALSE;
//				VMD_MotorReset();	
//			}
//		}
//		else if((VMD_SigRetRead(wSaleChannelTemp) == SIGRETRESET)&& (bRunEndFlag ==TURE))
//		{
//			VMD_MotorReset();
//			bVmdTimeRunCntFlag = FALSE;
//			dwVmdTimeRunCnt = 0;
//			bVmdTimeRunFlag = FALSE;
//			
//			bVmdRunningFlag = FALSE;
//			
//			SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
//			SEND_BUFF[wBufNum++] = bClientNum;
//			SEND_BUFF[wBufNum++] = bCommLen;
//			SEND_BUFF[wBufNum++] = bServerNum;
//			if(bChannelReset == TURE)
//			{
//				bChannelReset = FALSE;
//				SEND_BUFF[wBufNum++] = RESET_OK;
//			}
//			else
//			{	
//				SEND_BUFF[wBufNum++] = SALES_OK;
//			}	
//			SEND_BUFF[wBufNum++] = wSaleChannelTemp;
//			for(i=0;i<wBufNum;i++)
//			{
//				UART1SendByte(SEND_BUFF[i]);
//			}	
//		}				
	}
}

void VMD_LightCheck(void)
{
	BYTE SEND_BUFF[USART_REC_LEN];
	WORD wBufNum = 0;
	WORD i;
	unsigned int crcValue = 0;
	if((LightCheckFlag == 1)&&(SaleAndLightFlag == 0)&&(SaleAndLightCheckOverFlag == 1))
	{
		if(bLightCheck == 0)
		{
			//bLightCheck = 1;
			SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
			SEND_BUFF[wBufNum++] = bVerNUM;
			SEND_BUFF[wBufNum++] = bMeciType;
			
			SEND_BUFF[wBufNum++] = bVmdCmd;	
			SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
			SEND_BUFF[wBufNum++] = SALE_MOTOR_OK;
			crcValue = crc_calc(SEND_BUFF,6);
			SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
			SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
			SEND_BUFF[wBufNum++] = CLIENTTAIL;
				
			LED(OFF);
			for(i=0;i<wBufNum;i++)
			{
				UART1SendByte(SEND_BUFF[i]);
			}
			LED(ON);

		//	bVmdBusyFlag = FALSE;
			
		} 
		else
		{
			SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
			SEND_BUFF[wBufNum++] = bVerNUM;
			SEND_BUFF[wBufNum++] = bMeciType;
			
			SEND_BUFF[wBufNum++] = bVmdCmd;	
			SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
			SEND_BUFF[wBufNum++] = ERROR_NOLIGHT;
			crcValue = crc_calc(SEND_BUFF,6);
			SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
			SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
			SEND_BUFF[wBufNum++] = CLIENTTAIL;
				
			LED(OFF);
			for(i=0;i<wBufNum;i++)
			{
				UART1SendByte(SEND_BUFF[i]);
			}
			LED(ON);	
		}
		 SaleAndLightCheckOverFlag = FALSE;//0
	}
}


void VMD_AllCheck(IN WORD wSaleChannel)
{
	WORD i;
	BYTE cyc;
	BYTE SEND_BUFF[USART_REC_LEN];
	WORD wBufNum = 0;
	unsigned int crcValue = 0;
	cyc = 1;
	if(VMD_MotorIfExit(wSaleChannel) == TURE)
	{
		VMD_SalesControl(wSaleChannel);
		bVmdBusyFlag = FALSE;
		while(cyc)
		{
			if(bVmdRunningFlag == TURE)
			{
				if(bVmdTimeStartFlag == TURE)
				{
					if(bVmdTimeRunFlag == TURE)
					{
						SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
						SEND_BUFF[wBufNum++] = bVerNUM;
						SEND_BUFF[wBufNum++] = bMeciType;
				
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
						SEND_BUFF[wBufNum++] = 0xa0;//ERROR_TIMEOUT;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
							UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);
						bVmdRunningFlag = FALSE;
						dwVmdTimeRunCnt = 0;
						bVmdTimeRunFlag = FALSE;
						bVmdTimeRunCntFlag = FALSE;
						dwVmdTimeStartCnt = 0;
						bVmdTimeStartFlag = FALSE;
						bVmdTimeStartCntFlag = FALSE;
						VMD_MotorReset();

						bVmdBusyFlag = FALSE;
						cyc = 0;	
					}
					if((VMD_SigRetRead(wSaleChannelTemp) == SIGRETRESET))
					{
						bVmdRunningFlag = FALSE;
						dwVmdTimeRunCnt = 0;
						bVmdTimeRunFlag = FALSE;
						bVmdTimeRunCntFlag = FALSE;
						dwVmdTimeStartCnt = 0;
						bVmdTimeStartFlag = FALSE;
						bVmdTimeStartCntFlag = FALSE;
						VMD_MotorReset();	
						SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
						SEND_BUFF[wBufNum++] = bVerNUM;
						SEND_BUFF[wBufNum++] = bMeciType;
					
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
						SEND_BUFF[wBufNum++] = CHECK_CHAN_OK;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
							UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);

						if(wSaleChannelTemp >= 80)
						{
							delay_ms(100);
							SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
							SEND_BUFF[wBufNum++] = bVerNUM;
							SEND_BUFF[wBufNum++] = bMeciType;
						
							SEND_BUFF[wBufNum++] = bVmdCmd;	
							SEND_BUFF[wBufNum++] = 0xA3;
							SEND_BUFF[wBufNum++] = CHECK_ALLCHAN_OK;
							crcValue = crc_calc(SEND_BUFF,6);
							SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
							SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
							SEND_BUFF[wBufNum++] = CLIENTTAIL;
							
						}
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
							UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);

						bVmdBusyFlag = FALSE;
						cyc = 0;		
					}
				}
			}
			else 
			{
				bVmdRunningFlag = FALSE;
				dwVmdTimeRunCnt = 0;
				bVmdTimeRunFlag = FALSE;
				bVmdTimeRunCntFlag = FALSE;
				dwVmdTimeStartCnt = 0;
				bVmdTimeStartFlag = FALSE;
				bVmdTimeStartCntFlag = FALSE;
				VMD_MotorReset();
				
				bVmdBusyFlag = FALSE;	
				cyc = 0;	
			}
		}		
	}
	else 
	{
		SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
		SEND_BUFF[wBufNum++] = bVerNUM;
		SEND_BUFF[wBufNum++] = bMeciType;

		SEND_BUFF[wBufNum++] = bVmdCmd;	
		SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
		SEND_BUFF[wBufNum++] = 0xa0;//ERROR_NOMOTOR;
		crcValue = crc_calc(SEND_BUFF,6);
		SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
		SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
		SEND_BUFF[wBufNum++] = CLIENTTAIL;
		LED(OFF);
		for(i=0;i<wBufNum;i++)
		{
			UART1SendByte(SEND_BUFF[i]);
		}
		LED(ON);

		bVmdBusyFlag = FALSE;
	}
}



void VMD_AllReset(IN WORD wSaleChannel)
{
	WORD i;
	BYTE cyc;
	BYTE SEND_BUFF[USART_REC_LEN];
	WORD wBufNum = 0;
	unsigned int crcValue = 0;
	cyc = 1;
    if(VMD_MotorIfExit(wSaleChannel) == TURE)
    {
        VMD_ResetControl(wSaleChannel);
		bVmdBusyFlag = FALSE;
		while(cyc)
		{
			if(bVmdRunningFlag == TURE)
			{
				if(bVmdTimeStartFlag == TURE)
				{
					if(bVmdTimeRunFlag == TURE)
					{
						SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
						SEND_BUFF[wBufNum++] = bVerNUM;
						SEND_BUFF[wBufNum++] = bMeciType;
				
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
						SEND_BUFF[wBufNum++] = ERROR_TIMEOUT;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
							UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);
						bVmdRunningFlag = FALSE;
						dwVmdTimeRunCnt = 0;
						bVmdTimeRunFlag = FALSE;
						bVmdTimeRunCntFlag = FALSE;
						dwVmdTimeStartCnt = 0;
						bVmdTimeStartFlag = FALSE;
						bVmdTimeStartCntFlag = FALSE;
						VMD_MotorReset();
						bVmdBusyFlag = FALSE;
						cyc = 0;	
					}
					if((VMD_SigRetRead(wSaleChannelTemp) == SIGRETRESET))
					{
						bVmdRunningFlag = FALSE;
						dwVmdTimeRunCnt = 0;
						bVmdTimeRunFlag = FALSE;
						bVmdTimeRunCntFlag = FALSE;
						dwVmdTimeStartCnt = 0;
						bVmdTimeStartFlag = FALSE;
						bVmdTimeStartCntFlag = FALSE;
						VMD_MotorReset();	
						SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
						SEND_BUFF[wBufNum++] = bVerNUM;
						SEND_BUFF[wBufNum++] = bMeciType;
					
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
						SEND_BUFF[wBufNum++] = RESET_CHAN_OK;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
							UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);
						if(wSaleChannelTemp >= 80)
						{
							delay_ms(100);
							SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
							SEND_BUFF[wBufNum++] = bVerNUM;
							SEND_BUFF[wBufNum++] = bMeciType;
						
							SEND_BUFF[wBufNum++] = bVmdCmd;	
							SEND_BUFF[wBufNum++] = 0xA2;
							SEND_BUFF[wBufNum++] = RESET_CHAN_OK;
							crcValue = crc_calc(SEND_BUFF,6);
							SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
							SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
							SEND_BUFF[wBufNum++] = CLIENTTAIL;
						}

						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
							UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);
						bVmdBusyFlag = FALSE;
						cyc = 0;		
					}
				}
			}
			else 
			{
				bVmdRunningFlag = FALSE;
				dwVmdTimeRunCnt = 0;
				bVmdTimeRunFlag = FALSE;
				bVmdTimeRunCntFlag = FALSE;
				dwVmdTimeStartCnt = 0;
				bVmdTimeStartFlag = FALSE;
				bVmdTimeStartCntFlag = FALSE;
				VMD_MotorReset();
				bVmdBusyFlag = FALSE;	
				cyc = 0;	
			}	
		} 
    }
    else
    {
    	SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
		SEND_BUFF[wBufNum++] = bVerNUM;
		SEND_BUFF[wBufNum++] = bMeciType;

		SEND_BUFF[wBufNum++] = bVmdCmd;	
		SEND_BUFF[wBufNum++] = wSaleChannelTemp+1;
		SEND_BUFF[wBufNum++] = ERROR_NOMOTOR;
		crcValue = crc_calc(SEND_BUFF,6);
		SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
		SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
		SEND_BUFF[wBufNum++] = CLIENTTAIL;
		LED(OFF);
		for(i=0;i<wBufNum;i++)
		{
			UART1SendByte(SEND_BUFF[i]);
		}  
		LED(ON);  
		bVmdBusyFlag = FALSE;
    }	
}

void VMD_SelesControlStart(IN WORD wSaleChannel)
{
	VMD_AllCheck(wSaleChannel);
}
void VMD_ResetControlStart(IN WORD wSaleChannel)
{
	VMD_AllReset(wSaleChannel);
}



