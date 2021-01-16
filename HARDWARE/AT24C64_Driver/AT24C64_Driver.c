/*************************************************************
**
**  Project Name :  CO2
**
**  Created By   :  PYF 
**
** 	Created Data :  2016/04/23
**
***************************************************************/
/**************************************************************
注意：
	24C64的读写时序与24C16存在区别：
	区别在于24C16发送的地址是一个8位的，然后24C64需要的地址是一个16位的；
	所以，如果外部控制程序不变的话，两个芯片是不可以互换的。
***************************************************************/
// AT24C64 

#include "includes.h"

//extern SYSParam  GB_SYSParam;

void SoftDelay(INT16U delay)
{
	while(delay--);
}

void IIC_Init(void)
{
	//PB6---SCL   PB7---SDA
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = (GPIO_Pin_7 | GPIO_Pin_6);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;    	//开漏输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
    
	IIC_SCL_H;
	IIC_SDA_H;
}

void IIC_Delay(void)
{
	unsigned short delay = 0x80;
	while(delay--);
}

unsigned char IIC_Start(void)
{
	IIC_SDA_H;
	IIC_SCL_H;
	IIC_NOP();
	if(!IIC_SDA_STATE)
	{
		return IIC_BUSY;
	}
	IIC_SDA_L;
	IIC_NOP();
	IIC_SCL_L;
	IIC_NOP();
	if(IIC_SDA_STATE)
	{
		IIC_SDA_H;
		IIC_SCL_H;
		return IIC_EEROR;
	}
	return IIC_READY;
}

void IIC_Stop(void)
{
	IIC_SDA_L;
	IIC_SCL_H;
	IIC_NOP();
	IIC_SDA_H;
	IIC_NOP();
}

void IIC_Send_ACK(void)
{
	IIC_SDA_L;
	IIC_SCL_H;
	IIC_NOP();
	IIC_SCL_L;
	IIC_NOP();
	IIC_SDA_H;
}

void IIC_Send_NACK(void)
{ 
	IIC_SDA_H;
	IIC_SCL_H;
	IIC_NOP();
	IIC_SCL_L;
	IIC_NOP();
}

unsigned char IIC_SendByte(unsigned char ch)
{ 
	unsigned char n=8;
	IIC_SCL_L;
	while(n--)
	{ 
		if(ch & 0x80)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		IIC_SCL_H;
		IIC_NOP();
		IIC_SCL_L;
		ch = ch<<1;
		IIC_NOP();
	}
	IIC_SDA_H;
	IIC_SCL_H;
	IIC_NOP();
	if(IIC_SDA_STATE)
	{
		IIC_SCL_L;
		return IIC_NACK;
	}
	else
	{
		IIC_SCL_L;
		return IIC_ACK;
	}
}

unsigned char IIC_ReceiveByte(void)
{
	unsigned char i,ch;
	IIC_SDA_H;
	IIC_SCL_L;
	ch = 0;
	for(i = 0; i < 8; i++)
	{
		IIC_SCL_H;
		IIC_NOP();
		ch <<= 1;
		if(IIC_SDA_STATE)
			ch |= 0x01;
		IIC_SCL_L;
		IIC_NOP();
	}
	return ch;
}

//-------------------------------------------------------------
//-------------------------------------------------------------
//-------------------------------------------------------------
//写入数据串
INT8U EEPROM_WriteSeq(INT16U addr,INT8U *dat,INT16U len)
{
	INT16U slaveaddr;
	INT8U status,offset,num,i;
	INT8U buf[16];
	offset=addr&0x0f;	/* 计算页偏移 */
	num=16-offset;		/* 页中剩余字节数*/
	addr&=0x07f0;
	
	while(len)
	{
		EEPROM_ReadSeq(addr, buf, 16);		/* 读取整页数据 */
		if(num<len)	/* 剩余字节数不够时 */
		{
			for(;offset<16;offset++)
				buf[offset]=*dat++;
			len-=num;
			offset=0;
			num=16;
		}
		else
		{
			while(len--)
			{
				buf[offset++]=*dat++;
			}
			len=0;
		}
		
		while(1)
		{
			status = IIC_Start();
			if(status==IIC_READY)
				break;
			else if(status == IIC_EEROR)
			{
				IIC_Stop();
				return 1;
			}
		}
		status = IIC_SendByte(0xA0);
		if(status==IIC_NACK)
		{
			IIC_Stop();
			return 2;
		}
		slaveaddr = addr;
		IIC_SendByte((unsigned char)(slaveaddr>>8));
		IIC_SendByte((unsigned char)(slaveaddr&0xFF));
		
		for(i=0;i<16;i++)
		{
			status = IIC_SendByte(buf[i]);
			if(status==IIC_NACK)
			{
				IIC_Stop();
				return 4;
			}
		}
		IIC_Stop();
		SoftDelay(50000);
		SoftDelay(50000);
		addr+=16;
	}
	return 0;
}

