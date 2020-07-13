#include "comm.h"
#include "fram.h"
#include "adc.h"

BYTE bServerNum = 0;
BYTE bClientNum = 0;
BYTE bCommLen = 0;
BYTE bVmdCmd = 0;
BYTE bVmdData = 0; 
BYTE bChannelReset = 0;
BYTE bVerNUM = 0;
BYTE bMeciType	= 0;
BYTE bOtherCode = 0;


BYTE bVmdCheckEnd = TURE;
BYTE bVmdResetEnd = TURE;
WORD wRuncnt  = 0;

u8 REV_BUF[USART_REC_LEN];     //
u8 TEMP_REV_BUF[USART_REC_LEN];     //

unsigned int crc_calc(unsigned char ddata[],unsigned char l)
{
    unsigned char p;
    unsigned char q;
    unsigned int crc;
    crc=0xFFFF;
    for(p=0;p<l;p++)
    {
      crc^=ddata[p];
      for(q=0;q<8;q++)
      {
        if((unsigned char)(crc&1)==0)
          crc>>=1;
        else
        {
          crc>>=1;
          crc^=40961;
        }
      }
    }     
    return(crc);              
}


BYTE VMD_CommArrange(void)
{
	DWORD dwRevsize = 0;
	WORD i,j;
	unsigned int crcValue = 0;
	dwRevsize = USART_RX_STA;
	if(USART_RX_STA&0X8000)		//
	{
		dwRevsize &= 0x0fff;
		for(i=0;i<dwRevsize+1;i++)	
		{
			if(USART_RX_BUF[i] == SERVERCOMMHEAD)
			{
				for(j=0;j<dwRevsize+1;j++)
				{
					REV_BUF[j] = USART_RX_BUF[i+j]; 	
				}
				crcValue = REV_BUF[6] + (REV_BUF[7] << 8);
				if(crcValue != crc_calc(REV_BUF,6))
				{
				   UART1SendByte(0xff);
				   UART1SendByte(0xfe);
				   USART_RX_STA = 0; //
					return ERROR_OTHER;
				}
				if(REV_BUF[8] != 0x77)
				{
					UART1SendByte(0xff);
				   UART1SendByte(0x00);
				   USART_RX_STA = 0; //
					return ERROR_OTHER;	
				}
				break;
			}
			if(i == dwRevsize-1)
			{
				USART_RX_STA = 0; //
				return ERROR_OTHER;
			}	
		}
		bVerNUM = REV_BUF[1];
		bMeciType = REV_BUF[2];
		bVmdCmd = REV_BUF[3];	
		bVmdData = REV_BUF[4];
		bOtherCode  = REV_BUF[5];
		USART_RX_STA = 0; //
		return OK;
	}
	return FREE_STATE;
}

