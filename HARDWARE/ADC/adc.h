#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

#define TempNegBase   1000

void ADC1_Init(void);
unsigned int Get_temp1(void);
unsigned int Get_temp2(void);

#endif /* __ADC_H */


