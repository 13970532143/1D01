#ifndef __ADC_H
#define __ADC_H	
#include "includes.h" 
//////////////////////////////////////////////////////////////////////////////////	 

//ADC ��������	   


//��������:2020.6.13
//�汾��V1.0
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 
 							   
void Adc_Init(void); 				//ADCͨ����ʼ��
u16 Get_AdcValue(u8 Rank);
float Get_vac_value(void);          //��ȡ��ѹ��С
#endif 







