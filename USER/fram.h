#ifndef __FRAM_H
#define	__FRAM_H

#include "stm32f10x.h"


#define FRAM_ADDR_CMD		0xa0	/*����*/

#define		FRAM_CLK_SET()	{ GPIOE->BSRR  = GPIO_Pin_5; }	  	//FRAM CLK = 1
#define		FRAM_CLK_CLR()	{ GPIOE->BRR  = GPIO_Pin_5; }		//FRAM CLK = 0

#define		FRAM_SDA_SET()	{ GPIOE->BSRR  = GPIO_Pin_6; }	  	//FRAM SDA = 1
#define		FRAM_SDA_CLR()	{ GPIOE->BRR  = GPIO_Pin_6; }		//FRAM SDA = 0


#define		FRAM_SDA( )	  (GPIOE->IDR & 0x40	)			//PE6


extern u8 write_str_sub(u8 sla,u16 suba,u8 *s,u16 no);		//д����
extern u8 read_str_sub(u8 sla,u16 suba,u8 *s,u16 no);		//������

extern u8 Fram_Write_Data( u16 suba,u8 *s,u16 no );
extern u8 Fram_Read_Data( u16 suba,u8 *s,u16 no );

extern void write_file_sys_bit( void );
extern void GPIO_INIT_Fram( void );


extern u16 write_data( u16 addr,u16 len,u8 *pbuf );
extern void write_bit( u16 addr,u16 len );
extern u16 read_bit( u16 addr );
extern void read_data( u16 addr,u16 len,u8 *pbuf );


void Delayms( int n );



#endif
