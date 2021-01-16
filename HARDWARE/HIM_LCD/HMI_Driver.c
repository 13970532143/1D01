/*************************************************************
**
**  Project Name :  SDL-B
**
**  Created By   :  PYF 
**
** 	Created Date :  2017/08/01
**
**************************************************************/
//
#include "HMI_Driver.h"
//
//---------------------------------------------------------




void HMI_SendData(unsigned char *buf, unsigned char len)
{
	USART3_SendData(buf, len);
//	delay_ms(50);
}

/********************************************************************************************************
����˵������ȡ�������Ĵ�������
������ڣ�addr���Ĵ�����ʼ��ַ��length���ֽڳ���
�������أ���
*********************************************************************************************************/
//5A A5 03 81 00 01
void HMI_ReadRegCmd(unsigned char addr,unsigned char length)
{
	unsigned char buf[64] = {0};
	
	buf[0] = HMI_HEADER_H;
	buf[1] = HMI_HEADER_L;
	buf[2] = 3;//���ݳ��ȣ�ָ����ݺ�У��
	buf[3] = READ_REG_CMD;
	buf[4] = addr;
	buf[5] = length;
	HMI_SendData(buf, 6);
}

/********************************************************************************************************
����˵������ȡ������������ַ����
������ڣ�addr��������ʼ��ַ��length���ֳ���
�������أ���
*********************************************************************************************************/
//5A A5 04 83 0000 01
void HMI_ReadVarCmd(unsigned short addr,unsigned char length)
{
	unsigned char buf[64] = {0};
	
	if(length>0x80)
	{
		return;
	}	
	buf[0] = HMI_HEADER_H;
	buf[1] = HMI_HEADER_L;
	buf[2] = 4;//���ݳ��ȣ�ָ����ݺ�У��
	buf[3] = READ_VAR_CMD;
	buf[4] = (unsigned char)(addr >> 8);	//��λ
	buf[5] = (unsigned char)(addr&0xFF);	//��λ
	buf[6] = length;
	HMI_SendData(buf, 7);	
}

/********************************************************************************************************
����˵������������Ĵ���д������
������ڣ�addr���Ĵ�����ʼ��ַ��pdata:����ָ�룬length���ֽڳ���
�������أ���   
*********************************************************************************************************/
// 5A A5 04 80 03 00 03
void HMI_WriteRegCmd(unsigned char addr,unsigned short *pdata,unsigned char length)
{
	unsigned char TXBuf[32] = {0};
	unsigned char i;
	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = length + 2;		
	TXBuf[3] = WRITE_REG_CMD;				//0x80
	TXBuf[4] = addr;						//�Ĵ�����ʼ��ַ --- ����
	
	for(i=0;i<length;i+=2)
	{
		TXBuf[i+5] = (unsigned char)((*pdata) >> 8);
		TXBuf[i+6] = (unsigned char)((*pdata)&0xFF);
		pdata++;
	}
	HMI_SendData(TXBuf, length+5); 
}


//-------------------------------------------------------------------------
//��������100ms 5A A5 03 80 02 0A 
void HMI_BEEP_TIME(u8 var)
{
    unsigned char TXBuf[32] = {0};
	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 0x03;		
	TXBuf[3] = 0x80;				//0x80
	TXBuf[4] = 0x02;    
    TXBuf[5] = var;
    
    TXBuf[6] = HMI_HEADER_H;
	TXBuf[7] = HMI_HEADER_L;
	TXBuf[8] = 0x03;		
	TXBuf[9] = 0x80;				//0x80
	TXBuf[10] = 0x02;    
    TXBuf[11] = 0x5A;
    HMI_SendData(TXBuf, 12); 
}

