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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

	//RXD--PA3
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//�������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	//--------------------------------------------------------------------
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
	NVIC_Init(&NVIC_InitStructure);
	
	//--------------------------------------------------------------------
	//����USART�������
	USART_InitStructure.USART_BaudRate = baund;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART2, &USART_InitStructure);
	//
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	//����2 �����ж�ʹ��
	USART_Cmd(USART2, ENABLE);						//�����豸USART
 	USART_ClearFlag(USART2, USART_FLAG_TC);         //����жϱ�־λ
}

//-------------------------------------------------------------------------------------------
//����һ���ַ�
void USART2_SendByte(INT8U value)
{
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE)!=SET);
	USART_SendData(USART2, value);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC)!=SET);
}

//�����ַ���
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
//MP3���ƴ���  ������9600
void MP3USART_SendByte(INT8U value)
{
	USART2_SendByte(value);
}
//----------------------------------------------------------------------------
void MP3_SendCmd(unsigned char *buf, INT8U len)
{
    INT8U i = 0;

	MP3USART_SendByte(0x7E);		//��ʼ
    for(i=0; i<len; i++)//����
    {
		  MP3USART_SendByte(buf[i]);
    }
	MP3USART_SendByte(0xEF);	//����
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
    Send_buf[0] = 0xff;    				//�����ֽ� 
    Send_buf[1] = 0x06;    				//����
    Send_buf[2] = CMD;     				//����ָ��
    Send_buf[3] = feedback;				//�Ƿ���Ҫ����
    Send_buf[4] = (INT8U)(dat >> 8);	//datah
    Send_buf[5] = (INT8U)(dat);     	//datal
    DoSum(&Send_buf[0],6);        		//У�� 2Byte
	//------------------------------------------------
    MP3_SendCmd(Send_buf, 8);       	//���ʹ�֡����
}

//-----------------------------------------------------
// 7E FF 06 03 00   00 01   FE F7 EF  //���ŵ�һ������ 
// 0x01(��һ��) ��0x02(�ڶ���) ��0x03(������) 
void MP3_Play_Once(INT8U data)    //data---���ŵڼ��׸���
{
	unsigned char Send_buf[12]={0};
	//-----------------------------------------------
    Send_buf[0] = 0xff;    				//�����ֽ� 
    Send_buf[1] = 0x06;    				//����
    Send_buf[2] =  0x03;     			//����ָ��
    Send_buf[3] =  0x00;				//0:����ҪӦ��
	
    Send_buf[4] =  0x00;				//datah
    Send_buf[5] =  data;     			//datal
	
	MP3_SendCmd(Send_buf, 6);       	//���ʹ�֡����
}

//----------------------------------------------------
//7E FF 06 06 00 00 1E EF
void MP3_Send_Sound(INT8U data)    //��������
{
	unsigned char Send_buf[12]={0};
	//-----------------------------------------------
    Send_buf[0] = 0xff;    				//�����ֽ� 
    Send_buf[1] = 0x06;    				//����
    Send_buf[2] =  0x06;     			//����ָ��
    Send_buf[3] =  0x00;				//�Ƿ���Ҫ����
    Send_buf[4] =  0x00;				//datah
    Send_buf[5] =  data;     			//datal
	MP3_SendCmd(Send_buf, 6);       	//���ʹ�֡����
}
void MP3_Send_Song(INT8U data)    //����ѭ������ָ��
{
	unsigned char Send_buf[12]={0};
	//-----------------------------------------------
    Send_buf[0] = 0xff;    				//�����ֽ� 
    Send_buf[1] = 0x06;    				//����
    Send_buf[2] =  0x08;     		    //����ָ��
    Send_buf[3] =  0x00;				//�Ƿ���Ҫ����
    Send_buf[4] =  0x00;	            //datah
    Send_buf[5] =  data;     	        //datal
	MP3_SendCmd(Send_buf, 6);       	//���ʹ�֡����
}
 
void MP3_Play_Stop(void)               //ֹͣ
{
	unsigned char Send_buf[12]={0};
	//-----------------------------------------------
    Send_buf[0] = 0xff;    				//�����ֽ� 
    Send_buf[1] = 0x06;    				//����
    Send_buf[2] =  0x16;     			//����ָ��
    Send_buf[3] =  0x00;				//�Ƿ���Ҫ����
    Send_buf[4] =  0x00;				//datah
    Send_buf[5] =  0x00;     			//datal
	MP3_SendCmd(Send_buf, 6);       	//���ʹ�֡����
	MP3_SendCmd(Send_buf, 6);       	//���ʹ�֡����
}



//-------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------


//��ѯ����״̬
//���κ�ʱ�򶼿��Բ�ѯ��ǰ�Ĳ���״̬
void SV17F_MP3_Query(void)
{
    unsigned char Send_buf[12]={0};
    Send_buf[0] = 0xAA;    				//ָ���� 
    Send_buf[1] = 0x01;    				//ָ��
    Send_buf[2] = 0x00;     			//���ݳ���
    Send_buf[3] = 0xAB;				    //�ͼ���
    MP3_SendCmd(Send_buf, 4);       	//���ʹ�֡����
}
//����ָ������Ŀ
void SV17F_MP3_Specify(u16 music)
{
    unsigned char Send_buf[12]={0};
    Send_buf[0] = 0xAA;    				//ָ���� 
    Send_buf[1] = 0x07;    				//ָ��
    Send_buf[2] = 0x02;     			//���ݳ���
    Send_buf[3] = (music>>8)&0xFF;				    //�ͼ���
    Send_buf[4] = music&0xFF;				    //�ͼ���
    Send_buf[5] = (Send_buf[0]+Send_buf[1]+Send_buf[2]+Send_buf[3]+Send_buf[4])&0xFF;				    //�ͼ���
    MP3_SendCmd(Send_buf, 6);       	//���ʹ�֡����
}

//��������
void SV17F_MP3_Finsh(void)
{
    unsigned char Send_buf[12]={0};
    Send_buf[0] = 0xAA;    				//ָ���� 
    Send_buf[1] = 0x10;    				//ָ��
    Send_buf[2] = 0x00;     			//���ݳ���
    Send_buf[3] = 0xBA;				    //�ͼ���
    MP3_SendCmd(Send_buf, 4);       	//���ʹ�֡����
    
}

//��������
void SV17F_Set_Vol(u8 vol)
{
    unsigned char Send_buf[12]={0};
    Send_buf[0] = 0xAA;    				//ָ���� 
    Send_buf[1] = 0x13;    				//ָ��
    Send_buf[2] = 0x01;     			//���ݳ���
    Send_buf[3] = vol;				    //�ͼ���
    Send_buf[4] = (Send_buf[0]+Send_buf[1]+Send_buf[2]+Send_buf[3])&0xFF;				    //�ͼ���
    MP3_SendCmd(Send_buf, 5);       	//���ʹ�֡����
}
//=====================================================================
//=====================================================================


