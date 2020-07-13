#ifndef __GPIO_H
#define	__GPIO_H

#include "stm32f10x.h"
#include "config.h"

#define Hor_4_Pin 					GPIO_Pin_5
#define Hor_4_GPIO_Port 			GPIOB
#define Hor_3_Pin 					GPIO_Pin_6
#define Hor_3_GPIO_Port 			GPIOB
#define Hor_1_Pin 					GPIO_Pin_8
#define Hor_1_GPIO_Port 			GPIOB
#define Hor_2_Pin 					GPIO_Pin_7
#define Hor_2_GPIO_Port 			GPIOB
#define Hor_10_Pin 					GPIO_Pin_4
#define Hor_10_GPIO_Port 			GPIOD
#define Hor_9_Pin 					GPIO_Pin_5
#define Hor_9_GPIO_Port 			GPIOD
#define Hor_8_Pin 					GPIO_Pin_6
#define Hor_8_GPIO_Port 			GPIOD
#define Hor_7_Pin 					GPIO_Pin_7
#define Hor_7_GPIO_Port 			GPIOD
#define Hor_6_Pin 					GPIO_Pin_3
#define Hor_6_GPIO_Port 			GPIOB
#define Hor_5_Pin 					GPIO_Pin_4
#define Hor_5_GPIO_Port 			GPIOB

#define sigReturn_8_Pin 			GPIO_Pin_13
#define sigReturn_8_GPIO_Port 		GPIOB
#define sigReturn_8_EXTI_IRQn 		EXTI0_IRQn

#define sigReturn_7_Pin 			GPIO_Pin_15
#define sigReturn_7_GPIO_Port 		GPIOB
#define sigReturn_7_EXTI_IRQn 		EXTI15_10_IRQn

#define sigReturn_6_Pin 			GPIO_Pin_9
#define sigReturn_6_GPIO_Port 		GPIOD
#define sigReturn_6_EXTI_IRQn 		EXTI9_5_IRQn

#define sigReturn_5_Pin 			GPIO_Pin_11
#define sigReturn_5_GPIO_Port 		GPIOD
#define sigReturn_5_EXTI_IRQn 		EXTI15_10_IRQn

#define sigReturn_4_Pin 			GPIO_Pin_13
#define sigReturn_4_GPIO_Port 		GPIOD
#define sigReturn_4_EXTI_IRQn 		EXTI15_10_IRQn

#define sigReturn_3_Pin 			GPIO_Pin_15
#define sigReturn_3_GPIO_Port 		GPIOD
#define sigReturn_3_EXTI_IRQn 		EXTI15_10_IRQn

#define sigReturn_2_Pin 			GPIO_Pin_7
#define sigReturn_2_GPIO_Port 		GPIOC
#define sigReturn_2_EXTI_IRQn 		EXTI9_5_IRQn

#define sigReturn_1_Pin 			GPIO_Pin_9
#define sigReturn_1_GPIO_Port 		GPIOC
#define sigReturn_1_EXTI_IRQn 		EXTI9_5_IRQn

#define gndCheck_8_Pin 				GPIO_Pin_12
#define gndCheck_8_GPIO_Port 		GPIOB
#define gndCheck_7_Pin 				GPIO_Pin_14
#define gndCheck_7_GPIO_Port 		GPIOB
#define gndCheck_6_Pin 				GPIO_Pin_8
#define gndCheck_6_GPIO_Port 		GPIOD
#define gndCheck_5_Pin 				GPIO_Pin_10
#define gndCheck_5_GPIO_Port 		GPIOD
#define gndCheck_4_Pin 				GPIO_Pin_12
#define gndCheck_4_GPIO_Port 		GPIOD
#define gndCheck_3_Pin 				GPIO_Pin_14
#define gndCheck_3_GPIO_Port 		GPIOD
#define gndCheck_2_Pin 				GPIO_Pin_6
#define gndCheck_2_GPIO_Port 		GPIOC
#define gndCheck_1_Pin 				GPIO_Pin_8
#define gndCheck_1_GPIO_Port 		GPIOC

#define ver_1_Pin 					GPIO_Pin_3
#define ver_1_GPIO_Port 			GPIOD
#define ver_2_Pin 					GPIO_Pin_2
#define ver_2_GPIO_Port 			GPIOD
#define ver_3_Pin 					GPIO_Pin_1
#define ver_3_GPIO_Port 			GPIOD
#define ver_4_Pin 					GPIO_Pin_0
#define ver_4_GPIO_Port 			GPIOD
#define ver_5_Pin 					GPIO_Pin_12
#define ver_5_GPIO_Port 			GPIOG
#define ver_6_Pin 					GPIO_Pin_11
#define ver_6_GPIO_Port 			GPIOG
#define ver_7_Pin 					GPIO_Pin_10
#define ver_7_GPIO_Port 			GPIOG
#define ver_8_Pin 					GPIO_Pin_15
#define ver_8_GPIO_Port 			GPIOA