//读出数据串
INT8U EEPROM_ReadSeq(INT16U addr,INT8U *ptr,INT16U len)
{
	INT16U slaveaddr;
	INT8U status;

	while(1)
	{
		status = IIC_Start();
		if(status==IIC_READY)
			break;
		else if(status == IIC_EEROR)
			return 1;
	}
	status = IIC_SendByte(0xA0);
	if(status==IIC_NACK)
		return 2;
	slaveaddr = addr;
	IIC_SendByte((unsigned char)(slaveaddr>>8));
	IIC_SendByte((unsigned char)(slaveaddr&0xFF));
	
	//---------------------------
	while(1)
	{
		status = IIC_Start();
		if(status==IIC_READY)
			break;
		else if(status == IIC_EEROR)
			return 4;
	}
	status = IIC_SendByte(0xA1);
	if(status==IIC_NACK)
		return 5;
	while(len--)
	{
		*ptr++ = IIC_ReceiveByte();
		if(len)
			IIC_Send_ACK();
		else
			IIC_Send_NACK();
	}
	IIC_Stop();
	SoftDelay(200);
	return 0;
}
//------------------------------------------------------------
//------------------------------------------------------------
//extern char MasterNumber[16];
//extern CaliPARAM EV_1064Parm[4]; 
//extern CaliPARAM EV_532Parm[2];  
//extern char SetPSDBuf[8];
//extern unsigned char WaterFlowFlag;
////开机读取EEP
//void EEP_ReadDefault(void)
//{
//	EEPROM_ReadSeq(EEP_MasterSN, (INT8U*)MasterNumber, sizeof(MasterNumber));
//	OSTimeDly(10);
//	
//	EEPROM_ReadSeq(EEP_Language, (INT8U*)&GB_SYSParam.Language, sizeof(GB_SYSParam.Language));
//	OSTimeDly(10);
//	
//	//声音
//	EEPROM_ReadSeq(EEP_Sound, (INT8U*)&GB_SYSParam.SoundVal, sizeof(GB_SYSParam.SoundVal));
//	OSTimeDly(10);
//	
//	//瞄准光
//	EEPROM_ReadSeq(EEP_Aiming, (INT8U*)&GB_SYSParam.AimLevel, sizeof(GB_SYSParam.AimLevel));
//	OSTimeDly(10);
//	
//	EEPROM_ReadSeq(EEP_TotalCnt, (INT8U*)&GB_SYSParam.TotalCount, sizeof(GB_SYSParam.TotalCount));
//	OSTimeDly(50);

//	EEPROM_ReadSeq(EEP_M1064Param, (INT8U*)(&EV_1064Parm), sizeof(EV_1064Parm));
//	vTaskDelay(20); 
//	EEPROM_ReadSeq(EEP_M532Param, (INT8U*)(&EV_532Parm), sizeof(EV_532Parm));									
//	vTaskDelay(20); 
//	
//	EEPROM_ReadSeq(EEP_PSWSet, (INT8U*)SetPSDBuf, sizeof(SetPSDBuf));
//	OSTimeDly(10);
//	//-------------------------------------
//	
//	EEPROM_ReadSeq(EEP_M532Adj, (INT8U*)(&GB_SYSParam.M532Adj), sizeof(GB_SYSParam.M532Adj));
//	vTaskDelay(10); 
//	EEPROM_ReadSeq(EEP_M1064Adj, (INT8U*)(&GB_SYSParam.M1064Adj), sizeof(GB_SYSParam.M1064Adj));									
//	vTaskDelay(10); 
//	
//	//读取 WaterFlowFlag
//	EEPROM_ReadSeq(EEP_WFLOWCHOSE,  (INT8U *)&WaterFlowFlag, sizeof(WaterFlowFlag));
//	OSTimeDly(10);
//}

