/*************************************************************
**
**  Project Name :  SDL-F
**
**  Created By   :  PYF 
**
** 	Created Date :  2016/04/04  
**
**************************************************************/
#include "USART3_Driver.h"


char VersionD[16] = "";   
u16 BT_CMD = 0xFFFF;    //������ַ
u16 BT_KEY = 0xFFFF;    //������ֵ
u8 him_rx_buf[50] = {0};
u8 Lenght=0; 
u8 Sts_RX_END =0;
u8 GET_Time_Data = 0;
void USART3_Init(unsigned int baund)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	USART_DeInit(USART3); 
	//-------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//TXD--PB10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	//RXD--PB11
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;			//�������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	//--------------------------------------------------------------------
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;		
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	//---------------------------------------------------------------------
	//����USART�������
	USART_InitStructure.USART_BaudRate = baund;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	USART_Init(USART3, &USART_InitStructure);
	//
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	//����3 �����ж�ʹ��
	USART_Cmd(USART3, ENABLE);						//�����豸USART
 	USART_ClearFlag(USART3, USART_FLAG_TC);         //����жϱ�־λ
}

// ���ڷ����ֽ�����
void USART3_Sendbyte(u8 byte)
{
	while(USART_GetFlagStatus(USART3,USART_FLAG_TXE)!=SET);
	USART_SendData(USART3, byte);
	while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);

}

//-------------------------------------------------------------------------------------------
//�����ַ���
void USART3_SendData(unsigned char *ptr, unsigned char num)   
{
	if(ptr == (unsigned char *)0)
		return;
	
	while(num--)
	{		
		USART3_Sendbyte(*ptr++);
	}
}

INT8U uirxbuf[50]={0};
void USART3_IRQHandler()
{
//	static INT8U uirxbuf[50]={0};
	static INT8U uirxnum=0;
 	//--- ֪ͨucosii���жϷ����ӳ���ʼ�� ------------
	OS_CPU_SR cpu_sr;
	OS_ENTER_CRITICAL();  	//�����ж�
	OSIntNesting++;
	OS_EXIT_CRITICAL();	   	//�����ж�
	//-------------------------------------------------
	//��������
	//5A A5 06 83 00 24 02 00 00
    //ͷ:5A A5 ����:06  ������:83  ������ַ:0024  (��ֵ)�ֳ���:01  ��ֵ:0000
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
         
        uirxbuf[uirxnum] = USART_ReceiveData(USART3); 
        him_rx_buf[uirxnum] = uirxbuf[uirxnum];
//        printf("%x ",him_rx_buf[uirxnum]);
        uirxnum++;
        if(GET_Time_Data==0)
        {
            if(uirxnum == 0x01 && uirxbuf[0] != 0x5A)
                uirxnum = 0;
            else if(uirxnum == 0x02 && uirxbuf[1] != 0xA5)
                uirxnum = 0;
            else if(uirxnum == 0x09)
            {
                uirxnum=0;	
                BT_CMD = (uirxbuf[4]<<8) + uirxbuf[5];
                BT_KEY = (uirxbuf[7]<<8) + uirxbuf[8];
                
            }
            else if(uirxnum > 0x09)
            {
                uirxnum=0;
            }
        }
        else
        {
            if(uirxnum == 0x01 && uirxbuf[0] != 0x5A)
                uirxnum = 0;
            else if(uirxnum == 0x02 && uirxbuf[1] != 0xA5)
                uirxnum = 0;
            
            if(uirxnum > 12)
            {
                uirxnum=0;
                GET_Time_Data = 2;
            }
        }
                
	}
	//LED1_TGL;
	//-------------------------------------------------
	OSIntExit();  //֪ͨucosii���жϷ������ִ�����
}

//�жϽ���
void GetButtonData(unsigned short *btValue)
{
    u8 i=0;
    *btValue = BT_CMD;
    if(BT_CMD!=0xFFFF)
    {
        for(i=0;i<15;i++)
        {
            printf("%x ",uirxbuf[i]);
        }
        printf("\r\n");
    }
    BT_CMD = 0xFFFF; 

}
//��ȡ��ť�ؼ��ļ�ֵ
void GETButtonKEY(unsigned short *btKey)
{
	*btKey = BT_KEY;
    BT_KEY = 0xFFFF; 
}

u8 Get_HIM_Date(void )
{
    u8 i=0;
//    Set_HIM_Date(sys_var.date);
//    delay_ms(500);
    GET_Time_Data = 1;
    HMI_ReadRegCmd(0x20,7);
    
    delay_ms(200);
    
    for(i=0;i<20;i++)
    {
        printf("%x ",him_rx_buf[i]);
    }
//    printf("\r\n");
//    if(GET_Time_Data==2)
//    {
//        for(i=0;i<7;i++)
//        {
//            sys_var.date[i] = (him_rx_buf[6+i]>>4)*10+(him_rx_buf[6+i]&0x0F);
//            
//        }  
//        GET_Time_Data = 0;    
//        return 1;
//    }

    GET_Time_Data = 0;
    return 0;
}
    
//------------------------------------------------------------
//------------------------------------------------------------
//------------------------------------------------------------
//-----------------------(File End)---------------------------
//------------------------------------------------------------
//------------------------------------------------------------




