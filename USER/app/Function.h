/*
* 版权所有(C): 黄文基 深圳科医仁科技发展有限公司 2020.5
* 文档说明：模块功能函数
*
*/

#ifndef  Function_H
#define  Function_H

#include "includes.h"

//显示浓度
void dis_density(u8 mode, u8 nums);

void dis_countdown(u16 times);

void dis_vac_bar(u8 vac_value);     //真空瓶模式下显示压力条

void dis_vac_bar2(u8 vac_value);    //罩杯模式下显示压力条

void Deal_Language(u8 Language);

void dis_pro_data(u8 *data,u8 screen);

void Dis_CV_BAS(u16 addr,u8 sta,u16 PageID,u16 S_x,u16 E_y);
void Dis_SP_BAS(u16 addr,u8 sta,u16 S_x,u16 E_y);
void Clear(void);
void Clear1(void);
void Clear2(void);
void Clear3(void);
void Clear4(void);
void Clear5(void);



#endif