#define compressor_GPIO_Port		GPIOB
#define compressor_Pin				GPIO_Pin_1
#define lightstrip_GPIO_Port		GPIOB
#define lightstrip_Pin				GPIO_Pin_0
#define doorlock_GPIO_Port	 		GPIOC
#define doorlock_Pin				GPIO_Pin_5
#define yuliu_1_GPIO_Port	 		GPIOE
#define yuliu_1_Pin					GPIO_Pin_8
#define yuliu_2_GPIO_Port	 		GPIOE
#define yuliu_2_Pin					GPIO_Pin_7

#define lightcheck_Pin 				GPIO_Pin_5
#define lightcheck_GPIO_Port 		GPIOA
#define reshidian_Pin 				GPIO_Pin_6
#define reshidian_GPIO_Port 		GPIOA
#define doorswitch_Pin				GPIO_Pin_2
#define doorswitch_GPIO_Port 		GPIOC


#define READ_SIGRETURN_1()	(sigReturn_1_GPIO_Port->IDR & sigReturn_1_Pin)	
#define READ_SIGRETURN_2()	(sigReturn_2_GPIO_Port->IDR & sigReturn_2_Pin)
#define READ_SIGRETURN_3()	(sigReturn_3_GPIO_Port->IDR & sigReturn_3_Pin)
#define READ_SIGRETURN_4()	(sigReturn_4_GPIO_Port->IDR & sigReturn_4_Pin)
#define READ_SIGRETURN_5()	(sigReturn_5_GPIO_Port->IDR & sigReturn_5_Pin)	
#define READ_SIGRETURN_6()	(sigReturn_6_GPIO_Port->IDR & sigReturn_6_Pin)	
#define READ_SIGRETURN_7()	(sigReturn_7_GPIO_Port->IDR & sigReturn_7_Pin)	
#define READ_SIGRETURN_8()	(sigReturn_8_GPIO_Port->IDR & sigReturn_8_Pin)

#define READ_GNDCHECK_1()	(gndCheck_1_GPIO_Port->IDR & gndCheck_1_Pin)
#define READ_GNDCHECK_2()	(gndCheck_2_GPIO_Port->IDR & gndCheck_2_Pin)
#define READ_GNDCHECK_3()	(gndCheck_3_GPIO_Port->IDR & gndCheck_3_Pin)
#define READ_GNDCHECK_4()	(gndCheck_4_GPIO_Port->IDR & gndCheck_4_Pin)
#define READ_GNDCHECK_5()	(gndCheck_5_GPIO_Port->IDR & gndCheck_5_Pin)
#define READ_GNDCHECK_6()	(gndCheck_6_GPIO_Port->IDR & gndCheck_6_Pin)
#define READ_GNDCHECK_7()	(gndCheck_7_GPIO_Port->IDR & gndCheck_7_Pin)
#define READ_GNDCHECK_8()	(gndCheck_8_GPIO_Port->IDR & gndCheck_8_Pin)


#define READ_LIGHTCHECK_7()		(lightcheck_GPIO_Port->IDR & lightcheck_Pin)
#define READ_RESHIDIANCHECK_8()	(reshidian_GPIO_Port->IDR & reshidian_Pin)
#define READ_DOORSWITCH_8()		(doorswitch_GPIO_Port->IDR & doorswitch_Pin)


void HorState_Set(IN WORD wHorNum);
void HorState_Reset(IN WORD wHorNum);
void VerState_Set(IN WORD wVerNum);
void VerState_Reset(IN WORD wVerNum);
BYTE SigReturn_Read(IN WORD wSigRetNum);
BYTE GndCheck_Read(IN WORD wGndCheckNum);	  
BYTE LightCheck_Read(void);
BYTE ReShiDian_Read(void);
BYTE DoorSwitch_Read(void);
void VMD_GPIO_Init(void);
void Compressor_Set(void);
void Compressor_Reset(void);
void Lightstrip_Set(void);
void Lightstrip_Reset(void);
void Doorlock_Set(void);
void Doorlock_Reset(void);
void Heatbb_Set(void);
void Heatbb_Reset(void);

#endif /* __GPIO_H */


