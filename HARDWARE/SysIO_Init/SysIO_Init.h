#ifndef  SYSINIT_H
#define  SYSINIT_H

#include "includes.h"

#define Valve1  PBout(5)         //���Ʒ�1
#define Valve2  PBout(4)         //���Ʒ�2
#define Valve3  PBout(3)         //���Ʒ�3
#define Valve4  PDout(2)         //���Ʒ�4
#define Valve5  PCout(12)        //���Ʒ�5
#define Valve6  PCout(11)        //���Ʒ�6
#define Valve7  PCout(10)        //���Ʒ�7
#define Valve8  PAout(15)        //���Ʒ�8

//#define VacCtr PAout(1)        //��������

#define OFF 1       //��
#define ON  0       //��


void SystemGPIO(void);

#endif 


