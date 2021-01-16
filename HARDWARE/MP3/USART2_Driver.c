/*************************************************************
**
**  Project Name :  CO2
**
**  Created By   :  PYF 
**
** 	Created Date :  2016/04/14
**
***************************************************************/
//
#include "includes.h"
//

//MP3 + Calibrate + Wifi -- USART2
void USART2_Init(unsigned int baund)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	USART_DeInit(USART2); 
	//-------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//TXD--PA2
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//RXD--PA3
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//上拉输入 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//--------------------------------------------------------------------
	//配置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
	NVIC_Init(&NVIC_InitStructure);
	
	//--------------------------------------------------------------------
	//配置USART相关属性
	USART_InitStructure.USART_BaudRate = baund;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART_InitStructure);
	//
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	//串口2 接收中断使能
	USART_Cmd(USART2, ENABLE);						//启动设备USART
 	USART_ClearFlag(USART2, USART_FLAG_TC);         //清除中断标志位
}

//-------------------------------------------------------------------------------------------
//发送一个字符
void USART2_SendByte(INT8U value)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE)!=SET);
	USART_SendData(USART2, value);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC)!=SET);
}

//发送字符串
void USART2_SendData(unsigned char *ptr, unsigned char num)   
{
	if(ptr == (unsigned char *)0)
		return;
	
	while(num--)
	{		
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE)!=SET);
		USART_SendData(USART2, *ptr++);
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)!=SET);
	}
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
//============================================================================
//============================================================================
//MP3控制代码  波特率9600
void MP3USART_SendByte(INT8U value)
{
	USART2_SendByte(value);
}
//----------------------------------------------------------------------------
void MP3_SendCmd(unsigned char *buf, INT8U len)
{
    INT8U i = 0;

	MP3USART_SendByte(0x7E);		//起始
    for(i=0; i<len; i++)//数据
    {
		  MP3USART_SendByte(buf[i]);
    }
	MP3USART_SendByte(0xEF);	//结束
}

//----------------------------------------------------------------------------
void DoSum( INT8U *Str, INT8U len)
{
    INT16U xorsum = 0;
    INT8U i;

    for(i=0; i<len; i++)
    {
        xorsum  = xorsum + Str[i];
    }
	xorsum     = 0 -xorsum;
	*(Str+i)   = (INT8U)(xorsum >>8);
	*(Str+i+1) = (INT8U)(xorsum & 0x00ff);
}

//----------------------------------------------------------------------------
void MyMP3Usart_SendCMD(INT8U CMD ,INT8U feedback , INT16U dat)
{
	unsigned char Send_buf[12]={0};
	//-----------------------------------------------
    Send_buf[0] = 0xff;    				//保留字节 
    Send_buf[1] = 0x06;    				//长度
    Send_buf[2] = CMD;     				//控制指令
    Send_buf[3] = feedback;				//是否需要反馈
    Send_buf[4] = (INT8U)(dat >> 8);	//datah
    Send_buf[5] = (INT8U)(dat);     	//datal
    DoSum(&Send_buf[0],6);        		//校验 2Byte
	//------------------------------------------------
    MP3_SendCmd(Send_buf, 8);       	//发送此帧数据
}

//-----------------------------------------------------
// 7E FF 06 03 00   00 01   FE F7 EF  //播放第一首声音 
// 0x01(第一首) 、0x02(第二首) 、0x03(第三首) 
void MP3_Play_Once(INT8U data)    //data---播放第几首歌曲
{
	unsigned char Send_buf[12]={0};
	//-----------------------------------------------
    Send_buf[0] = 0xff;    				//保留字节 
    Send_buf[1] = 0x06;    				//长度
    Send_buf[2] =  0x03;     			//控制指令
    Send_buf[3] =  0x00;				//0:不需要应答
	
    Send_buf[4] =  0x00;				//datah
    Send_buf[5] =  data;     			//datal
	
	MP3_SendCmd(Send_buf, 6);       	//发送此帧数据
}

