/*************************************************************
**
**  Project Name :  CO2
**
**  Created By   :  PYF 
**
** 	Created Date :  2016/04/04  
**
**************************************************************/
//
#ifndef USART3_DRIVER_H
#define	USART3_DRIVER_H

#include "includes.h"

#define ERR_CMD 0xFFFF

extern u16 BT_CMD;
extern u16 BT_KEY ;    //变量键值
extern u8 him_rx_buf[50];
extern u8 Lenght; 

void USART3_Init(unsigned int baund);
void USART3_SendData(unsigned char *ptr, unsigned char num);
void USART3_Sendbyte(u8 byte);
void GetButtonData(unsigned short *btValue);		//中断接收函数
void GETButtonKEY(unsigned short *btKey);
u8 Get_HIM_Date(void );
//
#endif // __BSP_H
//------------------------------------------------------------
//------------------------------------------------------------
//-----------------------(File End)---------------------------
//------------------------------------------------------------
//------------------------------------------------------------
