#ifndef __LED_H
#define	__LED_H

#include "stm32f10x.h"
#include "config.h"


#define LED_Pin 					GPIO_Pin_4
#define LED_GPIO_Port 				GPIOA

/* the macro definition to trigger the led on or off 
 * 1 - off
 - 0 - on
 */
#define ON  1
#define OFF 0

#define LED(a)	if (a)	\
					GPIO_SetBits(LED_GPIO_Port,LED_Pin);\
					else		\
					GPIO_ResetBits(LED_GPIO_Port,LED_Pin)

void LED_GPIO_Config(void);

#endif /* __LED_H */
