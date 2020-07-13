#ifndef __VMDDIR_H
#define	__VMDDIR_H

#include "stm32f10x.h"
#include "config.h"
#include "gpio.h"
#include "delay.h"
#include "vmddir.h"
#include "comm.h"
#include "usart.h"

#define HORNUM_MAX  10
#define VERNUM_MAX	8

#define SIGRETRESET		1
#define GNDCHECKMOTOR 	0
#define GNDCHECKRUN		1

#define START_TIME_MAX		1000  //2S
#define RUN_TIME_MAX		10000 //10S

extern DWORD dwVmdTimeStartCnt ;
extern DWORD dwVmdTimeRunCnt ;
extern DWORD dwSaleAndlightCnt;
extern BYTE bVmdTimeStartCntFlag ;
extern BYTE bVmdTimeRunCntFlag ;
extern BYTE bVmdTimeStartFlag ;
extern BYTE bVmdTimeRunFlag ;

extern BYTE bVmdRunningFlag ;
extern BYTE bRunEndFlag ;
extern BYTE bVmdBusyFlag ;
extern BYTE bLightCheck;

extern WORD wSaleChannelTemp ;


void HorCom_ON(IN WORD wHorNum);
void  HorCom_OFF(IN WORD wHorNum);
void VerGnd_ON(IN WORD wHorNum);
void  VerGnd_OFF(IN WORD wHorNum);

void VMD_MotorReset(void);
void VMD_SalesControl(IN WORD wSaleChannel);
void VMD_ResetControl(IN WORD wSaleChannel);
void VMD_ErrCheck(void);
void VMD_LightCheck(void);

void VMD_AllCheck(IN WORD wSaleChannel);
void VMD_AllReset(IN WORD wSaleChannel);

void VMD_SelesControlStart(IN WORD wSaleChannel);
void VMD_ResetControlStart(IN WORD wSaleChannel);


#endif /* __VMDDIR_H */


