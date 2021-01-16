#ifndef  SYSINIT_H
#define  SYSINIT_H

#include "includes.h"

#define Valve1  PBout(5)         //控制阀1
#define Valve2  PBout(4)         //控制阀2
#define Valve3  PBout(3)         //控制阀3
#define Valve4  PDout(2)         //控制阀4
#define Valve5  PCout(12)        //控制阀5
#define Valve6  PCout(11)        //控制阀6
#define Valve7  PCout(10)        //控制阀7
#define Valve8  PAout(15)        //控制阀8

//#define VacCtr PAout(1)        //控制气泵

#define OFF 1       //关
#define ON  0       //开


void SystemGPIO(void);

#endif 