//void EEP_WriteDefault(void)
//{
//	if(MasterNumber[0]<'0' || MasterNumber[0]>'9')		//不在这个范围内的要初始化
//	{
//		char DefaultSN[16] = "1A029999999";		//主机序列号 
//	
//		MemoryCopy(MasterNumber, DefaultSN, sizeof(DefaultSN));
//		EEPROM_WriteSeq(EEP_MasterSN, (INT8U*)DefaultSN, sizeof(DefaultSN));
//		OSTimeDly(10);
//	}
//	
//	GB_SYSParam.Language = English;
//	EEPROM_WriteSeq(EEP_Language, (INT8U*)&GB_SYSParam.Language, sizeof(GB_SYSParam.Language));
//	OSTimeDly(10);
//	
//	//瞄准光
//	GB_SYSParam.AimLevel = 5;
//	EEPROM_WriteSeq(EEP_Aiming, (INT8U*)&GB_SYSParam.AimLevel, sizeof(GB_SYSParam.AimLevel));
//	OSTimeDly(10);
//	
//	MemoryCopy(SetPSDBuf, "123456", sizeof(SetPSDBuf));  
//	EEPROM_WriteSeq(EEP_PSWSet, (INT8U*)SetPSDBuf, sizeof(SetPSDBuf));
//	OSTimeDly(10);
//	
//	if(GB_SYSParam.M532Adj != true)
//	{
//		GB_SYSParam.M532Adj = false;
//		EEPROM_WriteSeq(EEP_M532Adj, (INT8U*)(&GB_SYSParam.M532Adj), sizeof(GB_SYSParam.M532Adj));
//		vTaskDelay(10); 
//	}
//	if(GB_SYSParam.M1064Adj != true)
//	{
//		GB_SYSParam.M1064Adj = false;
//		EEPROM_WriteSeq(EEP_M1064Adj, (INT8U*)(&GB_SYSParam.M1064Adj), sizeof(GB_SYSParam.M1064Adj));
//		vTaskDelay(10);
//	}
//	
//	//-----------------------------------------------------------------------
//	WaterFlowFlag = false;		//V3.5之后 水流除以2
//	EEPROM_WriteSeq(EEP_WFLOWCHOSE,  (INT8U *)&WaterFlowFlag, sizeof(WaterFlowFlag));
//	OSTimeDly(10);
//}


//void EEP_WriteDefaultCalib(void)
//{
//	//-----------------------------------------------------------------------
//	CaliPARAM Temp_1064Parm[4] = {  0.4, 500,	
//									0.6, 400,	
//									1.3, 200,	
//									1.7, -100,};
//							
//	CaliPARAM Temp_532Parm[2] = {   0.6, 500,
//									1.4, 350, };

//	MemoryCopy(EV_1064Parm, Temp_1064Parm, sizeof(EV_1064Parm));  
//	MemoryCopy(EV_532Parm, Temp_532Parm, sizeof(EV_532Parm));    
//									
//	EEPROM_WriteSeq(EEP_M1064Param, (INT8U*)(&EV_1064Parm), sizeof(EV_1064Parm));
//	vTaskDelay(20); 
//	EEPROM_WriteSeq(EEP_M532Param, (INT8U*)(&EV_532Parm), sizeof(EV_532Parm));									
//	vTaskDelay(20); 
//	//-----------------------------------------------------------------------
//	
//	//恢复未校准状态
//	GB_SYSParam.M532Adj = false;
//	EEPROM_WriteSeq(EEP_M532Adj, (INT8U*)(&GB_SYSParam.M532Adj), sizeof(GB_SYSParam.M532Adj));
//	vTaskDelay(10); 
//			
//	GB_SYSParam.M1064Adj = false;
//	EEPROM_WriteSeq(EEP_M1064Adj, (INT8U*)(&GB_SYSParam.M1064Adj), sizeof(GB_SYSParam.M1064Adj));
//	vTaskDelay(10);
//	//-----------------------------------------------------------------------								
//}

