/*************************************************************
**
**  Project Name :  CO2
**
**  Created By   :  PYF 
**
** 	Created Date :  2016/04/15
**
***************************************************************/
//
#ifndef  BASIC_LIB__H
#define  BASIC_LIB__H

#include "includes.h"
#define fabs(n) n>0?n:-n

#define Add  1
#define Dec  0


void StrCat(char *s,char *t);
void CheckOutputVal(unsigned char adj,unsigned char dir, void* valuedata, unsigned short limithigh,unsigned short limitlow);
unsigned short XuanZe_Average(unsigned short *arr, unsigned char n);
void Linearfit(float *a,float *b,float *dat,unsigned char num);
void MemoryCopy(void *target, void *source, const unsigned int len);
void IntToStr_Decimal(int sourceVal, char *str, unsigned char bitnum);
void IntToStr(int sourceVal, char *str); 
void myIntToStr(int num,char *str,int bit);   //bit为需要显示的位数
void my_sprintf(char *str, unsigned char bitnum, float value);
long map(long x, long in_min, long in_max, long out_min, long out_max);
int  compare_array(char * array1,char *array2,int len);
void Str_memset(char *array,char value,u8 len);

#endif

//------------------------------------------------------------
//------------------------------------------------------------
//-----------------------(File End)---------------------------
//------------------------------------------------------------
//------------------------------------------------------------