//5A A5 03 80 1C 20     5A A5 03 80 1D 5A ��������ť�����ر� ����
//5A A5 03 80 1C 00     5A A5 03 80 1D 5A ��������ť��������
//sta 0-->�ر�������������1-->��������
void HMI_BEEP_ENABLE(u8 sta)
{
    unsigned char TXBuf[32] = {0};
	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 0x03;		
	TXBuf[3] = 0x80;				//0x80
	TXBuf[4] = 0x1C;    
    if(sta==0)
    {
        TXBuf[5] = 0x20;
    }
    else if(sta==1)
    {
        TXBuf[5] = 0x00;
    }
    TXBuf[6] = HMI_HEADER_H;
	TXBuf[7] = HMI_HEADER_L;
	TXBuf[8] = 0x03;		
	TXBuf[9] = 0x80;				//0x80
	TXBuf[10] = 0x1D;    
    TXBuf[11] = 0x5A;
    
    HMI_SendData(TXBuf, 12); 
}


//�л�����
// 5A A5 04 80 03 00 03
void HMI_ChangeScreen(unsigned short picID)
{
//    sys_var.Screen = picID;
	HMI_WriteRegCmd(REG_PIC_ID, &picID, 2);	//REG_PIC_ID --- 0x03
}

//-------------------------------------------------------------------------
//���ڱ���
// 5A A5 03 80 01 20
void HMI_BackLightCtrl(unsigned short val)  //0--64
{
	unsigned char TXBuf[32] = {0};
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 5;		
	TXBuf[3] = 0x82;				//0x80
	TXBuf[4] = 0x00;				//�Ĵ�����ʼ��ַ --- ����
    TXBuf[5] = 0x82;
	TXBuf[6] = val;
    TXBuf[7] = val;
	HMI_SendData(TXBuf, 8); 
}

