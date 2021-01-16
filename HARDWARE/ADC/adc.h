#ifndef __ADC_H
#define __ADC_H	
#include "includes.h" 
//////////////////////////////////////////////////////////////////////////////////	 

//ADC 驱动代码	   


//创建日期:2020.6.13
//版本：V1.0
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
 							   
void Adc_Init(void); 				//ADC通道初始化
u16 Get_AdcValue(u8 Rank);
float Get_vac_value(void);          //获取负压大小
#endif 







