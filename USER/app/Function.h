/*
* ��Ȩ����(C): ���Ļ� ���ڿ�ҽ�ʿƼ���չ���޹�˾ 2020.5
* �ĵ�˵����ģ�鹦�ܺ���
*
*/

#ifndef  Function_H
#define  Function_H

#include "includes.h"

//��ʾŨ��
void dis_density(u8 mode, u8 nums);

void dis_countdown(u16 times);

void dis_vac_bar(u8 vac_value);     //���ƿģʽ����ʾѹ����

void dis_vac_bar2(u8 vac_value);    //�ֱ�ģʽ����ʾѹ����

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