void VMD_CommProcess(void)
{
//	WORD wLen;
	BYTE bRetCode;
	BYTE SEND_BUFF[USART_REC_LEN];
	BYTE TEMP_SEND_BUFF[20];
	BYTE bcmdcode = 0x00;
	WORD wBufNum = 0;
	WORD i;
	unsigned int crcValue = 0;
	bRetCode = VMD_CommArrange();
	if(bRetCode == OK && bVmdBusyFlag == FALSE)
	{
		bRetCode = 	FREE_STATE;
		SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
		SEND_BUFF[wBufNum++] = bVerNUM;
		SEND_BUFF[wBufNum++] = bMeciType;

		switch(bVmdCmd)
		{
			case 0x00:
				bcmdcode = 	CONNECT_TEST;
			break;
			case 0x01:
				bcmdcode = 	SALES_STATE;
			break;
			case 0x02:
			  	if(bVmdData == 0xA1)
				{
					bcmdcode = ALL_RESET;
				}
				else
				{
				  	bcmdcode = CHANNEL_RESET;
				}		
			break;
			case 0x03:
				bcmdcode = 	ALL_CHECK;	
			break;
			case 0x04:
				bcmdcode = 	LIGHT_STARE;
			break;
			case 0x05:
				bcmdcode = 	SET_LIGHT_STARE;
			break;
			case 0x06:
				bcmdcode = DOOR_STARE;		
			break;
			case 0x07:
				bcmdcode = SET_DOOR_STARE;	
			break;
			case 0x08:
				bcmdcode = 	HEAT_STARE;
			break;
			case 0x09:
				bcmdcode = 	SET_HEAT_STARE_OPEN;
			break;
			case 0x0A:
				bcmdcode = 	SET_HEAT_STARE_CLOSE;
			break;
			case 0x0B:
				bcmdcode = 	COMPRE_STARE;
			break;
			case 0x0C:
				bcmdcode = 	SET_COMPRE_STARE_OPEN;
			break;
			case 0x0D:
				bcmdcode = 	SET_COMPRE_STARE_CLOSE;
			break;
			case 0x0E:
				bcmdcode = 	INFRA_STARE;
			break;
			case 0x0F:
				bcmdcode = 	INFRA_STARE_NUM;
			break;
			case 0x10:
				bcmdcode = 	SET_INFRA_STARE_ZERO;
			break;
			case 0x11:
				bcmdcode = 	READ_PROBE_TEMP;    //Ì½Í·ÎÂ¶È
			break;
		   case 0x12:
				bcmdcode = 	READ_CTRL_TEMP;    //¿ØÖÆÎÂ¶È
			break;
			case 0x13:
				bcmdcode = 	READ_DIFF_TEMP;    //»Ø²îÎÂ¶È
			break;
			case 0x14:
				 bcmdcode = SET_CTRL_TEMP; 
			break;
			case 0x15:
				 bcmdcode = SET_DIFF_TEMP; 
			break;
		   	case 0x16:
				 bcmdcode = AUTO_TEMP; 
			break;
			case 0x17:
				 bcmdcode = LIGHTSTRIP_STATRE; 
			break;												 
			default:
			break;
		}
				

	//	SEND_BUFF[wBufNum++] = bServerNum;
		switch(bcmdcode)	
		{
			case CONNECT_TEST:
			{
				SEND_BUFF[wBufNum++] = bVmdCmd;	
				SEND_BUFF[wBufNum++] = bVmdData;
				SEND_BUFF[wBufNum++] = bOtherCode;
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
				break;
			}
			case SALES_STATE:
			{
				bVmdCheckEnd = TURE;
				bVmdResetEnd = TURE;
				bLightCheck = 1;

				SEND_BUFF[wBufNum++] = bVmdCmd;	
				SEND_BUFF[wBufNum++] = bVmdData;
				SEND_BUFF[wBufNum++] = bOtherCode;
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
				bChannelReset = FALSE;
				bVmdBusyFlag = TURE;
				if(LightCheckFlag)
				{
				  if(LightCheck_Read() == 0)
				  {
				  	delay_ms(100);
					if(LightCheck_Read() == 0)
					{
						SaleAndLightFlag = 1;
						dwSaleAndlightCnt = 0;
						SaleAndLightCheckOverFlag = 0;
						VMD_SalesControl(bVmdData-1);
					}
					else 
					{
						goto nolight_do;
					}	
				  }
				  else 
				  {
	nolight_do:		wBufNum = 3;
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
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
					bVmdRunningFlag = FALSE;
					bVmdTimeStartFlag = FALSE;
					VMD_MotorReset();
					bVmdBusyFlag = FALSE;
				  }
				}
				else 
				{
					VMD_SalesControl(bVmdData-1);
				}
				//VMD_SelesControlStart(bVmdData-1);
				break;
			}
			case CHANNEL_RESET:	 //  bChannelReset
			{
				bVmdCheckEnd = TURE;
				bVmdResetEnd = TURE;

				SEND_BUFF[wBufNum++] = bVmdCmd;	
				SEND_BUFF[wBufNum++] = bVmdData;
				SEND_BUFF[wBufNum++] = bOtherCode;
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
				bChannelReset = TURE;
				bVmdBusyFlag = TURE;
				VMD_ResetControl(bVmdData-1);

				
				//VMD_ResetControlStart(bVmdData-1);
				break;
			}
			case ALL_CHECK:
			{	 
				if(bVmdData == 0xA3)
				{
					//VMD_AllCheck();
					wRuncnt = 0;
					bVmdCheckEnd = FALSE;
				}
				else
				{
					bVmdCheckEnd = TURE;
				}
				bVmdResetEnd = TURE;
				bChannelReset = FALSE;
				break;
			}
			case ALL_RESET:
			{
				if(bVmdData == 0xA1)
				{
					wRuncnt = 0;
					bVmdResetEnd = FALSE;
				}
				else
				{
					bVmdResetEnd = TURE;	
				}
				bVmdCheckEnd = TURE;
				bChannelReset = TURE;
				break;	
			}
			case LIGHT_STARE:
			{
				if(bOtherCode == 0x30)
				{
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					if(LightCheck_Read() == 1)
					{
						SEND_BUFF[wBufNum++]  = 0xa1;	
					}
					else 
					{
						SEND_BUFF[wBufNum++]  = 0xa2;	
					}
					//SEND_BUFF[wBufNum++] = bOtherCode;
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
			
				
				break;
			}

			case SET_LIGHT_STARE:
			{	
				if(bOtherCode == 0x33)
				{									    
					LightCheckFlag	= 1;
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					SEND_BUFF[wBufNum++] = 0xa3;
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
				else if(bOtherCode == 0x32)
				{
				   	LightCheckFlag = 0;
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					SEND_BUFF[wBufNum++] = 0xa3;
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
				break;	
			}
			

			case DOOR_STARE:
			{
				if(bOtherCode == 0x40)
				{
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					if(DoorSwitch_Read() == 1)
					{
						SEND_BUFF[wBufNum++]  = 0xa5;	
					}
					else 
					{
						SEND_BUFF[wBufNum++]  = 0xa6;	
					}
					//SEND_BUFF[wBufNum++] = bOtherCode;
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
				
				break;
			}

			case SET_DOOR_STARE:
			{
				if(bOtherCode == 0x44)
				{
					Doorlock_Set();
					delay_ms(500);
					Doorlock_Reset();
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					if(DoorSwitch_Read() == 1)
					{
						SEND_BUFF[wBufNum++]  = 0x44;	
					}
					else 
					{
						SEND_BUFF[wBufNum++]  = 0x4f;	
					}
				//	SEND_BUFF[wBufNum++] = 0x44;
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
				break;
			}	
			
			case HEAT_STARE:	  //BYTE HeatFlag
			{
				if(bOtherCode == 0x50)
				{
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					if(HeatFlag == 1)
					{
						SEND_BUFF[wBufNum++]  = 0xa7;	
					}
					else 
					{
						SEND_BUFF[wBufNum++]  = 0xa8;	
					}
					//SEND_BUFF[wBufNum++] = bOtherCode;
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
				break;
			}
			case SET_HEAT_STARE_OPEN:
			{
				if(bOtherCode == 0x55)
				{
					HeatFlag = 1;
					Heatbb_Set();
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					SEND_BUFF[wBufNum++] = 0xa8;
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
				break;
			}
			case SET_HEAT_STARE_CLOSE:
			{
				if(bOtherCode == 0x52)
				{
					HeatFlag = 0;	
					Heatbb_Reset();
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					SEND_BUFF[wBufNum++] = 0xa9;
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
				break;
			}
			case LIGHTSTRIP_STATRE:
			{
				if(bOtherCode == 0xaa)
				{
					Lightstrip_Set();
					LightStripFlag = 1;
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					SEND_BUFF[wBufNum++] = 0xd0;
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
				else if(bOtherCode == 0xa2) 
				{
					Lightstrip_Reset();
					LightStripFlag = 0;
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					SEND_BUFF[wBufNum++] = 0xd0;
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
				break;
			}
			case COMPRE_STARE:	//CompreFlag
			{
				if(bOtherCode == 0x60)
				{
					/****************/
					/*ÎÂ¿ØÆ÷*/
					TEMP_SEND_BUFF[0] = 0x20;	 
					TEMP_SEND_BUFF[1] = 0x18;
					TEMP_SEND_BUFF[2] = 0x30;
					TEMP_SEND_BUFF[3] = 0x00;
					TEMP_SEND_BUFF[4] = 0x78;
					LED(OFF);
					for(i=0;i<5;i++)
					{
						UART3SendByte(TEMP_SEND_BUFF[i]);
					}
					LED(ON);
					/****************/

					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					if(CompreFlag == 1)
					{
						SEND_BUFF[wBufNum++]  = 0xB2;	
					}
					else 
					{
						SEND_BUFF[wBufNum++]  = 0xB3;	
					}
					//SEND_BUFF[wBufNum++] = bOtherCode;
					crcValue = crc_calc(SEND_BUFF,6);
					SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
					SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
					SEND_BUFF[wBufNum++] = CLIENTTAIL;
					LED(OFF);
					for(i=0;i<wBufNum;i++)
					{
					//	UART1SendByte(SEND_BUFF[i]);
					}
					LED(ON);			
				}
			
				
				break;
			}
			case SET_COMPRE_STARE_OPEN:
			{
				if(bOtherCode == 0x66)
				{
				   /****************/
					/*ÎÂ¿ØÆ÷*/
					TEMP_SEND_BUFF[0] = 0x20;	 
					TEMP_SEND_BUFF[1] = 0x18;
					TEMP_SEND_BUFF[2] = 0x40;
					TEMP_SEND_BUFF[3] = 0xF1;
					TEMP_SEND_BUFF[4] = 0x78;
					LED(OFF);
					for(i=0;i<5;i++)
					{
						UART3SendByte(TEMP_SEND_BUFF[i]);
					}
					LED(ON);
					/****************/
					
					CompreFlag = 1;
					Compressor_Set();
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;				
					SEND_BUFF[wBufNum++] = 0xb4;
					crcValue = crc_calc(SEND_BUFF,6);
					SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
					SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
					SEND_BUFF[wBufNum++] = CLIENTTAIL;
					LED(OFF);
					for(i=0;i<wBufNum;i++)
					{
					//	UART1SendByte(SEND_BUFF[i]);
					}
					LED(ON);				
				}
				break;	
			}
			case SET_COMPRE_STARE_CLOSE:
			{
				if(bOtherCode == 0x62)
				{
					/****************/
					/*ÎÂ¿ØÆ÷*/
					TEMP_SEND_BUFF[0] = 0x20;	 
					TEMP_SEND_BUFF[1] = 0x18;
					TEMP_SEND_BUFF[2] = 0x40;
					TEMP_SEND_BUFF[3] = 0xF0;
					TEMP_SEND_BUFF[4] = 0x78;
					LED(OFF);
					for(i=0;i<5;i++)
					{
						UART3SendByte(TEMP_SEND_BUFF[i]);
					}
					LED(ON);
					/****************/
					CompreFlag = 0;
					Compressor_Reset();
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;				
					SEND_BUFF[wBufNum++] = 0xb6;
					crcValue = crc_calc(SEND_BUFF,6);
					SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
					SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
					SEND_BUFF[wBufNum++] = CLIENTTAIL;
					LED(OFF);
					for(i=0;i<wBufNum;i++)
					{
				//		UART1SendByte(SEND_BUFF[i]);
					}
					LED(ON);				
				}
				break;
			}
			case INFRA_STARE:
			{
				if(bOtherCode == 0x70)
				{
				 	SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;
					if(ReShiDian_Read() == 1)
					{
						SEND_BUFF[wBufNum++]  = 0xB8;	
					}
					else 
					{
						SEND_BUFF[wBufNum++]  = 0xB9;	
					}
					//SEND_BUFF[wBufNum++] = bOtherCode;
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
				
				 
				break;
			}
			case INFRA_STARE_NUM:
			{
				if(bOtherCode == 0x7A)
				{
					ReShiDianFlag = 1;
					Write_config_Data();
					SEND_BUFF[wBufNum++] = bVmdCmd;				
					SEND_BUFF[wBufNum++] = ReshidianCnt & 0x00ff ;
					SEND_BUFF[wBufNum++] = (ReshidianCnt & 0x00ff) >> 8;
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
				break;
			}
			case SET_INFRA_STARE_ZERO:
			{
				if(bOtherCode == 0x72)
				{
					ReShiDianFlag = 0;
					ReshidianCnt = 0;
					Write_config_Data();
					SEND_BUFF[wBufNum++] = bVmdCmd;	
					SEND_BUFF[wBufNum++] = bVmdData;				
					SEND_BUFF[wBufNum++] = 0xc0;
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
				break;
			}
			case READ_PROBE_TEMP:
			{
				if(bOtherCode == 0x81)
				{
					unsigned int Get_temp1V = 0;
					/****************/
					/*ÎÂ¿ØÆ÷*/
					TEMP_SEND_BUFF[0] = 0x20;	 
					TEMP_SEND_BUFF[1] = 0x18;
					TEMP_SEND_BUFF[2] = 0x30;
					TEMP_SEND_BUFF[3] = 0x00;
					TEMP_SEND_BUFF[4] = 0x78;
					LED(OFF);
					for(i=0;i<5;i++)
					{
						UART3SendByte(TEMP_SEND_BUFF[i]);
					}
					LED(ON);
					/****************/

				   	SEND_BUFF[wBufNum++] = bVmdCmd;	
					//SEND_BUFF[wBufNum++] = bVmdData;
					Get_temp1V = Get_temp1();
					if(Get_temp1V > 1000)
					{
						SEND_BUFF[wBufNum++] = 0xab;
						SEND_BUFF[wBufNum++]  = Get_temp1V - 1000;	
					}
					else 
					{
						SEND_BUFF[wBufNum++] = 0xaa;
						SEND_BUFF[wBufNum++]  = Get_temp1V;	
					}
					//SEND_BUFF[wBufNum++] = bOtherCode;
					crcValue = crc_calc(SEND_BUFF,6);
					SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
					SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
					SEND_BUFF[wBufNum++] = CLIENTTAIL;
					LED(OFF);
					for(i=0;i<wBufNum;i++)
					{
					//	UART1SendByte(SEND_BUFF[i]);
					}
					LED(ON);
				}
				break;
			}
			case READ_CTRL_TEMP:
			{
				/****************/
				/*ÎÂ¿ØÆ÷*/
				TEMP_SEND_BUFF[0] = 0x20;	 
				TEMP_SEND_BUFF[1] = 0x18;
				TEMP_SEND_BUFF[2] = 0x30;
				TEMP_SEND_BUFF[3] = 0x00;
				TEMP_SEND_BUFF[4] = 0x78;
				LED(OFF);
				for(i=0;i<5;i++)
				{
					UART3SendByte(TEMP_SEND_BUFF[i]);
				}
				LED(ON);
				/****************/
				
			 	SEND_BUFF[wBufNum++] = bVmdCmd;	
				//SEND_BUFF[wBufNum++] = bVmdData;
				if(TempValue > 1000)
				{
					SEND_BUFF[wBufNum++] = 0xab;
					SEND_BUFF[wBufNum++]  = TempValue - 1000;	
				}
				else 
				{
					SEND_BUFF[wBufNum++] = 0xaa;
					SEND_BUFF[wBufNum++]  = TempValue;	
				}
				//SEND_BUFF[wBufNum++] = bOtherCode;
				crcValue = crc_calc(SEND_BUFF,6);
				SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
				SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
				SEND_BUFF[wBufNum++] = CLIENTTAIL;
				LED(OFF);
				for(i=0;i<wBufNum;i++)
				{
				//	UART1SendByte(SEND_BUFF[i]);
				}
				LED(ON);	

			   break;
			}
			case READ_DIFF_TEMP:
			{
				/****************/
				/*ÎÂ¿ØÆ÷*/
				TEMP_SEND_BUFF[0] = 0x20;	 
				TEMP_SEND_BUFF[1] = 0x18;
				TEMP_SEND_BUFF[2] = 0x30;
				TEMP_SEND_BUFF[3] = 0x00;
				TEMP_SEND_BUFF[4] = 0x78;
				LED(OFF);
				for(i=0;i<5;i++)
				{
					UART3SendByte(TEMP_SEND_BUFF[i]);
				}
				LED(ON);
				/****************/
				break;
			}
			case SET_CTRL_TEMP:
			{
				switch(bVmdData)   
				{
					case 0xaa:
					{
						/****************/
						/*ÎÂ¿ØÆ÷*/
						TEMP_SEND_BUFF[0] = 0x20;	 
						TEMP_SEND_BUFF[1] = 0x18;
						TEMP_SEND_BUFF[2] = 0x41;
						TEMP_SEND_BUFF[3] = bOtherCode;
						TEMP_SEND_BUFF[4] = 0x78;
						LED(OFF);
						for(i=0;i<5;i++)
						{
							UART3SendByte(TEMP_SEND_BUFF[i]);
						}
						LED(ON);
						/****************/
						TempValue = bOtherCode;
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = 0xa9;				
						SEND_BUFF[wBufNum++] = 0xc2;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
					//		UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);			
						break;
					}
					case 0xab:
					{
						
						/****************/
						/*ÎÂ¿ØÆ÷*/
						TEMP_SEND_BUFF[0] = 0x20;	 
						TEMP_SEND_BUFF[1] = 0x18;
						TEMP_SEND_BUFF[2] = 0x41;
						TEMP_SEND_BUFF[3] = bOtherCode|0x80;
						TEMP_SEND_BUFF[4] = 0x78;
						LED(OFF);
						for(i=0;i<5;i++)
						{
							UART3SendByte(TEMP_SEND_BUFF[i]);
						}
						LED(ON);
						/****************/

						TempValue = bOtherCode + 1000;
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = 0xa9;				
						SEND_BUFF[wBufNum++] = 0xc3;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
						//	UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);			
						break;
					}
					default:
						break;
				}
				break;
			}
			case SET_DIFF_TEMP:
			{
				switch(bVmdData)   
				{
					case 0xaa:
					{
						/****************/
						/*ÎÂ¿ØÆ÷*/
						TEMP_SEND_BUFF[0] = 0x20;	 
						TEMP_SEND_BUFF[1] = 0x18;
						TEMP_SEND_BUFF[2] = 0x42;
						TEMP_SEND_BUFF[3] = bOtherCode;
						TEMP_SEND_BUFF[4] = 0x78;
						LED(OFF);
						for(i=0;i<5;i++)
						{
							UART3SendByte(TEMP_SEND_BUFF[i]);
						}
						LED(ON);
						/****************/
						TempValue = bOtherCode;
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = 0xa9;				
						SEND_BUFF[wBufNum++] = 0xc4;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
					//		UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);			
						break;
					}
					case 0xab:
					{
						
						/****************/
						/*ÎÂ¿ØÆ÷*/
						TEMP_SEND_BUFF[0] = 0x20;	 
						TEMP_SEND_BUFF[1] = 0x18;
						TEMP_SEND_BUFF[2] = 0x41;
						TEMP_SEND_BUFF[3] = bOtherCode|0x80;
						TEMP_SEND_BUFF[4] = 0x78;
						LED(OFF);
						for(i=0;i<5;i++)
						{
							UART3SendByte(TEMP_SEND_BUFF[i]);
						}
						LED(ON);
						/****************/

						TempValue = bOtherCode + 1000;
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = 0xa9;				
						SEND_BUFF[wBufNum++] = 0xc5;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
						//	UART1SendByte(SEND_BUFF[i]);
						}
						LED(ON);			
						break;
					}
					default:
						break;
				}
				break;
			}
			case AUTO_TEMP:
			{		  
				switch(bVmdData)   
				{
					case 0xa9:
					{ 	
						if(bOtherCode == 0x98)
						{
							TempAutoFlag = 1;
							SEND_BUFF[wBufNum++] = bVmdCmd;	
							SEND_BUFF[wBufNum++] = bVmdData;
							SEND_BUFF[wBufNum++] = bOtherCode;
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
						else if(bOtherCode == 0x99)	
						{
							TempAutoFlag = 0;
							SEND_BUFF[wBufNum++] = bVmdCmd;	
							SEND_BUFF[wBufNum++] = bVmdData;
							SEND_BUFF[wBufNum++] = bOtherCode;
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
						break;
					}	
				}
				break;
			}
			case TEMP_STARE:
			{
				
			}
			default :
				break;
		}
		Write_config_Data();
	}
	else
	{
		;	
	}
   
}


BYTE TEMP_CommArrange(void)
{
	DWORD dwRevsize = 0;
	WORD i,j;
	dwRevsize = USART3_RX_STA;
	if(USART3_RX_STA&0X8000)		//
	{
		dwRevsize &= 0x0fff;
		for(i=0;i<dwRevsize+1;i++)	
		{
			if((USART3_RX_BUF[i] == 0X20)&&(USART3_RX_BUF[i+1] == 0X18))
			{
				for(j=0;j<dwRevsize+1;j++)
				{
					TEMP_REV_BUF[j] = USART3_RX_BUF[i+j]; 	
				}
				break;
			}
			if(i == dwRevsize-1)
			{
				USART3_RX_STA = 0; //
				return ERROR_OTHER;
			}	
		}
		USART3_RX_STA = 0; //
		return OK;
	}
	return FREE_STATE;
}


void TEMP_CommProcess(void)	 //ÎÂ¿ØÆ÷
{
//	WORD wLen;
	BYTE bRetCode;
	BYTE SEND_BUFF[USART_REC_LEN];
//	BYTE bcmdcode = 0x00;
	WORD wBufNum = 0;
	WORD i;
	unsigned int crcValue = 0;
	bRetCode = TEMP_CommArrange();
	if(bRetCode == OK)
	{
		bRetCode = 	FREE_STATE;
		SEND_BUFF[wBufNum++] = CLIENTCOMMHEAD;
		SEND_BUFF[wBufNum++] = bVerNUM;
		SEND_BUFF[wBufNum++] = bMeciType;
		switch(TEMP_REV_BUF[2])
		{
			case 0x30:
			{
				switch(bVmdCmd)
				{
					case 0x0b:
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = 0xA7;
						if(TEMP_REV_BUF[6] == 1)
						{
							SEND_BUFF[wBufNum++] = 0xB2;	
						}
						else 
						{
							SEND_BUFF[wBufNum++] = 0xB3;
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
					break;
					case 0x11:
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						if(TEMP_REV_BUF[3]&0x80)
						{
							SEND_BUFF[wBufNum++] = 0xAB;	
						}
						else 
						{
							SEND_BUFF[wBufNum++] = 0xAA;
						}									  
						SEND_BUFF[wBufNum++] = TEMP_REV_BUF[3]&0x7f;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
							UART1SendByte(SEND_BUFF[i]);
						}
					break;
					case 0x12:
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						if(TEMP_REV_BUF[4]&0x80)
						{
							SEND_BUFF[wBufNum++] = 0xAB;	
						}
						else 
						{
							SEND_BUFF[wBufNum++] = 0xAA;
						}									  
						SEND_BUFF[wBufNum++] = TEMP_REV_BUF[4]&0x7f;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
							UART1SendByte(SEND_BUFF[i]);
						}
					break;
					case 0x13:
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						if(TEMP_REV_BUF[5]&0x80)
						{
							SEND_BUFF[wBufNum++] = 0xAB;	
						}
						else 
						{
							SEND_BUFF[wBufNum++] = 0xAA;
						}									  
						SEND_BUFF[wBufNum++] = TEMP_REV_BUF[5]&0x7f;
						crcValue = crc_calc(SEND_BUFF,6);
						SEND_BUFF[wBufNum++] = crcValue & 0x00ff;
						SEND_BUFF[wBufNum++] = (crcValue  & 0xff00 ) >> 8;
						SEND_BUFF[wBufNum++] = CLIENTTAIL;
						LED(OFF);
						for(i=0;i<wBufNum;i++)
						{
							UART1SendByte(SEND_BUFF[i]);
						}
					break;

					default:
					break;
				}				
			}
			break;
			case 0x40:
			{
				switch(bVmdCmd)
				{
					case 0x0c:	  //Ñ¹Ëõ»ú¿ªÆô
					{
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = bVmdData; 
						if(TEMP_REV_BUF[3] == 1)
						{
							SEND_BUFF[wBufNum++] = 0xB4;	
						}
						else 
						{
							SEND_BUFF[wBufNum++] = 0xB5;
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
					}
					break;
					
					case 0x0d:		//Ñ¹Ëõ»ú¹Ø±Õ
					{
						SEND_BUFF[wBufNum++] = bVmdCmd;	
						SEND_BUFF[wBufNum++] = bVmdData; 
						if(TEMP_REV_BUF[3] == 1)
						{
							SEND_BUFF[wBufNum++] = 0xB6;	
						}
						else 
						{
							SEND_BUFF[wBufNum++] = 0xB7;
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
					}
					break;

					default:
					break;
				}
			}
			break;	
			
			case 0x41:
			{
				SEND_BUFF[wBufNum++] = bVmdCmd;	
				SEND_BUFF[wBufNum++] = 0xa9; 
				if(TEMP_REV_BUF[3] == 1)
				{
					SEND_BUFF[wBufNum++] = 0xc2;	
				}
				else 
				{
					SEND_BUFF[wBufNum++] = 0xc3;
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
			}
			break; 

			case 0x42:
			{
				SEND_BUFF[wBufNum++] = bVmdCmd;	
				SEND_BUFF[wBufNum++] = 0xa9; 
				if(TEMP_REV_BUF[3] == 1)
				{
					SEND_BUFF[wBufNum++] = 0xc4;	
				}
				else 
				{
					SEND_BUFF[wBufNum++] = 0xc5;
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
			}
			break; 
		}
	}
	else
	{
		;	
	}
}

void Output_Init(void)
{
	if(HeatFlag == 1)
	{
		Heatbb_Set();	
	}
	else 
	{
		Heatbb_Reset();
	}

	if(LightStripFlag == 1)
	{
		Lightstrip_Set();	
	}
	else 
	{
		Lightstrip_Reset();
	}

	if(CompreFlag == 1)
	{
		Compressor_Set();
	}
	else 
	{
		Compressor_Reset();
	}
}

	   
void Read_Config_Data(void)
{
	u8 buf[20];
	Fram_Read_Data( 0x00,buf,10 );
	LightCheckFlag = buf[0];
	HeatFlag = buf[1];
	CompreFlag = buf[2];
	ReShiDianFlag = buf[3];
	LightStripFlag = buf[4];
	TempAutoFlag = buf[5];

	TempValue = buf[6];	
	TempValue |= (unsigned int)buf[7]<<8;

	ReshidianCnt = buf[8];
	ReshidianCnt |= (unsigned int)buf[9]<<8;

	if((LightCheckFlag !=0)&&(LightCheckFlag !=1)) 
	{
		LightCheckFlag = 0;
	}
	if((HeatFlag !=0)&&(HeatFlag !=1)) 
	{
		HeatFlag = 0;
	}
	if((CompreFlag !=0)&&(CompreFlag !=1)) 
	{
		CompreFlag = 0;
	}
	if((ReShiDianFlag !=0)&&(ReShiDianFlag !=1)) 
	{
		ReShiDianFlag = 0;
	}
	if((LightStripFlag !=0)&&(LightStripFlag !=1)) 
	{
		LightStripFlag = 0;
	}
	if((TempAutoFlag !=0)&&(TempAutoFlag !=1)) 
	{
		TempAutoFlag = 0;
	}
}

void Write_config_Data(void)
{
	u8 buf[20];	
	buf[0] = (u8)LightCheckFlag;
	buf[1] = (u8)HeatFlag;
	buf[2] = (u8)CompreFlag	;
	buf[3] = (u8)ReShiDianFlag;
	buf[4] = (u8)LightStripFlag	;
	buf[5] = (u8)TempAutoFlag;

	buf[6] = (u8)TempValue;
	buf[7] = (u8)(TempValue	>> 8);

	buf[8] = (u8)ReshidianCnt;
	buf[9] = (u8)(ReshidianCnt	>> 8);
	Fram_Write_Data(0x00,buf,10 );
}

