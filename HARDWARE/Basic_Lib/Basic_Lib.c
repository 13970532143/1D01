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
#include "includes.h"

//-------------------------------------------------------------------------
//数组初始化
void mymemset(u16 *array,u16 value,u8 len)
{
	u8 i;
	for(i = 0;i < len;i++)
	{
		array[i] = value;
	}
}

void Str_memset(char *array,char value,u8 len)
{
	u8 i;
	for(i = 0;i < len;i++)
	{
		array[i] = value;
	}
}

int Power(int a,int n)
{
    if(n==0)
    {
        return 1;
    }
    else if(n>0)
    {
        return a * Power(a,n-1);
    }
    else if(n<0)
    {
        return 1/a * Power(a,n-1);
    }
    return 1;    
}


//--------------------------------------------------------------------------
char * myIntStr(int value,int bit) 
{  
    u16 val = value; 
    char *str1 = "X:";
    u8 i = 0;
    for(i = 0;i < bit;i++)
    {
        *str1++ = val/Power(10,bit-i) + '0';
        val %= 10;
    }
	*str1++ = '\0';
    return str1;
}
//--------------------------------------------------------------------------
//数组比较，一样则返回1，不一样则返回0
int  compare_array(char * array1,char *array2,int len) 
{
    u8 i ;
    for(i = 0; i < len;i++)
    {
        if(array1[i] != array2[i]) 
            return 0;
    }
    return 1;
}

//字符串连接函数
void StrCat(char *s,char *t)
{
	while(*s!='\0')
	{
		s++;
	}
	while(*t!='\0')
	{
		*s++=*t++;
	}
}

//-------------------------------------------------------------------------
//加减限制函数
void CheckOutputVal(unsigned char adj,unsigned char dir, void* valuedata, unsigned short limithigh,unsigned short limitlow)
{
	unsigned short *val = (unsigned short *)valuedata;
	
	if(dir == Add) 
	{
		if(*val + adj < limithigh)
		{
			*val += adj;
		} 
		else
		{
			*val = limithigh;
		}
	}
	else if(dir == Dec)
	{
		if(*val - adj > limitlow)
		{
			*val -= adj;
		}
		else
		{
			*val = limitlow;
		}
	}
}

//-------------------------------------------------------------------------
//选择排序 取平均值---从小到大
unsigned short XuanZe_Average(unsigned short *arr, unsigned char n)
{
    unsigned char i=0,j=0,k=0, m=0;
    unsigned short temp=0, sum=0;
    for(i=0; i<n; i++)
    {
        k = i;
        for(j=i+1; j<n; j++)
        {
            if(arr[k] > arr[j])
            k = j;
        }
        if(k != i)
        {
            temp = arr[k];
            arr[k] = arr[i];
            arr[i] = temp;
        }
    }
    
    //5个数取中间3个求平均值
    for(m=1; m<4; m++)
    {
         sum += arr[m];
    }
    return (sum/3);
}

//-------------------------------------------------------------------------
//最小二乘法 取直线
void Linearfit(float *a,float *b,float *dat,unsigned char num)
{
	unsigned char i;
	float ave_xy=0,ave_x=0,ave_y=0,ave_x2=0;
	for(i=0;i<num;i+=2)
	{
		ave_xy+=dat[i]*dat[i+1];
		ave_x+=dat[i];
		ave_y+=dat[i+1];
		ave_x2+=dat[i]*dat[i];
	}
	ave_x/=num/2;
	ave_xy/=num/2;
	ave_y/=num/2;
	ave_x2/=num/2;
	*a=(ave_xy-ave_x*ave_y)/(ave_x2-ave_x*ave_x);
	*b=ave_y-(*a)*ave_x;
}

//-------------------------------------------------------------------------
//复制函数
void MemoryCopy(void *target, void *source, const unsigned int len)
{
	unsigned char *t = (unsigned char *)target;
	unsigned char *s = (unsigned char *)source;
	unsigned int n = 0;
	for(n=0; n<len; n++)
	{
	    *t++ = *s++;
	}
}