////================================================================
//void DSPCalibrate1064Param(void)
//{
//	//-----------------------------------------------------
//	char CalibBuf1[8][12]={0};
//	char textbuf1[50] = "";
//	char textbuf2[50] = "";
//	
//	my_sprintf(CalibBuf1[0], 3, EV_1064Parm[0].param_k);
//	my_sprintf(CalibBuf1[1], 3, EV_1064Parm[0].param_b);
//	my_sprintf(CalibBuf1[2], 3, EV_1064Parm[1].param_k);
//	my_sprintf(CalibBuf1[3], 3, EV_1064Parm[1].param_b);
//	my_sprintf(CalibBuf1[4], 3, EV_1064Parm[2].param_k);
//	my_sprintf(CalibBuf1[5], 3, EV_1064Parm[2].param_b);
//	my_sprintf(CalibBuf1[6], 3, EV_1064Parm[3].param_k);
//	my_sprintf(CalibBuf1[7], 3, EV_1064Parm[3].param_b);
//	
//	strcat(textbuf1,"k1=");
//	strcat(textbuf1,CalibBuf1[0]);
//	strcat(textbuf1," b1=");
//	strcat(textbuf1,CalibBuf1[1]);
//	strcat(textbuf1," k2=");
//	strcat(textbuf1,CalibBuf1[2]);
//	strcat(textbuf1," b2=");
//	strcat(textbuf1,CalibBuf1[3]);
//	
//	strcat(textbuf2,"k3=");
//	strcat(textbuf2,CalibBuf1[4]);
//	strcat(textbuf2," b3=");
//	strcat(textbuf2,CalibBuf1[5]);
//	strcat(textbuf2," k4=");
//	strcat(textbuf2,CalibBuf1[6]);
//	strcat(textbuf2," b4=");
//	strcat(textbuf2,CalibBuf1[7]);
//	
//	HMI_TXStrToEdit(TE_EN_Param1, textbuf1, 50);	//
//	HMI_TXStrToEdit(TE_EN_Param2, textbuf2, 50);	//
//	//-----------------------------------------------------
//}

//void DSPCalibrate532Param(void)
//{
//	//-----------------------------------------------------
//	char CalibBuf1[8][12]={0};
//	char textbuf1[50] = "";
//	char textbuf2[50] = "";
//	
//	
//	my_sprintf(CalibBuf1[0], 3, EV_532Parm[0].param_k);
//	my_sprintf(CalibBuf1[1], 3, EV_532Parm[0].param_b);
//	my_sprintf(CalibBuf1[2], 3, EV_532Parm[1].param_k);
//	my_sprintf(CalibBuf1[3], 3, EV_532Parm[1].param_b);
//	
//	strcat(textbuf1,"k1=");
//	strcat(textbuf1,CalibBuf1[0]);
//	strcat(textbuf1," b1=");
//	strcat(textbuf1,CalibBuf1[1]);
//	strcat(textbuf1," k2=");
//	strcat(textbuf1,CalibBuf1[2]);
//	strcat(textbuf1," b2=");
//	strcat(textbuf1,CalibBuf1[3]);
//	
//	HMI_TXStrToEdit(TE_EN_Param1, textbuf1, 50);	//
//	HMI_TXStrToEdit(TE_EN_Param2, textbuf2, 50);	//
//	//-----------------------------------------------------
//}


////---------------------------------------------------------------------
////是KEIL ARM的ARM-CC编译器不支持sprintf函数的float显示
////解决办法：把float分成两个unsigned int 数，再显示
//void my_sprintf(char *str, unsigned char bitnum, float value)
//{
//	float val = value;
//	char *buffer = str;
//	int Intergar = 0;
//	int Decimal = 0;
//	int BitVal = 0; 
//	
//	BitVal = (int)pow(10, bitnum);
//	
//	Intergar = (int)val;
//	Decimal = (int)( val*BitVal - Intergar*BitVal );
//	Decimal = abs(Decimal);		//绝对值
//	
//	if(Intergar==0 && val<0)	//打印 -0.123
//	{
//		if(bitnum == 1)
//			sprintf(buffer,"-0.%01d", Decimal); 
//		else if(bitnum == 2)
//			sprintf(buffer,"-0.%02d", Decimal);
//		else if(bitnum == 3)
//			sprintf(buffer,"-0.%03d", Decimal);
//		else if(bitnum == 4)
//			sprintf(buffer,"-0.%04d", Decimal);	
//	}
//	else
//	{  
//		if(bitnum == 1)
//			sprintf(buffer,"%d.%01d", Intergar, Decimal); 
//		else if(bitnum == 2)
//			sprintf(buffer,"%d.%02d", Intergar, Decimal);
//		else if(bitnum == 3)
//			sprintf(buffer,"%d.%03d", Intergar, Decimal);
//		else if(bitnum == 4)
//			sprintf(buffer,"%d.%04d", Intergar, Decimal);
//	}
//}
//------------------------------------------------------------
//------------------------------------------------------------
//-----------------------(File End)---------------------------
//------------------------------------------------------------
//------------------------------------------------------------