//-------------------------------------------------------------------------
//��ĻУ׼
// 5A A5 03 80 EA 5A
void HMI_AdjustScreen(void) 
{
	unsigned char TXBuf[32] = {0};
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 3;		
	TXBuf[3] = WRITE_REG_CMD;				//0x80
	TXBuf[4] = 0xEA;						//�Ĵ�����ʼ��ַ --- ����
	TXBuf[5] = 0x5A;
	HMI_SendData(TXBuf, 6); 
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
/********************************************************************************************************
����˵�����������������ַд������
������ڣ�addr���Ĵ�����ʼ��ַ��pdata:����ָ�룬length��pdata�ֽڳ���
�������أ���
*********************************************************************************************************/
//5A A5 05 82 01 42 00 01
void HMI_WriteVarCmd(unsigned short addr,unsigned short *pdata,unsigned char length)
{
	unsigned char TXBuf[40] = {0};
	unsigned char i;
	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = length + 3;		
	TXBuf[3] = WRITE_VAR_CMD;				//0x82
	TXBuf[4] = (unsigned char)(addr >> 8);	//��λ
	TXBuf[5] = (unsigned char)(addr&0xFF);	//��λ
	for(i=0;i<length;i+=2)
	{
		TXBuf[i+6] = (unsigned char)((*pdata) >> 8);	
		TXBuf[i+7] = (unsigned char)((*pdata)&0xFF);
		pdata++;
	}
	HMI_SendData(TXBuf, length+6); 	
}

//-------------------------------------------------------------------------
//�л�ͼƬ    5A A5 05 82 00 20 00 01
void HMI_TXIconVal(unsigned short addr,unsigned short val)
{
	HMI_WriteVarCmd(addr, &val, 2);
}

//-------------------------------------------------------------------------
//дһ�� unsigned short �� ��������
//5A A5 05 82 01 42 00 01
void HMI_TXIntToEdit(unsigned short addr,unsigned short val)
{
	HMI_WriteVarCmd(addr, &val, 2);
}

//-------------------------------------------------------------------------
//дһ���ַ����� string ��������
//���ݳ���Length ������ �������ؼ����õĳ���һ�£�����ʾ�� д00
//5A A5 05 82 01 41 30 31
void HMI_TXStrToEdit(unsigned short addr, char *SourceStr, unsigned char Length)
{
	unsigned char len = strlen(SourceStr);
	unsigned char TXBuf[100] = {0};	
	unsigned char *pstr;
	unsigned char i=0;
	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = Length + 3;					
	TXBuf[3] = WRITE_VAR_CMD;				//0x82
	TXBuf[4] = (unsigned char)(addr >> 8);	//��λ
	TXBuf[5] = (unsigned char)(addr&0xFF);	//��λ

	pstr = &TXBuf[6];
	for(i=0; i<Length; i++)
	{
		if(len < Length)
			*pstr++ = *SourceStr++;
		else 
			*pstr++ = ' ';
	}
	HMI_SendData(TXBuf, TXBuf[2]+3);	
}

//��ʾ������ ���� �� С��λ�� , Ĭ�Ͽؼ����� len<20,bitnum<=3
void HMI_ShowNumber(unsigned short addr, int xCounter,u8 bitnum, u8 len)
{
	char StrBuf[24]={0};
    IntToStr_Decimal(xCounter, StrBuf, bitnum);
    HMI_TXStrToEdit(addr, StrBuf, len);			//�ؼ����� 20
}

//��ʾ������ ���� �� ����λ�� , Ĭ�Ͽؼ����� len<20,bitnum<=3
void HMI_ShowNumber_int(unsigned short addr, int xCounter,u8 bitnum, u8 len)
{
	char StrBuf[24]={0}; 
    myIntToStr(xCounter,StrBuf,bitnum);
    HMI_TXStrToEdit(addr, StrBuf, len);			//�ؼ����� 20
}

//-------------------------------------------------------------------------
//�� һ��ͼƬ�Ĺ̶���С ���Ƶ� ��ǰ����ġ�����ͼ����ʾ�� λ��
// 5a a5 15 82 40 01 00 06 00 01 00 03 02 55 01 c7 02 ed 02 25 02 55 01 c7
void HMI_PictureCopy_xy(unsigned short addr, unsigned short PageID,unsigned short Start_X,unsigned short Start_Y,unsigned short End_X,unsigned short End_Y)
{
	unsigned char TXBuf[28] = {0};	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 21;  									//���ݳ��ȣ�ָ����ݺ�У��
	TXBuf[3] = WRITE_VAR_CMD;						//0x82
	TXBuf[4] = (unsigned char)(addr >> 8);			//��λ
	TXBuf[5] = (unsigned char)(addr&0xFF);			//��λ
	TXBuf[6] = 0x00;
	TXBuf[7] = 0x06;
	TXBuf[8] = 0x00;
	TXBuf[9] = 0x01;
	TXBuf[10] = (unsigned char)(PageID >> 8);	//����ͼƬ����ҳ��ID ���ֽ�
	TXBuf[11] = (unsigned char)(PageID&0xFF);	//����ͼƬ����ҳ��ID ���ֽ�
	TXBuf[12] = (unsigned char)(Start_X >> 8);	//��ʼX���� ���ֽ�
	TXBuf[13] = (unsigned char)(Start_X&0xFF);	//��ʼX���� ���ֽ�
	TXBuf[14] = (unsigned char)(Start_Y >> 8);	//��ʼY���� ���ֽ�
	TXBuf[15] = (unsigned char)(Start_Y&0xFF);	//��ʼY���� ���ֽ�
	TXBuf[16] = (unsigned char)(End_X >> 8);	//����X���� ���ֽ�
	TXBuf[17] = (unsigned char)(End_X&0xFF);	//����X���� ���ֽ�
	TXBuf[18] = (unsigned char)(End_Y >> 8);	//����Y���� ���ֽ�
	TXBuf[19] = (unsigned char)(End_Y&0xFF);	//����Y���� ���ֽ�
	
	TXBuf[20] = (unsigned char)(Start_X >> 8);	//��ʼX���� ���ֽ�
	TXBuf[21] = (unsigned char)(Start_X&0xFF);	//��ʼX���� ���ֽ�
	TXBuf[22] = (unsigned char)(Start_Y >> 8);	//��ʼY���� ���ֽ�
	TXBuf[23] = (unsigned char)(Start_Y&0xFF);	//��ʼY���� ���ֽ�
	
	HMI_SendData(TXBuf, TXBuf[2]+3);	
}
//������ͼƬ
//addr:����ͼ�οؼ���ַ
//PageID������ͼƬ���ڵĽ���
//Start_X��Start_Y��End_X��End_Y������ͼƬ����ʼλ�ú�ĩβλ��
//target_x��target_x��Ŀ�����ͼ�οؼ�����ʼλ��
void HMI_PictureCopy_S_T_xy(unsigned short addr, unsigned short PageID,unsigned short Start_X,unsigned short Start_Y,unsigned short End_X,unsigned short End_Y,unsigned short target_x,unsigned short target_y)
{
	unsigned char TXBuf[28] = {0};	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 21;									//���ݳ��ȣ�ָ����ݺ�У��
	TXBuf[3] = WRITE_VAR_CMD;						//0x82
	TXBuf[4] = (unsigned char)(addr >> 8);			//��λ
	TXBuf[5] = (unsigned char)(addr&0xFF);			//��λ
	TXBuf[6] = 0x00;
	TXBuf[7] = 0x06;
	TXBuf[8] = 0x00;
	TXBuf[9] = 0x01;
	TXBuf[10] = (unsigned char)(PageID >> 8);	//����ͼƬ����ҳ��ID ���ֽ�
	TXBuf[11] = (unsigned char)(PageID&0xFF);	//����ͼƬ����ҳ��ID ���ֽ�
	TXBuf[12] = (unsigned char)(Start_X >> 8);	//��ʼX���� ���ֽ�
	TXBuf[13] = (unsigned char)(Start_X&0xFF);	//��ʼX���� ���ֽ�
	TXBuf[14] = (unsigned char)(Start_Y >> 8);	//��ʼY���� ���ֽ�
	TXBuf[15] = (unsigned char)(Start_Y&0xFF);	//��ʼY���� ���ֽ�
	TXBuf[16] = (unsigned char)(End_X >> 8);	//����X���� ���ֽ�
	TXBuf[17] = (unsigned char)(End_X&0xFF);	//����X���� ���ֽ�
	TXBuf[18] = (unsigned char)(End_Y >> 8);	//����Y���� ���ֽ�
	TXBuf[19] = (unsigned char)(End_Y&0xFF);	//����Y���� ���ֽ�
	//Ŀ��
	TXBuf[20] = (unsigned char)(target_x >> 8);	//��ʼX���� ���ֽ�
	TXBuf[21] = (unsigned char)(target_x&0xFF);	//��ʼX���� ���ֽ�
	TXBuf[22] = (unsigned char)(target_y >> 8);	//��ʼY���� ���ֽ�
	TXBuf[23] = (unsigned char)(target_y&0xFF);	//��ʼY���� ���ֽ�
	
	HMI_SendData(TXBuf, TXBuf[2]+3);	
}
//-------------------------------------------------------------------------
//�� һ��ͼƬ�Ĺ̶���С ���Ƶ� ��ǰ����ġ�����ͼ����ʾ�� λ��
// 5a a5 15 82 40 01 00 06 00 01 00 03 02 55 01 c7 02 ed 02 25 02 55 01 c7
void HMI_PictureCopy(unsigned short addr, HMI_PIC_COPY *para)
{
	unsigned char TXBuf[28] = {0};	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 21;									//���ݳ��ȣ�ָ����ݺ�У��
	TXBuf[3] = WRITE_VAR_CMD;						//0x82
	TXBuf[4] = (unsigned char)(addr >> 8);			//��λ
	TXBuf[5] = (unsigned char)(addr&0xFF);			//��λ
	TXBuf[6] = 0x00;
	TXBuf[7] = 0x06;
	TXBuf[8] = 0x00;
	TXBuf[9] = 0x01;
	TXBuf[10] = (unsigned char)(para->PageID >> 8);	//����ͼƬ����ҳ��ID ���ֽ�
	TXBuf[11] = (unsigned char)(para->PageID&0xFF);	//����ͼƬ����ҳ��ID ���ֽ�
	TXBuf[12] = (unsigned char)(para->Start_X >> 8);	//��ʼX���� ���ֽ�
	TXBuf[13] = (unsigned char)(para->Start_X&0xFF);	//��ʼX���� ���ֽ�
	TXBuf[14] = (unsigned char)(para->Start_Y >> 8);	//��ʼY���� ���ֽ�
	TXBuf[15] = (unsigned char)(para->Start_Y&0xFF);	//��ʼY���� ���ֽ�
	TXBuf[16] = (unsigned char)(para->End_X >> 8);	//����X���� ���ֽ�
	TXBuf[17] = (unsigned char)(para->End_X&0xFF);	//����X���� ���ֽ�
	TXBuf[18] = (unsigned char)(para->End_Y >> 8);	//����Y���� ���ֽ�
	TXBuf[19] = (unsigned char)(para->End_Y&0xFF);	//����Y���� ���ֽ�
	
	TXBuf[20] = (unsigned char)(para->Start_X >> 8);	//��ʼX���� ���ֽ�
	TXBuf[21] = (unsigned char)(para->Start_X&0xFF);	//��ʼX���� ���ֽ�
	TXBuf[22] = (unsigned char)(para->Start_Y >> 8);	//��ʼY���� ���ֽ�
	TXBuf[23] = (unsigned char)(para->Start_Y&0xFF);	//��ʼY���� ���ֽ�
	
	HMI_SendData(TXBuf, TXBuf[2]+3);	
}


void HMI_PicCopyTwo(unsigned short addr, HMI_PIC_COPY *para, HMI_PIC_COPY *sour)
{
	unsigned char TXBuf[28] = {0};	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 21;									//���ݳ��ȣ�ָ����ݺ�У��
	TXBuf[3] = WRITE_VAR_CMD;						//0x82
	TXBuf[4] = (unsigned char)(addr >> 8);			//��λ
	TXBuf[5] = (unsigned char)(addr&0xFF);			//��λ
	TXBuf[6] = 0x00;
	TXBuf[7] = 0x06;
	TXBuf[8] = 0x00;
	TXBuf[9] = 0x01;
	TXBuf[10] = (unsigned char)(sour->PageID >> 8);	//����ͼƬ����ҳ��ID ���ֽ�
	TXBuf[11] = (unsigned char)(sour->PageID&0xFF);	//����ͼƬ����ҳ��ID ���ֽ�
	TXBuf[12] = (unsigned char)(sour->Start_X >> 8);	//��ʼX���� ���ֽ�
	TXBuf[13] = (unsigned char)(sour->Start_X&0xFF);	//��ʼX���� ���ֽ�
	TXBuf[14] = (unsigned char)(sour->Start_Y >> 8);	//��ʼY���� ���ֽ�
	TXBuf[15] = (unsigned char)(sour->Start_Y&0xFF);	//��ʼY���� ���ֽ�
	TXBuf[16] = (unsigned char)(sour->End_X >> 8);	//����X���� ���ֽ�
	TXBuf[17] = (unsigned char)(sour->End_X&0xFF);	//����X���� ���ֽ�
	TXBuf[18] = (unsigned char)(sour->End_Y >> 8);	//����Y���� ���ֽ�
	TXBuf[19] = (unsigned char)(sour->End_Y&0xFF);	//����Y���� ���ֽ�
	//Ŀ��
	TXBuf[20] = (unsigned char)(para->Start_X >> 8);	//��ʼX���� ���ֽ�
	TXBuf[21] = (unsigned char)(para->Start_X&0xFF);	//��ʼX���� ���ֽ�
	TXBuf[22] = (unsigned char)(para->Start_Y >> 8);	//��ʼY���� ���ֽ�
	TXBuf[23] = (unsigned char)(para->Start_Y&0xFF);	//��ʼY���� ���ֽ�
	
	HMI_SendData(TXBuf, TXBuf[2]+3);	
}

//ģ�����ֺ���
//ͨ����ȡ������ϵͳ�汾
//TX:5A A5 03 81 00 01
//RX:5A A5 03 81 00 01 64
u8 HIM_HandShake(void)
{
    unsigned short BT_Value = 0;
    u8 cnt=0;
    while(1)
    {
        HMI_ReadVarCmd(0x000F,1); 
        OSTimeDly(200);
        GetButtonData(&BT_Value);
        if(BT_Value == 0x000F)
            return 1;       
        else
            cnt++;
        if(cnt>5)return 0;
        
    }
}
/*
����T5�� 
��ʾʱ�� 2050 �� 10 �� 1 �� 11 ʱ 12 �� 13 ��
5AA5 0B 82 009C5AA532 0A01 0B 0C 0D
���壺0x5AA5 ֡ͷ��0x0B ���ݳ��ȣ�0x82 дָ�
0x009C��������ַ���õ�ַ�̶��������Զ������ϵͳ�����ӿڱ� 0x9C ��ַ���壻
0x5AA5������һ�� RTC ���ã���ϸ�ɼ�ϵͳ�����ӿڱ� 0x9C ��ַ���壻
0x32 �꣬0x0A �£�0x01 �գ�0x0B ʱ��0x0C �֣�0x0D �롣
*/
u8 Set_T5HIM_Time(u8 year,u8 mon,u8 date,u8 hours,u8 min,u8 sec)
{
    unsigned char TXBuf[28] = {0};	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 0x0B;
	TXBuf[3] = 0x82;
	TXBuf[4] = 0x00;
	TXBuf[5] = 0x9C;
    TXBuf[6] = 0x5A;
	TXBuf[7] = 0xA5;
	TXBuf[8] = year;
	TXBuf[9] = mon;
	TXBuf[10] = date;
	TXBuf[11] = hours;
	TXBuf[12] = min;
	TXBuf[13] = sec;
    HMI_SendData(TXBuf, 14);
}


u8 Set_HIM_Date(u8 *date)
{
    u8 i=0;
    unsigned char TXBuf[28] = {0};	
	TXBuf[0] = HMI_HEADER_H;
	TXBuf[1] = HMI_HEADER_L;
	TXBuf[2] = 0x0A;
	TXBuf[3] = WRITE_REG_CMD;
	TXBuf[4] = 0x1F;
	TXBuf[5] = 0x5A;
    for(i=0;i<7;i++)
    {
        TXBuf[6+i] = ((date[i]/10)<<4)+date[i]%10;
    }
    HMI_SendData(TXBuf, 13);
    return 0;
}

//void HMI_ChangeSelectStatus(unsigned short controlID,unsigned char mode)
//{
//  unsigned char index;
//  HMI_PIC_COPY tmp; 
//  
//  index = (controlID - 0x021C) / 0x20;
//  if(mode==0)//ѡ��״̬
//  {
//    tmp.PageID = BasicGrap[index].pageID + 1;
//  }
//  else//δѡ��״̬
//  {
//    tmp.PageID = BasicGrap[index].pageID;
//  }
//  tmp.Start_X = BasicGrap[index].position_X;
//  tmp.Start_Y = BasicGrap[index].position_Y;
//  tmp.End_X = BasicGrap[index].position_X + BasicGrap[index].width;
//  tmp.End_Y = BasicGrap[index].position_Y + BasicGrap[index].height;

//  HMI_PictureCopy(controlID,&tmp);
//}


//void HMI_UpdateProgressBar(unsigned short controlID,unsigned short data)
//{
//  unsigned char index;
//  unsigned short remap;
//  HMI_PIC_COPY tmp;
//  
//  if(data==0)
//  {
//    return;
//  }
//  index = (controlID - 0x021C) / 0x20;

//  tmp.PageID = BasicGrap[index].pageID + 1;

//  tmp.Start_X = BasicGrap[index].position_X;
//  tmp.Start_Y = BasicGrap[index].position_Y;
//  tmp.End_X = BasicGrap[index].position_X + (unsigned short)remap;
//  tmp.End_Y = BasicGrap[index].position_Y + BasicGrap[index].height;
//  HMI_PictureCopy(controlID,&tmp);
//}

//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------


