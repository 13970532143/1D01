#include "HMI_Driver_T5.h"


void HIM_SCR_ID(unsigned short addr)
{
	unsigned char buf[64] = {0};
	

	buf[0] = HMI_HEADER_H;
	buf[1] = HMI_HEADER_L;
	buf[2] = 0x07;//数据长度，指令、数据和校验
	buf[3] = 0x82;
	buf[4] = 0x00;	//高位
	buf[5] = 0x84;	//低位    
	buf[6] = 0x5A;    
	buf[7] = 0x01;   
    buf[8] = (unsigned char)(addr >> 8);	//高位
	buf[9] = (unsigned char)(addr&0xFF);	//低位 
	USART3_SendData(buf, 10);	
}

void  HIM_ADJ()
{
    unsigned char buf[64] = {0};
    u8 i=0;
    for(i=0;i<31;i++)
    {
        buf[i] = 0x55;
    }
    USART3_SendData(buf, 31);
}
