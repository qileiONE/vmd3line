#ifndef __COMM_H
#define	__COMM_H

#include "stm32f10x.h"
#include "config.h"
#include "usart.h"
#include "vmddir.h"

#define SERVERCOMMHEAD		0xAD
#define CLIENTCOMMHEAD		0xFC
#define SERVERTAIL			0x77
#define	CLIENTTAIL			0x88

#define CONNECT_TEST	0x01
#define SALES_STATE		0x24
#define CHANNEL_RESET	0x32
#define ALL_RESET		0x37
#define	ALL_CHECK		0x38
#define	LIGHT_STARE		0x39
#define	DOOR_STARE		0x40
#define	HEAT_STARE		0x41
#define	COMPRE_STARE	0x42
#define	INFRA_STARE		0x43
#define	TEMP_STARE		0x44
#define LIGHTSTRIP_STATRE  0x45
#define SET_LIGHT_STARE	  0x46
#define SET_DOOR_STARE	 0x47
#define SET_HEAT_STARE_OPEN  0x48
#define SET_HEAT_STARE_CLOSE  0x49
#define SET_COMPRE_STARE_OPEN  0x50
#define SET_COMPRE_STARE_CLOSE 0x51
#define INFRA_STARE_NUM		0x52
#define SET_INFRA_STARE_ZERO 0x53
#define READ_PROBE_TEMP		0x54
#define READ_CTRL_TEMP 		0x55
#define READ_DIFF_TEMP		0x56
#define SET_CTRL_TEMP		0x57
#define SET_DIFF_TEMP		0x58
#define AUTO_TEMP			0x59

#define SALES_OK		0x25
#define RUN_ERR			0x30
#define RESET_OK		0x31


extern BYTE bServerNum ;
extern BYTE bClientNum ;
extern BYTE bCommLen ;
extern BYTE bVmdCmd ;
extern BYTE bVmdData ; 
extern BYTE bChannelReset ;
extern BYTE bVerNUM ;
extern BYTE bMeciType	;
extern BYTE bOtherCode ;

extern BYTE bVmdCheckEnd ;
extern BYTE bVmdResetEnd ;
extern WORD wRuncnt ;

extern u8 REV_BUF[USART_REC_LEN]; 
extern u8 TEMP_REV_BUF[USART_REC_LEN];

unsigned int crc_calc(unsigned char ddata[],unsigned char l);
void VMD_CommProcess(void);
void TEMP_CommProcess(void);
void Write_config_Data(void);
void Read_Config_Data(void);
void Output_Init(void);
#endif

