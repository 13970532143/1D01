/*************************************************************
**
**  Project Name :  SDL-B
**
**  Created By   :  PYF 
**
** 	Created Date :  2017/08/01
**
**************************************************************/
//dwin屏幕采用16bit调色板，但要求图片均为24位色bmp。
//
#ifndef HMI_DRIVER_H
#define HMI_DRIVER_H

#include "includes.h"
//---------------------------------------------------------
#define 	HMI_HEADER_H	0x5A
#define 	HMI_HEADER_L	0xA5

#define 	WRITE_REG_CMD 	0x80
#define 	READ_REG_CMD 	0x81
#define 	WRITE_VAR_CMD 	0x82
#define 	READ_VAR_CMD 	0x83
#define 	WRITE_CURVE_CMD 0x84


#define 	REG_VERSION 	0x00   	//屏版本号：BCD码，0x12表示V1.2
#define 	REG_BACKLIGHT 	0x01 	//背光调节，范围0x00~0x40
#define 	REG_BZ_TIME 	0x02  	//蜂鸣器鸣叫时间，单位10ms
#define 	REG_PIC_ID 		0x03	//2字节，当前页面ID，用于切换页面
#define 	REG_TP_FLAG 	0x05	//0x5A=触摸屏坐标更新，其他：坐标未更新
#define 	REG_TP_STATUS 	0x06	//0x01=第一次按下，0x03=长按，0x02=抬起
#define 	REG_RUN_TIME 	0x0C	//4字节，上电运行时间：BCD码，最大9999:59:59
#define 	REG_RTC_NOW 	0x20	//16字节，YY:MM:DD:WW:HH:MM:SS+农历YY:MM:DD+天干地支+生肖

//---------------------------------------------------------
typedef struct
{
	unsigned short PageID;
	unsigned short Start_X;
	unsigned short Start_Y;
	unsigned short End_X;
	unsigned short End_Y;
}HMI_PIC_COPY;

typedef struct 
{
  unsigned short pageID;
  unsigned short position_X;
  unsigned short position_Y;
  unsigned short width;
  unsigned short height;
}BasicGrapInfo;
extern BasicGrapInfo BasicGrap[67];
//---------------------------------------------------------
//
void HMI_AdjustScreen(void);
void HMI_ChangeScreen(unsigned short picID);
void HMI_BackLightCtrl(unsigned short val);
//
void HMI_ReadRegCmd(unsigned char addr,unsigned char length);
void HMI_WriteRegCmd(unsigned char addr,unsigned short *pdata,unsigned char length);
void HMI_BEEP_TIME(u8 var);         //蜂鸣器音亮输出
void HMI_BEEP_ENABLE(u8 sta);       //蜂鸣器使能指令
void HMI_WriteVarCmd(unsigned short addr,unsigned short *pdata,unsigned char length);
void HMI_TXIconVal(unsigned short addr,unsigned short val);
void HMI_TXIntToEdit(unsigned short addr,unsigned short val);
void HMI_TXStrToEdit(unsigned short addr, char *SourceStr, unsigned char Length);
void HMI_PictureCopy(unsigned short addr, HMI_PIC_COPY *para);
void HMI_PictureCopy_xy(unsigned short addr, unsigned short PageID,unsigned short Start_X,unsigned short Start_Y,unsigned short End_X,unsigned short End_Y);
void HMI_PictureCopy_S_T_xy(unsigned short addr, unsigned short PageID,unsigned short Start_X,unsigned short Start_Y,unsigned short End_X,unsigned short End_Y,unsigned short target_x,unsigned short target_y);
void HMI_ShowNumber(unsigned short addr, int xCounter,u8 bitnum, u8 len);
void HMI_ShowNumber_int(unsigned short addr, int xCounter,u8 bitnum, u8 len);
void HMI_PicCopyTwo(unsigned short addr, HMI_PIC_COPY *para, HMI_PIC_COPY *sour);
u8 HIM_HandShake(void); //握手
u8 Set_HIM_Date(u8 *date);  //设置时间
u8 Set_T5HIM_Time(u8 year,u8 mon,u8 date,u8 hours,u8 min,u8 sec);
//void HMI_ChangeSelectStatus(unsigned short controlID,unsigned char mode);
//void HMI_UpdateProgressBar(unsigned short controlID,unsigned short data);


#endif



