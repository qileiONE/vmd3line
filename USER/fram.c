/****************************************Copyright (c)**************************************************
**                                Copyright  (C)  W.ch (2004--2010)
**                                Web:  http://www.winchiphead.com 
**                                                                                       
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��: fram.c																							
**��   ��   ��: fqb
**����޸�����: 2009��09��09��
**��        ��: 
**��        ����v1.0              
**�� �� ˵  ��: FM24C64����
**--------------------------------------------------------------------------------------------------------
*/
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include  "fram.h"

#define u8 unsigned char
#define u16 unsigned short

u8 ack;	         /*Ӧ���־λ*/
u8 iic_speed;   


void Fram_SDA_OUT( void )
{	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);	
}

void Fram_SDA_IN( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOE, &GPIO_InitStructure);	
}


void GPIO_INIT_Fram( void )
{
	GPIO_InitTypeDef GPIO_InitStructure;
	FRAM_CLK_SET( );
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);		
	FRAM_CLK_SET();
	FRAM_SDA_SET();		
	Fram_SDA_OUT();		
}

void mDelayuS1( u8 cnt )
{
	unsigned char	i;

	while( cnt -- )
	{
		i = 2;
		while( i -- )
			__nop( );
	}
}

/*******************************************************************
                     �����ߺ���               
����ԭ��: void  Start_I2c();  
����:       ����I2C����,������I2C��ʼ����.
  
********************************************************************/
void Start_I2c()
{
  	Fram_SDA_OUT( );	//��������Ϊ���
	mDelayuS1( 1 );
	FRAM_SDA_SET( );   /*������ʼ�����������źţ�SDA = 1*/
	mDelayuS1( 1 );
  	FRAM_CLK_SET( );	/*scl = 1*/
	mDelayuS1( 1 );
  	FRAM_SDA_CLR( );   /*������ʼ�ź�sda = 0 */
	mDelayuS1( 1 );
  	FRAM_CLK_CLR( );   /*ǯסI2C���ߣ�׼�����ͻ�������� scl = 0*/
	mDelayuS1( 1 );
//	Fram_SDA_IN();	  //����Ϊ����
}


/*******************************************************************
                      �������ߺ���               
����ԭ��: void  Stop_I2c();  
����:       ����I2C����,������I2C��������.
  
********************************************************************/
void Stop_I2c()
{
  	Fram_SDA_OUT( );	//��������Ϊ���
	mDelayuS1( 1 );
	FRAM_CLK_CLR( );	//scl = 0
	mDelayuS1( 1 );
	FRAM_SDA_CLR( );  /*���ͽ��������������ź�sda = 0*/
	mDelayuS1( 1 );
  	FRAM_CLK_SET( );  //scl = 1
	mDelayuS1( 1 );  	
  	FRAM_SDA_SET( );  /*����I2C���߽����ź� sda = 1*/
	mDelayuS1( 1 );  
//	Fram_SDA_IN();	  //����Ϊ����
}



/*******************************************************************
                 �ֽ����ݴ��ͺ���               
����ԭ��: void  SendByte(uchar c);
����:  ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������,�����ȴ�Ӧ��,����
     ��״̬λ���в���.(��Ӧ����Ӧ��ʹack=0 ��)     
     ��������������ack=1; ack=0��ʾ��������Ӧ����𻵡�
********************************************************************/
void  SendByte(u8 c)
{
	u8 BitCnt;
  	Fram_SDA_OUT( );	//��������Ϊ���
 	for(BitCnt=0;BitCnt<8;BitCnt++)  /*Ҫ���͵����ݳ���Ϊ8λ*/
    {
//		FRAM_CLK_CLR( );	//scl = 0
		if( c&0x80 ){FRAM_SDA_SET();} //sda = 1
     	else{  FRAM_SDA_CLR(); }      //sda = 0         
     	FRAM_CLK_CLR( );               /*scl = 1��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
		mDelayuS1( 1 );
     	FRAM_CLK_SET( ); 			   //scl = 0
		mDelayuS1( 1 );
     	FRAM_CLK_CLR( );               /*scl = 1��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ*/
		mDelayuS1( 1 );
		c <<= 1;
	}
//    FRAM_SDA_SET( );               /*sda = 1 8λ��������ͷ������ߣ�׼������Ӧ��λ*/
	Fram_SDA_IN( );	  	//��������Ϊ����
	mDelayuS1( 1 );
    FRAM_CLK_SET( );			   //scl  = 1
	mDelayuS1( 1 );
    if(FRAM_SDA( ))ack=0;  //���� 
    else ack=1;        /*�ж��Ƿ���յ�Ӧ���ź�*/
	mDelayuS1( 1 );
    FRAM_CLK_CLR( );			   //scl  = 0
}