//-------------------------------------------------------------------------
//整数--->字符串小数
void IntToStr_Decimal(int sourceVal, char *str, unsigned char bitnum)
{
	int tmp = 1;
	int val = fabs(sourceVal); 
	if(sourceVal < 0)
	{
		*str++ = '-';
	}
	//---------------------------------------
	if(bitnum == 1)
	{
		if(val/10==0)  //个位数
		{
			*str++ = '0';
		}
	}
	else if(bitnum == 2)
	{
		if(val/100==0)
		{
			*str++ = '0';
				
			if(val/10==0)
			{
				*str++ = '.';
				*str++ = '0';
			}
		}
	}
	else if(bitnum == 3)
	{
		if(val/1000==0)
		{
			*str++ = '0';
				
			if(val/100==0)
			{
				*str++ = '.';
				*str++ = '0';
				
				if(val/10==0)
				{
					*str++ = '0';
				}
			}
		}
	}
	//-------------------------------------------    
	while(val >= 10)		//
	{
		tmp *= 10;
		val /= 10;
	}
	val = fabs(sourceVal);
	while(tmp>0)
	{
	    if(tmp==1 && bitnum==1)
		    *str++ = '.';			//一位小数
	    else if(tmp==10 && bitnum==2)   
	        *str++ = '.';			//二位小数
	    else if(tmp==100 && bitnum==3)   
	        *str++ = '.';			//三位小数
	        
		*str++ = val/tmp + '0';	
		val %= tmp;
		tmp /= 10;
	}
	*str = '\0';
}

//-------------------------------------------------------------------------
//整型数转字符串
void IntToStr(int sourceVal, char *str)
{
    int tmp = 1;
	int val =fabs(sourceVal);
	if(sourceVal < 0)    //判断正负
	{
		*str++ = '-';
	}
	while(val >= 10)		//确定value是几位数
	{
		tmp *= 10;
		val /= 10;
	}
	val = fabs(sourceVal);    //###
    if(tmp>0)
    {
        while(tmp>0)
        {
            *str++ = val/tmp + '0';
            val %= tmp;
            tmp /= 10;
        }
    }
	*str = '\0';
}

void myIntToStr(int num,char *str,int bit)
{
    int i=0;
    for(;i<bit;i++)
    {
        str[i] = '0';
    }
    i=1;
    while(num)
    {
        str[bit-i]=num%10+'0';//加字符0 自动从数值转换成字符型
        i++;
        num/=10;
    }
    str[bit]='\0';//末尾加0以表示字符结束
}


//-------------------------------------------------------------------------
//是KEIL ARM的ARM-CC编译器不支持sprintf函数的float显示
//解决办法：把float分成两个unsigned int 数，再显示
void my_sprintf(char *str, unsigned char bitnum, float value)
{
	float val = value;
	char *buffer = str;
	int Intergar = 0;
	int Decimal = 0;
	int BitVal = 0; 
	
	BitVal = (int)Power(10, bitnum);
	
	Intergar = (int)val;
	Decimal = (int)( val*BitVal - Intergar*BitVal );
	Decimal = abs(Decimal);		//绝对值
	
	if(Intergar==0 && val<0)	//打印 -0.123
	{
		if(bitnum == 1)
			sprintf(buffer,"-0.%01d", Decimal); 
		else if(bitnum == 2)
			sprintf(buffer,"-0.%02d", Decimal);
		else if(bitnum == 3)
			sprintf(buffer,"-0.%03d", Decimal);
		else if(bitnum == 4)
			sprintf(buffer,"-0.%04d", Decimal);	
	}
	else
	{  
		if(bitnum == 1)
			sprintf(buffer,"%d.%01d", Intergar, Decimal); 
		else if(bitnum == 2)
			sprintf(buffer,"%d.%02d", Intergar, Decimal);
		else if(bitnum == 3)
			sprintf(buffer,"%d.%03d", Intergar, Decimal);
		else if(bitnum == 4)
			sprintf(buffer,"%d.%04d", Intergar, Decimal);
	}
}
//map映射函数
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
} 



//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//-----------------------(File End)---------------------------
//------------------------------------------------------------
//------------------------------------------------------------

