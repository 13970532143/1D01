/*************************************************************
**
**  Project Name :  CO2
**
**  Created By   :  PYF 
**
** 	Created Date :  2016/04/14
**
***************************************************************/
//
#ifndef  USART2_DRIVER
#define  USART2_DRIVER
#include "includes.h"
/*******************************************
�����Ƴ������
"$FE" (Force Energy)
"$SE" (Send Energy) returns the energy 

$FP ǿ���е����ʲ��Խ���
$SP��ȡ����  ( 0x0d '\n' �س���)

IPL ������ͷ
$WN0 ----- 600J
$WN1 ----- 60.0J
$WN2 ----- 6.00J

YAG ������ͷ
$WN0 ----- 10.0J
$WN1 ----- 2.00J
$WN2 ----- 200mJ
$WN3 ----- 20.0mJ
$WN4 ----- 2.00mJ

********************************************/

void USART2_Init(unsigned int baund);
void USART2_SendData(unsigned char *ptr, unsigned char num);
//
void MP3_Play_Once(u8 data);
void MP3_Send_Sound(u8 data);
void MP3_Send_Song(INT8U data);
void MP3_Play_Stop(void);
//
void CalibLaserRun(void);
void CalibrationStart(void);
void SemCalib_Init(void);
void ToggleReadEnergy(void);

//
void SV17F_MP3_Query(void);
void SV17F_MP3_Specify(u16 music);
void SV17F_MP3_Finsh(void);
void SV17F_Set_Vol(u8 vol);

#endif

