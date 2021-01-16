/*************************************************************
**
**  Project Name :  CO2
**
**  Created By   :  PYF 
**
** 	Created Date :  2016/04/23
**
***************************************************************/
//
#ifndef  AT24C64_DRIVER_H
#define  AT24C64_DRIVER_H
#include "includes.h"
//
//PB6---SCL   PB7---SDA
#define 	IIC_SCL_H		GPIO_SetBits(GPIOB, GPIO_Pin_6)
#define 	IIC_SCL_L		GPIO_ResetBits(GPIOB, GPIO_Pin_6)
#define 	IIC_SDA_H		GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define 	IIC_SDA_L		GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define 	IIC_SDA_STATE 	GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)  // IIC_SDA-- ˝æ› ‰»ÎºÏ≤‚

#define 	IIC_NOP()		IIC_Delay()


typedef enum teACK
{
	IIC_NACK = 0,
	IIC_ACK,
}IIC_REPLY;

typedef enum teIICBUSSTATE
{
	IIC_READY = 0,
	IIC_BUSY,
	IIC_EEROR,
}IIC_BUSSTATE;

void IIC_Init(void);
INT8U EEPROM_WriteSeq(INT16U addr,INT8U *dat,INT16U len);
INT8U EEPROM_ReadSeq(INT16U addr,INT8U *ptr,INT16U len);

void EEP_ReadDefault(void);
void EEP_WriteDefault(void);
void EEP_WriteDefaultCalib(void);

void DSPCalibrate1064Param(void);
void DSPCalibrate532Param(void);
void my_sprintf(char *str, unsigned char bitnum, float value);

#endif

//------------------------------------------------------------
//------------------------------------------------------------
//-----------------------(File End)---------------------------
//------------------------------------------------------------
//------------------------------------------------------------

