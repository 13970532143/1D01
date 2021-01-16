#include "HMI_Driver_T5.h"


void HIM_SCR_ID(unsigned short addr)
{
	unsigned char buf[64] = {0};
	

	buf[0] = HMI_HEADER_H;
	buf[1] = HMI_HEADER_L;
	buf[2] = 0x07;//���ݳ��ȣ�ָ����ݺ�У��
	buf[3] = 0x82;
	buf[4] = 0x00;	//��λ
	buf[5] = 0x84;	//��λ    
	buf[6] = 0x5A;    
	buf[7] = 0x01;   
    buf[8] = (unsigned char)(addr >> 8);	//��λ
	buf[9] = (unsigned char)(addr&0xFF);	//��λ 
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