/*******************************************************************
                 �ֽ����ݴ��ͺ���               
����ԭ��: uchar  RcvByte();
����:  �������մ���������������,���ж����ߴ���(����Ӧ���ź�)��
     ���������Ӧ������  
********************************************************************/	
u8  RcvByte( )
{
 	u8 retc;
  	u8 BitCnt;
  	Fram_SDA_OUT( );	//��������Ϊ���
  
  	retc=0; 
  	FRAM_SDA_SET( );             /*sda = 1��������Ϊ���뷽ʽ*/
	Fram_SDA_IN( );	  	//��������Ϊ����
  	for(BitCnt=8;BitCnt!=0;BitCnt--)
    {
		mDelayuS1( 1 );
        FRAM_CLK_CLR( );       /*scl = 0��ʱ����Ϊ�ͣ�׼����������λ*/
		mDelayuS1( 1 );
        FRAM_CLK_SET( );       /*scl = 1��ʱ����Ϊ��ʹ��������������Ч*/
		mDelayuS1( 1 );
        retc=retc<<1;
        if(FRAM_SDA( ))retc++; /*������λ,���յ�����λ����retc�� */
    }
  	FRAM_CLK_CLR(); 		//scl = 0   
	mDelayuS1( 1 );
	Fram_SDA_IN();		//����Ϊ����
  	return(retc);
}


/********************************************************************
                     Ӧ���Ӻ���
ԭ��:  void Ack_I2c(bit a);
 
����:����������Ӧ���ź�,(������Ӧ����Ӧ���ź�)
********************************************************************/
void Ack_I2c(unsigned char a)
{
  	Fram_SDA_OUT( );	//��������Ϊ���
	if( a ) {FRAM_SDA_SET();}
	else {FRAM_SDA_CLR(); } 
	mDelayuS1( 1 );
  	FRAM_CLK_SET( );
	mDelayuS1( 1 );
 	FRAM_CLK_CLR( );                /*��ʱ���ߣ�ǯסI2C�����Ա��������*/
	mDelayuS1( 1 );
//	Fram_SDA_IN( );		//����Ϊ����
}


/*******************************************************************
                    �����ӵ�ַ�������Ͷ��ֽ����ݺ���               
����ԭ��: bit  ISendStr(uchar sla,uchar suba,ucahr *s,uchar no);  
����:     ���������ߵ����͵�ַ���ӵ�ַ,���ݣ��������ߵ�ȫ����,������
          ��ַsla���ӵ�ַsuba������������sָ������ݣ�����no���ֽڡ�
           �������1��ʾ�����ɹ��������������
ע�⣺    ʹ��ǰ�����ѽ������ߡ�
********************************************************************/
u8 write_str_sub(u8 sla,u16 suba,u8 *s,u16 no)
{
    u16 i;
	Start_I2c();               /*��������*/
	SendByte(sla);            /*����������ַ*/
	if( ack == 0 )return 0;
	SendByte(suba>>8);
	if(ack==0)return(0);	
	SendByte(suba);            /*���������ӵ�ַ*/
   	if(ack==0)return(0);
    for(i=0;i<no;i++)
  	{	   
       SendByte(*s);               /*��������*/
       if(ack==0)return(0);
       s++;
    } 
 	Stop_I2c();                 /*��������*/ 
  	return(1);
}



