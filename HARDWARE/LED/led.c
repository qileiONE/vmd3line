//////////////////////////////////////////////////////////////////////////////////	           
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//SIMϵ�п�����		   
//ȫ��ӥ����@UNV
//�޸�����:2016/8/18
//�汾��V1.0
//�ٷ��Ա����ַ��https://shop110330041.taobao.com
//��Ȩ���У�����ؾ���
//All rights reserved
///////////////////////////////////////////////////////////////////
#include "led.h"

/***************  ����LED�õ���I/O�� *******************/
void LED_GPIO_Config(void)	
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE, ENABLE); // ʹ��PA�˿�ʱ��  
  GPIO_InitStructure.GPIO_Pin = LED_Pin;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(LED_GPIO_Port, &GPIO_InitStructure);  //��ʼ��PC�˿�
  GPIO_SetBits(LED_GPIO_Port, LED_Pin);	 // �ر�����LED
}