//----------------------------------------------------
//7E FF 06 06 00 00 1E EF
void MP3_Send_Sound(INT8U data)    //音量调节
{
	unsigned char Send_buf[12]={0};
	//-----------------------------------------------
    Send_buf[0] = 0xff;    				//保留字节 
    Send_buf[1] = 0x06;    				//长度
    Send_buf[2] =  0x06;     			//控制指令
    Send_buf[3] =  0x00;				//是否需要反馈
    Send_buf[4] =  0x00;				//datah
    Send_buf[5] =  data;     			//datal
	MP3_SendCmd(Send_buf, 6);       	//发送此帧数据
}
void MP3_Send_Song(INT8U data)    //单曲循环播放指令
{
	unsigned char Send_buf[12]={0};
	//-----------------------------------------------
    Send_buf[0] = 0xff;    				//保留字节 
    Send_buf[1] = 0x06;    				//长度
    Send_buf[2] =  0x08;     		    //控制指令
    Send_buf[3] =  0x00;				//是否需要反馈
    Send_buf[4] =  0x00;	            //datah
    Send_buf[5] =  data;     	        //datal
	MP3_SendCmd(Send_buf, 6);       	//发送此帧数据
}
 
void MP3_Play_Stop(void)               //停止
{
	unsigned char Send_buf[12]={0};
	//-----------------------------------------------
    Send_buf[0] = 0xff;    				//保留字节 
    Send_buf[1] = 0x06;    				//长度
    Send_buf[2] =  0x16;     			//控制指令
    Send_buf[3] =  0x00;				//是否需要反馈
    Send_buf[4] =  0x00;				//datah
    Send_buf[5] =  0x00;     			//datal
	MP3_SendCmd(Send_buf, 6);       	//发送此帧数据
	MP3_SendCmd(Send_buf, 6);       	//发送此帧数据
}



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


//查询播放状态
//在任何时候都可以查询当前的播放状态
void SV17F_MP3_Query(void)
{
    unsigned char Send_buf[12]={0};
    Send_buf[0] = 0xAA;    				//指令码 
    Send_buf[1] = 0x01;    				//指令
    Send_buf[2] = 0x00;     			//数据长度
    Send_buf[3] = 0xAB;				    //和检验
    MP3_SendCmd(Send_buf, 4);       	//发送此帧数据
}
//播放指定的曲目
void SV17F_MP3_Specify(u16 music)
{
    unsigned char Send_buf[12]={0};
    Send_buf[0] = 0xAA;    				//指令码 
    Send_buf[1] = 0x07;    				//指令
    Send_buf[2] = 0x02;     			//数据长度
    Send_buf[3] = (music>>8)&0xFF;				    //和检验
    Send_buf[4] = music&0xFF;				    //和检验
    Send_buf[5] = (Send_buf[0]+Send_buf[1]+Send_buf[2]+Send_buf[3]+Send_buf[4])&0xFF;				    //和检验
    MP3_SendCmd(Send_buf, 6);       	//发送此帧数据
}

//结束播放
void SV17F_MP3_Finsh(void)
{
    unsigned char Send_buf[12]={0};
    Send_buf[0] = 0xAA;    				//指令码 
    Send_buf[1] = 0x10;    				//指令
    Send_buf[2] = 0x00;     			//数据长度
    Send_buf[3] = 0xBA;				    //和检验
    MP3_SendCmd(Send_buf, 4);       	//发送此帧数据
    
}

//设置音量
void SV17F_Set_Vol(u8 vol)
{
    unsigned char Send_buf[12]={0};
    Send_buf[0] = 0xAA;    				//指令码 
    Send_buf[1] = 0x13;    				//指令
    Send_buf[2] = 0x01;     			//数据长度
    Send_buf[3] = vol;				    //和检验
    Send_buf[4] = (Send_buf[0]+Send_buf[1]+Send_buf[2]+Send_buf[3])&0xFF;				    //和检验
    MP3_SendCmd(Send_buf, 5);       	//发送此帧数据
}
//=====================================================================
//=====================================================================