/*******************************************************************
                    �����ӵ�ַ������ȡ���ֽ����ݺ���               
����ԭ��: bit  ISendStr(uchar sla,uchar suba,ucahr *s,uchar no);  
����:     ���������ߵ����͵�ַ���ӵ�ַ,�����ݣ��������ߵ�ȫ����,������
          ��ַsla���ӵ�ַsuba�����������ݷ���sָ��Ĵ洢������no���ֽڡ�
           �������1��ʾ�����ɹ��������������
ע�⣺    ʹ��ǰ�����ѽ������ߡ�
********************************************************************/
u8 read_str_sub(u8 sla,u16 suba,u8 *s,u16 no)
{
   	u16 i;
	Start_I2c();               /*��������*/
   	SendByte(sla);			//����������ַ�� 1
    if(ack==0)return(0);

	SendByte(suba>>8);
	SendByte(suba);            /*���������ӵ�ַ*/
    if(ack==0)return(0);

   	Start_I2c();
   	SendByte(sla+1);			//����������ַ�� 1
    if(ack==0)return(0);
   	for(i=0;i<no-1;i++)
    {   
     	*s=RcvByte();               /*��������*/
      	Ack_I2c(0);                /*���;ʹ�λ*/  
     	s++;
    } 
   	*s=RcvByte();
    Ack_I2c(1);                 /*���ͷ�Ӧλ*/
 	Stop_I2c();                    /*��������*/ 
  	return(1);
}

u8 Fram_Read_Data( u16 suba,u8 *s,u16 no )
{
	return read_str_sub(FRAM_ADDR_CMD,suba,s,no);
}

u8 Fram_Write_Data( u16 suba,u8 *s,u16 no )
{
	return write_str_sub(FRAM_ADDR_CMD,suba,s,no);
}

/*
	д��־λ���ݣ���ַΪ8192-512=7680=0x1e00
	addr����ʾ��7.5K�ĵ�ַ�ռ��λ��
	len�� ��ʾ��7.5K����Ч���ݳ���
*/
void write_bit( u16 addr,u16 len )
{
	u8 buf[8];
	buf[0] = addr>>8;buf[1] = addr;
	buf[2] = len>>8;buf[3] = len;
	Fram_Write_Data( 0x1e00,buf,4 );
}

/*
	����־λ���ݣ���ַΪ8192-512=7680=0x1e00
	addr����ʾ��7.5K�ĵ�ַ�ռ��λ��
	len�� ��ʾ��7.5K����Ч���ݳ���
*/
u16 read_bit( u16 addr )
{
   u8 buf[8];
   u16 len;
	Fram_Read_Data( 0x1e00,buf,4 );
	addr = (u16)buf[0]<<8;
	addr |= buf[1];
	len = (u16)buf[2]<<8;
	len |= buf[3];

printf("len=%02x\n",len);
printf("addr=%02x\n",addr);
	return len;

}


/*
	д������FRAM����
	�������ݣ����������ݵ�ַ
*/
#define  FRAM_SIZE	0x1e00	
u16 write_data( u16 addr,u16 len,u8 *pbuf )
{
	u16 back_addr,i;
//	u8 test_buf[100];
	if( addr+len < FRAM_SIZE ){
		Fram_Write_Data( addr,pbuf,len);
		addr+=len;
	}
	else if( addr+len == FRAM_SIZE ){
		Fram_Write_Data( addr,pbuf,len );
		addr = 0;	
	}
	else if( addr+len > FRAM_SIZE ){
		back_addr = addr+len-FRAM_SIZE;
		i = FRAM_SIZE-addr;
		Fram_Write_Data( addr,pbuf,i );
		addr = 0;pbuf+=i;
		Fram_Write_Data( addr,pbuf,back_addr );
//		Fram_Read_Data( addr,test_buf,i );
//		Fram_Read_Data( 0,&test_buf[i],back_addr );
//for( i=0;i!=100;i++ )printf("%02x ",test_buf[i]);

		addr = back_addr;
		

	}
	return addr;	
}


/*
	��ȡ������RAM����
*/
void read_data( u16 addr,u16 len,u8 *pbuf )
{
	u16 back_addr,i;
	if( addr+len <= FRAM_SIZE ){
		Fram_Read_Data( addr,pbuf,len );	
	}
	else if( addr+len > FRAM_SIZE ){
		back_addr = addr+len-FRAM_SIZE;
		i = FRAM_SIZE-addr;
		Fram_Read_Data( addr,pbuf,i );
		addr = 0;pbuf+=i;
		Fram_Read_Data( addr,pbuf,back_addr );	
	}
}

