#ifndef __CONFIG_H
#define	__CONFIG_H

#include "stm32f10x.h"


#define VERSION		0X01

#define IN
#define OUT
#define INOUT

#define CHAR	char
#define UCHAR	unsigned char
#define BYTE	unsigned char

#define SHORT	short				// 2byte
#define USHORT	unsigned short		// 2byte
#define WORD	unsigned short		// 2byte
#define INT		int					// 4byte	
#define UINT	unsigned int		// 4byte
#define DWORD	unsigned int		// 4byte
//#define BOOL	unsigned char		// 1byte
#define LONG	long				// 4byte
#define ULONG	unsigned long		// 4byte


#define OK					0x00
#define TURE 				1
#define FALSE				0

#define SALE_MOTOR_OK  		0x20
#define RESET_CHAN_OK  		0x30
#define RESET_ALLCHAN_OK  	0x60
#define CHECK_CHAN_OK  		0xA0
#define CHECK_ALLCHAN_OK  	0x90							  

#define ERROR_BASE			0x00

#define ERROR_NOMOTOR  		0x40 // no motor
#define ERROR_TIMEOUT		0x50
#define ERROR_NOPALCE		0x30
#define ERROR_NOLIGHT		0x60
#define ERROR_OTHER			0xff
#define FREE_STATE			0xfe

#define RCC_GPIOA_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE); // enable the PA clock  
#define RCC_GPIOB_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); // enable the PB clock  
#define RCC_GPIOC_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC, ENABLE); // enable the PC clock  
#define RCC_GPIOD_CLK_ENBALE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOD, ENABLE); // enable the PD clock  
#define	RCC_GPIOE_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE); // enable the PE clock  
#define RCC_GPIOF_CLK_ENABLE()	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOF, ENABLE); // enable the PF clock  



enum eHorizontalNum
{
	HORNum_1,
	HORNum_2,
	HORNum_3,
	HORNum_4,
	HORNum_5,
	HORNum_6,
	HORNum_7,
	HORNum_8,
	HORNum_9,
	HORNum_10,

	MAXHORNum_NULL
};

enum eVerticalNum
{
	VERNum_1,
	VERNum_2,
	VERNum_3,
	VERNum_4,
	VERNum_5,
	VERNum_6,
	VERNum_7,
	VERNum_8,

	MAXVERNum_NULL
};

enum eSigReturnNum
{
 	SIGRETNUM_1,
	SIGRETNUM_2,
	SIGRETNUM_3,
	SIGRETNUM_4,
	SIGRETNUM_5,
	SIGRETNUM_6,
	SIGRETNUM_7,
	SIGRETNUM_8,

	MAXSIGRETNUM_NULL

};

enum eGndCheckNum
{
	GNDCHECKNUM_1,
	GNDCHECKNUM_2,
	GNDCHECKNUM_3,
	GNDCHECKNUM_4,
	GNDCHECKNUM_5,
	GNDCHECKNUM_6,
	GNDCHECKNUM_7,
	GNDCHECKNUM_8,

	MAXGNDCHECKNUM_NULL
};

extern BYTE LightCheckFlag;
extern BYTE HeatFlag;
extern BYTE CompreFlag;
extern BYTE TempAutoFlag;
extern BYTE ReShiDianFlag;
extern unsigned int TempValue;
extern BYTE LightStripFlag;
extern DWORD ReshidianCnt;
extern BYTE SaleAndLightFlag;
extern BYTE SaleAndLightCheckOverFlag;
extern BYTE DateSaveFlag;

#endif /* __CONFIG_H */



