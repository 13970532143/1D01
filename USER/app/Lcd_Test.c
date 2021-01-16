/*
* ��Ȩ����(C): ���Ļ� ���ڿ�ҽ�ʿƼ���չ���޹�˾ 2020.6
* �ĵ�˵����������������Ӧ�������ڴ������ϵĲ���
*
*/

//LCD UI test

#include "test.h"
volatile SYStem_Variables sys_var;
u32 num_value[2];  //���볤��
u8 input_sta = 0;    //����״̬ 0��ֹ
char versions_B[14]= {"1D01-B-V1.0"};	//�汾
char versions_A[14]={"1D01-A-V1.0"};
u8 New_language=0;
u8 Ready=0,Stadby=0;
u16 Back_Light = 100;
void Screen_Welcome(unsigned short bt_value);   //��������
void Screen_HOME(unsigned short bt_value);      //ģʽѡ�����
void Screen_O3Bag(unsigned short bt_value);     //�����״�����
void Screen_IFBottle(unsigned short bt_value);  //���ƿ����
void Screen_IFBAG(unsigned short bt_value);     //��Һ������
void Screen_O3Hydrate(unsigned short bt_value); //����ˮ����
void Screen_SuctionCup(unsigned short bt_value);//��ѹ�ֱ�
void Screen_Ration(unsigned short bt_value);    //������������
void Screen_Injector(unsigned short bt_value);  //ע��������
void Screen_Admi(unsigned short bt_value);      //����Ա����
void Screen_Setting(unsigned short bt_value);   //ϵͳ���ý���
void Screen_Language(unsigned short bt_value);  //���Խ���
void Screen_ProSet(unsigned short bt_value);    //Ũ�Ȳ������ý���
void Screen_DevInf(unsigned short bt_value);    //�豸��Ϣ����
void Screen_Test(unsigned short bt_value);      //���Խ���
void Screen_Error(unsigned short bt_value);      //���Խ��� 

//�洢���
void ERP_Check(void)
{
    EEPROM_ReadSeq(ERPIP_Language,(INT8U*)&sys_var.Language,sizeof(sys_var.Language));
    delay_ms(50);
    if(sys_var.Language>7)      //û����ȷ��������
    {             
        sys_var.Language = Engliah;
        EEPROM_WriteSeq(ERPIP_Language,(INT8U*)&sys_var.Language,sizeof(sys_var.Language));
        delay_ms(50);
        sys_var.BEEP_sta = 1;
        EEPROM_WriteSeq(ERPIP_BEEP,(INT8U*)&sys_var.BEEP_sta,sizeof(sys_var.BEEP_sta));       
        delay_ms(50);
        EEPROM_WriteSeq(ERRIP_Density_P,(INT8U*)Density_Adj_P,sizeof(Density_Adj_P));       
        delay_ms(50);
        
    }
    else
    {
        
        EEPROM_ReadSeq(ERPIP_BEEP,(INT8U*)&sys_var.BEEP_sta,sizeof(sys_var.BEEP_sta));
        delay_ms(50);
        EEPROM_ReadSeq(ERRIP_Density_P,(INT8U*)Density_Adj_P,sizeof(Density_Adj_P));
        delay_ms(50);
        
    }
    Map_Density(Density_Adj_P);
}





//�������������
void lcd_task(void *pdata)
{
    unsigned short BT_Value = 0;
//	u8 i = 0;
    pdata = pdata;
    delay_ms(200);


//    EEPROM_WriteSeq(ERPIP_Language,(INT8U*)&sys_var.Language,sizeof(sys_var.Language));
    ERP_Check();
Rest_LCD:
    if(HIM_HandShake()!=0)
    {
        printf("���ֳɹ�\r\n");
        sys_var.Screen = S_Welcome;
        HIM_SCR_ID(sys_var.Screen);
        delay_ms(50);
        HMI_TXIntToEdit(ED_Ver_E,5);                //��ʾ����
        HMI_PictureCopy_xy(BAS_W_E,1,16,621,16+45,621+26);     //��ʾ������
        HMI_TXStrToEdit(TXT_Ver_A,versions_A,15);      //��ʾ�汾��
        HMI_TXStrToEdit(TXT_Ver_B,versions_B,15);
    }
    else
    {
        printf("����ʧ��\r\n");
        SV17F_MP3_Specify(13);
        goto Rest_LCD;
    }
    delay_ms(50);

     Clear();    //������ࡤ
//    if(sys_var.Language!=0)
//    {
//        sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
//    }
//    else sys_var.Screen = S_HOME;
////    sys_var.Screen = S_Welcome;
//    HIM_SCR_ID(sys_var.Screen);
//    Set_T5HIM_Time(20,8,16,11,31,50);//����ʱ�䣬��ע��ȡ�������ڸ���ʱ�䣬���º���Ҫ�Ѵ���ע��
//    HIM_ADJ();
//    printf("���ֳɹ�\r\n");
    while(1)
    {
        GetButtonData(&BT_Value);
        if(sys_var.Error==0)
        {
            if(BT_Value != 0xffff)
            {
                if(sys_var.Screen == S_Welcome)
                {
                    Screen_Welcome(BT_Value);
                }
                if(sys_var.Screen == S_Language)
                {
                    Screen_Language(BT_Value);
                }
                switch(sys_var.Screen)
                {
                    case S_HOME:
                    case S_HOME+76:
                    case S_HOME+78:
                    case S_HOME+80:
                    case S_HOME+82:
                    case S_HOME+84:
                        Screen_HOME(BT_Value);
                        break;
                    case S_O3Bag:
                        Screen_O3Bag( BT_Value);
                        break;
                    case S_IFBottle:
                        Screen_IFBottle(BT_Value);
                        break;
                    case S_IFBAG:
                        Screen_IFBAG(BT_Value);
                        break;
                    case S_O3Hydrate:
                        Screen_O3Hydrate( BT_Value);
                        break;
                    case S_SuctionCup:
                        Screen_SuctionCup(BT_Value);
                        break;
                    case S_Ration:
                        Screen_Ration(BT_Value);
                        break;
                    case S_Injector:
                        Screen_Injector( BT_Value);
                        break;
                    case S_Setting:
                    case S_Setting+8:
                    case S_Setting+16:
                    case S_Setting+24:
                    case S_Setting+32:
                    case S_Setting+40:
                        
                        Screen_Setting(BT_Value);
                        break;
                    case S_Administrator:
                    case S_Administrator+8:
                    case S_Administrator+16:
                    case S_Administrator+24:
                    case S_Administrator+32:
                    case S_Administrator+40:
                        Screen_Admi(BT_Value);
                        break;
                    case S_ProSet:
                    case S_ProSet+8:
                    case S_ProSet+16:
                    case S_ProSet+24:
                    case S_ProSet+32:
                    case S_ProSet+40:
                        Screen_ProSet( BT_Value);
                        break;
                    case S_Information:
                    case S_Information+8:
                    case S_Information+16:
                    case S_Information+24:
                    case S_Information+32:
                    case S_Information+40:
                        Screen_DevInf( BT_Value);
                        break;
                    case S_Test:
                        Screen_Test( BT_Value);
                        break;
                    case S_ERROR:
                        Screen_Error( BT_Value);
                        break;
                }
//                printf("����=%d\r\n",sys_var.Screen);
            }

            
        }
        delay_ms(50);
    }

}

//��������
void Screen_Welcome(unsigned short bt_value)
{
    static u8 cnt=0;
    bt_value = bt_value;
    if(bt_value==BT_W_WEL)
    {
        if(sys_var.Language!=0)
        {
            sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
        }
        else sys_var.Screen = S_HOME;
        HIM_SCR_ID(sys_var.Screen);
    }
//    else if(bt_value==BT_W_TEST)        //���԰�ť
//    {
//        cnt++;
//        if(cnt>=5)
//        {
//            cnt = 0;
//            
//        }
//    }
}



//�˵�����/ģʽѡ�����
void Screen_HOME(unsigned short bt_value)
{
    bt_value = bt_value;
    Ready = 0;
    switch(bt_value)
    {
    case BT_M_O3Bag://�����״�
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //����״̬ 0��ֹ
        sys_var.Density = 0;
        sys_var.work_mode = O3Bag;
        dis_density(sys_var.work_mode,sys_var.Density);

        sys_var.Screen = S_O3Bag ;                                            
        HMI_PictureCopy_S_T_xy(BAS_OB_TM,70,0,0+100*sys_var.Language,450-1,100+100*sys_var.Language-1,316,24);
        Dis_CV_BAS(BAS_OB_C,0,77,91,414);
        Dis_CV_BAS(BAS_OB_V,0,78,95,522);
        HMI_TXIconVal(VAR_SR,sys_var.Language);
        HMI_PictureCopy_xy(BAS_OB_Cnum,sys_var.Screen,94,213,94+382,312+158);  //������ʾ��
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_InfusionBottle://��Һƿ
//            LED1 = !LED1;
        sys_var.Density = 0;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //����״̬ 0��ֹ
        sys_var.work_mode = infusionBottle;
        dis_density(sys_var.work_mode,sys_var.Density);     //��ʾ����Ũ��



//        dis_vac_bar(100);
        sys_var.Screen = S_IFBottle;
//        HMI_PictureCopy_S_T_xy(BAS_BT_Work,70,0,0+100*sys_var.Language,450-1,100+100*sys_var.Language-1,599,556);
        HMI_PictureCopy_S_T_xy(BAS_BT_TM,71,0,0+100*sys_var.Language,500-2,100+100*sys_var.Language-2,266,29);
        Dis_CV_BAS(BAS_BT_C,0,77,95,374);
        Dis_CV_BAS(BAS_BT_V,0,78,97,474);
        HMI_PictureCopy_xy(BAS_BT_Cnum,sys_var.Screen,89,204,89+384,204+155);  //������ʾ��
        HMI_TXIconVal(VAR_SR,sys_var.Language);
        HMI_PictureCopy_xy(BAS_BT_Vbar,sys_var.Screen+1,99,588,120+320*3/5,588+35);  //ѹ����
        
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_InfusionBag://��Һ��
//            LED1 = !LED1;
        sys_var.Density = 0;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //����״̬ 0��ֹ
        sys_var.work_mode = infusionBag;
        dis_density(sys_var.work_mode,sys_var.Density);
        sys_var.O3bulk = 0;
        sys_var.Dosage = 0;
        HMI_ShowNumber(TXT_BG_V,sys_var.O3bulk,0,8);
        HMI_ShowNumber(TXT_BG_Dosage,sys_var.Dosage,0,8);
        sys_var.Screen = S_IFBAG ;
        Dis_SP_BAS(BAS_BG_Work,0,598,553);
        HMI_PictureCopy_S_T_xy(BAS_BG_TM,72,0,0+100*sys_var.Language,450-7,100+100*sys_var.Language-7,266,30);    //ģʽ       
        HMI_PictureCopy_S_T_xy(BAS_BG_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,103,190);    //Ũ���ַ�
        HMI_PictureCopy_S_T_xy(BAS_BG_TV,80,501,0+50*sys_var.Language,501+125,50+50*sys_var.Language,46,509);    //Ũ���ַ�
        HMI_PictureCopy_S_T_xy(BAS_BG_TQ,80,689,0+50*sys_var.Language,689+125,50+50*sys_var.Language,47,572);    //Ũ���ַ�
        
//        HMI_PictureCopy_S_T_xy(BAS_BG_TC,80,0,0+100*5,450-1,100+100*5-2,103,190);    //ģʽ
        HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen,95,313,95+381,313+154);
        HMI_PictureCopy_xy(BAS_BG_V,sys_var.Screen,179,507,179+252,507+57); //���
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_BG_Work,sys_var.Screen,599,556,599+362,556+88);  //������ͣ�ؼ�
        
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_O3Hydrate://����ˮ��
//            LED1 = !LED1;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //����״̬ 0��ֹ
        sys_var.Density = 0;
        sys_var.H2O_countdowm = 0;
        sys_var.work_mode = O3Hydrate;

        dis_density(sys_var.work_mode,sys_var.Density);
        sys_var.H2O_countdowm = 0;  //����ʱ��ģʽ����Ϊ0


        sys_var.Countdown = 600;
        dis_countdown(sys_var.Countdown);       //��ʾ����ʱ
        sys_var.Screen = S_O3Hydrate ;
        HMI_PictureCopy_S_T_xy(BAS_H_TM,73,0,0+100*sys_var.Language,450-2,100+100*sys_var.Language-2,267,29);    //ģʽ       
        HMI_PictureCopy_S_T_xy(BAS_H_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,104,187);    //Ũ���ַ�
        
        HMI_PictureCopy_xy(BAS_H_Cnum,sys_var.Screen,97,349,97+375,349+223);
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_H_Work,sys_var.Screen,597,552,597+361,552+90);  //������ͣ�ؼ�
        Dis_SP_BAS(BAS_H_Work,0,598,553);
        HIM_SCR_ID(S_O3Hydrate);
        break;
    case BT_M_SuctionCup://��ѹ�ֱ�
//            LED1 = !LED1;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //����״̬ 0��ֹ
        sys_var.Density = 0;
        sys_var.work_mode = suctionCup;

        dis_density(sys_var.work_mode,sys_var.Density);//��ʾ����Ũ��
        sys_var.Set_vac = 0;
//        HMI_TXIconVal(AMT_SC_Work,0);       //��ʾ����״̬
        sys_var.Screen = S_SuctionCup ;
        HMI_PictureCopy_S_T_xy(BAS_SC_TM,74,0,2+100*sys_var.Language,500-2,102+100*sys_var.Language-2,266,29);    //ģʽ       
        HMI_PictureCopy_S_T_xy(BAS_SC_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,103,168);    //Ũ���ַ�
        HMI_PictureCopy_S_T_xy(BAS_SC_TV,81,34,30+60*sys_var.Language,34+358,30+56+60*sys_var.Language,104,461);    //Ũ���ַ�
        
        HMI_PictureCopy_xy(BAS_SC_Cnum,sys_var.Screen,98,283,98+373,283+148);  //������ʾ��    
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_SC_Work,sys_var.Screen,598,553,598+361,553+90);  //������ͣ�ؼ�
        Dis_SP_BAS(BAS_SC_Work,0,598,553);
        HMI_PictureCopy_xy(BAS_SC_Vbar,S_SuctionCup+1,94,535,94+350,535+35);
        HIM_SCR_ID(S_SuctionCup);         //�л�����
        break;
    case BT_M_Ration://��������
//            LED1 = !LED1;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //����״̬ 0��ֹ
        sys_var.Density = 0;
        sys_var.work_mode = ration;

//        HMI_TXIconVal(VAR_RT_TM,sys_var.Language);  //��ʾ���������ַ�
//        HMI_TXIconVal(VAR_RT_TC,sys_var.Language);  //��ʾŨ���ַ�
//        HMI_TXIconVal(VAR_RT_TV,sys_var.Language);  //��ʾ����ַ�

        dis_density(sys_var.work_mode,sys_var.Density);//��ʾ����Ũ��
        sys_var.O3bulk = 0; //���
        HMI_ShowNumber(TXT_RT_V,sys_var.O3bulk,0,8);    //��ʾ�������
//        HMI_TXIconVal(AMT_RT_Work,0);       //��ʾ����״̬
        sys_var.Screen = S_Ration;
        
    
        HMI_PictureCopy_S_T_xy(BAS_RT_TM,75,0,0+100*sys_var.Language,500-2,100+100*sys_var.Language-2,266,29);    //ģʽ       
        HMI_PictureCopy_S_T_xy(BAS_RT_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,103,168);    //Ũ���ַ�
        HMI_PictureCopy_S_T_xy(BAS_RT_TV,80,501,0+50*sys_var.Language,501+125,50+50*sys_var.Language,48,472);    //Ũ���ַ�
       
        HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen,0,0,0,0);  //������ʾ��
        HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen,181,475,181+248,475+44);  //����ʾ��
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_RT_Work,sys_var.Screen,599,558,599+362,558+84);  //������ͣ�ؼ�
        Dis_SP_BAS(BAS_RT_Work,0,598,553);    
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_Injector://ע����ģʽ
//          LED1 = !LED1;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //����״̬ 0��ֹ
        sys_var.Density = 0;
        sys_var.work_mode = injector;

//        HMI_TXIconVal(VAR_IJ_TM,sys_var.Language);  //��ʾע�������ַ�
//        HMI_TXIconVal(VAR_IJ_TC,sys_var.Language);  //��ʾŨ���ַ�

        dis_density(sys_var.work_mode,sys_var.Density); //��ʾ����Ũ��
//        HMI_TXIconVal(AMT_RT_Work,0);       //��ʾ����״̬
        sys_var.Screen = S_Injector;
        HMI_PictureCopy_S_T_xy(BAS_IJ_TM,76,0,0+100*sys_var.Language,450-2,100+100*sys_var.Language-2,266,29);    //ģʽ       
        HMI_PictureCopy_S_T_xy(BAS_IJ_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,104,199);    //Ũ���ַ�
           
        HMI_PictureCopy_xy(BAS_IJ_Cnum,sys_var.Screen,98,352,98+376,352+217);  //������ʾ��
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_IJ_Work,sys_var.Screen,600,558,600+359,558+86);  //������ͣ�ؼ�
        Dis_SP_BAS(BAS_IJ_Work,0,598,553);    
        
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_Settings:
        HMI_PictureCopy_xy(BAS_ST_Voice,S_Setting,860,549,860+92,549+50);      //����״̬        
        
        HMI_BackLightCtrl(Back_Light);
        HMI_TXIconVal(BT_ST_Light,Back_Light);       //������ʾ
//            HMI_BackLightCtrl(50);
        sys_var.Screen = S_Setting+8*sys_var.Language;
        HIM_SCR_ID(sys_var.Screen);    //�л�ϵͳ���ý���
        break;

    default:
        break;
    }

}

/* �����״�����
*   1. �����գ�����գ���ѹ<50Kpa��ֹͣ�����
*   2. ����Ũ��(1-80,>80ʱ������)
*   3. ���Ũ�ȣ��Ƴ���
*/
void Screen_O3Bag(unsigned short bt_value)
{

    bt_value = bt_value;
    if(sys_var.work_sta==0 &&sys_var.Vac_Open==0)    //����δ����
    {
        switch(bt_value)
        {

        case BT_OB_0:
        case BT_OB_1:
        case BT_OB_2:
        case BT_OB_3:
        case BT_OB_4:
        case BT_OB_5:
        case BT_OB_6:
        case BT_OB_7:
        case BT_OB_8:
        case BT_OB_9:
            if(input_sta==1)
            {
                if((num_value[0]*10 + bt_value-BT_OB_0)<100)
                {
                    num_value[0] = num_value[0]*10 + bt_value-BT_OB_0;
                }
                else
                {
                     num_value[0] = ( num_value[0]%10)*10 + bt_value-BT_OB_0;   
                }
                dis_density(sys_var.work_mode,num_value[0]);
            }
            break;
        case BT_OB_Back:        //��λ
            if(input_sta==1)
            {
                if(num_value[0] > 0)
                {
                    num_value[0] = num_value[0]/10;
                    dis_density(sys_var.work_mode,num_value[0]);
                }
            }
            
            break;
        case BT_OB_Enter:            
//            if(Ready==1)
//            {
//                Ready = 0;
//                HMI_TXIconVal(VAR_SR,sys_var.Language);
//            }
            
            if(num_value[0]!=0)
            {
                if(num_value[0]>80)
                {
                    num_value[0] = 0;
                    dis_density(sys_var.work_mode,num_value[0]);
                }
                else
                {
                    
                    Ready = !Ready;
                    HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                    if(input_sta==1)
                    {
                        sys_var.Density = num_value[0];
                        HMI_PictureCopy_xy(BAS_OB_Cnum,sys_var.Screen,94,213,94+382,312+158);  //������ʾ��
    //                        HMI_PictureCopy_xy(BAS_OB_Cnum,S_O3Bag,33,199,33+281,199+196);  //������ʾ��
                        input_sta  = 2; //����ȷ�����������룬�����ٴε��Ũ�������
                        
                    }
                }
            }
            break;

        case BT_NUM_ET:     //Ũ����ʾ��ť
            if(Ready==0)
            {
                input_sta = 1;
    //            num_value[0] = 0;
                dis_density(sys_var.work_mode,num_value[0]);
                HMI_PictureCopy_xy(BAS_OB_Cnum,sys_var.Screen+1,94,213,94+382,312+158);  //������ʾ��
//            HMI_PictureCopy_xy(BAS_OB_Cnum,S_O3Bag+1,33,199,33+281,199+196);
            }
            
            break;
        case BT_OB_Home:
            sys_var.work_sta = 0;
            sys_var.Vac_Open = 0;
            sys_var.Density  = 0;
            if(sys_var.Language!=0)
            {
                sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
            }
            else sys_var.Screen = S_HOME;
            sys_var.work_mode = 0;
            HIM_SCR_ID(sys_var.Screen);
            HMI_PictureCopy_xy(BAS_OB_Cnum,sys_var.Screen,94,213,94+382,312+158);  //������ʾ��
            break;
        }
    }
    if(Ready==1)
    {
        if(bt_value==  BT_OB_Concentration)   //����
        {
            if(sys_var.Vac_Open == 0)  //����ս�����δ����
            {

                if(input_sta == 2)  //�������--����Enter�ؼ�
                {
                    if(sys_var.Adc_value[vacuum_v]<130)       //�״��������ѹ����130ʱ���ܿ����Ƴ���
                    {
                        sys_var.work_sta = !sys_var.work_sta;
                        if(sys_var.work_sta==1)
                        {
                            Dis_CV_BAS(BAS_OB_C,1,77,91,414);
                            sys_var.Job_step = 3;
                        }
                        else //�س���
                        {
                            Dis_CV_BAS(BAS_OB_C,0,77,91,414);

                            PWM3_OUT(VacCtr_OFF);       //��
                            Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                            Valve5 = Valve6 = ON;
                            TIM_Cmd(TIM4, DISABLE);  //�س���
                            PWM2_OUT(0);
                        }
                    }
                    else
                    {
                        if(sys_var.work_sta==1)  sys_var.work_sta = 0;
                        Dis_CV_BAS(BAS_OB_C,0,77,91,414);           //Ũ��״̬
                        PWM3_OUT(VacCtr_OFF);       //��
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                        Valve5 = Valve6 = ON;
                        TIM_Cmd(TIM4, DISABLE);  //�س���
                        PWM2_OUT(0);      //PWM ռ�ձȵ�Ϊ0
                    }
                }
            }
        }
        if(bt_value==  BT_OB_Vacuo)
        {

            if(sys_var.work_sta == 0)  //����δ����
            {
                if(sys_var.Adc_value[vacuum_v]>85)       //��ǰѹ������85Kpa
                {
                    sys_var.Vac_Open = !sys_var.Vac_Open;       //�л��鸺ѹ����״̬
                    if(sys_var.Vac_Open!=0)     //�����鸺ѹ
                    {
                        Dis_CV_BAS(BAS_OB_V,1,78,95,522);       //��ѹ�ؼ�����
                        sys_var.Job_step = 1;

                    }
                    else
                    {
                        Dis_CV_BAS(BAS_OB_V,0,78,95,522);       //��ѹ�ؼ�����
                        PWM3_OUT(VacCtr_OFF);       //��
                        Valve6 = ON;       //�л���ͨ״̬��ά���״��ڲ���ѹ

                    }
                }
                else
                {
                    if(sys_var.Vac_Open==1)sys_var.Vac_Open = 0;
                    Dis_CV_BAS(BAS_OB_V,0,78,95,522);   //��ѹ�ؼ�����
                    PWM3_OUT(VacCtr_OFF);       //��
                    Valve6 = ON;       //�л���ͨ״̬��ά���״��ڲ���ѹ
                }
            }
        }
    }
}
//��Һƿ
void Screen_IFBottle(unsigned short bt_value)
{
    bt_value = bt_value;
    if(sys_var.work_sta==0&&sys_var.Vac_Open!=1)    //�������ڴ���״̬
    {
        switch(bt_value)
        {
        case BT_BT_0:
        case BT_BT_1:
        case BT_BT_2:
        case BT_BT_3:
        case BT_BT_4:
        case BT_BT_5:
        case BT_BT_6:
        case BT_BT_7:
        case BT_BT_8:
        case BT_BT_9:
            if(input_sta==1)
            {
                if((num_value[0]*10 + bt_value-BT_BT_0)<100)
                {
                    num_value[0] = num_value[0]*10 + bt_value-BT_BT_0;

                }
                else
                {
                     num_value[0] = ( num_value[0]%10)*10 + bt_value-BT_BT_0;   
                }
                dis_density(sys_var.work_mode,num_value[0]);
            }
            break;
        case BT_BT_Back:
            if(input_sta==1)
            {
                if(num_value[0] > 0)
                {
                    num_value[0] = num_value[0]/10;
                    dis_density(sys_var.work_mode,num_value[0]);
                }
            }
            break;
        case BT_BT_Enter:
            
            if(num_value[0]!=0)
            {
                if(num_value[0]>80)
                {
                    num_value[0] = 0;  //�޶�Ũ�ȴ�СΪ80
                    dis_density(sys_var.work_mode,num_value[0]);//��ʾŨ��

                }
                else
                {
                    Ready = !Ready;
                    HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                    if(input_sta==1)
                    {
                        sys_var.Density = num_value[0];
                        Ready = 1;
//                        HMI_TXIconVal(VAR_SR,sys_var.Language+6);
//                        sys_var.Vac_Open = 0;
//                        sys_var.work_sta = 0;
                        input_sta  = 2; //�������
//                        HMI_PictureCopy_xy(BAS_BT_Cnum,S_IFBottle,42,188,42+252,188+173);
                        HMI_PictureCopy_xy(BAS_BT_Cnum,sys_var.Screen,89,204,89+384,204+155);  //������ʾ��
                    }
                }
            }
            break;
        case BT_NUM_ET:     //Ũ����ʾ��ť
            if(Ready==0)
            {
                input_sta = 1;
    //            num_value[0] = 0;
    //            HMI_PictureCopy_xy(BAS_BT_Cnum,S_IFBottle+1,43,188,42+252,188+173);
                HMI_PictureCopy_xy(BAS_BT_Cnum,sys_var.Screen+1,89,204,89+384,204+155);  //������ʾ��
                dis_density(sys_var.work_mode,num_value[0]);
            }
            break;
        case BT_BT_Home:
            if(sys_var.work_sta==0)  //����ս������������
            {
                sys_var.Density = 0;
                if(sys_var.Language!=0)
                {
                    sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
                }
                else sys_var.Screen = S_HOME;
                 sys_var.work_mode = 0;
//                if(sys_var.Job_step!=0) Clear();
                HIM_SCR_ID(sys_var.Screen );
//                HMI_PictureCopy_xy(BAS_BT_Cnum,S_IFBottle,43,188,42+252,188+173);
            }
            break;
        }
    }
    if(Ready==1)
    {
        if(bt_value== BT_BT_Concentration)
        {
            if(sys_var.Vac_Open!=1)  //����ս�����δ����
            {

                if(input_sta == 2)  //�������--����Enter�ؼ�
                {
                    
                    
                    if(sys_var.Adc_value[vacuum_v]<130)    //
                    {
                        sys_var.work_sta=!sys_var.work_sta;
                        if(sys_var.work_sta)
                        {
                            Dis_CV_BAS(BAS_BT_C,1,77,95,374);
    //                        HMI_PictureCopy_xy(BAS_BT_C,sys_var.Screen+1,97,388,97+378,388+80);  //Ũ�ȿؼ�
    //                        HMI_TXIconVal(VAR_BT_C,sys_var.work_sta);   //�л���������ѹָʾ
    //                        HMI_TXIconVal(VAR_BT_TC,2*sys_var.Language+sys_var.work_sta);   //Ũ���ַ�״̬
                            sys_var.Job_step=3;  
                        } 
                        else
                        {
                            Dis_CV_BAS(BAS_BT_C,0,77,95,374);
    //                        HMI_PictureCopy_xy(BAS_BT_C,sys_var.Screen,97,388,97+378,388+80);  //Ũ�ȿؼ�
    //                        HMI_TXIconVal(VAR_BT_C,sys_var.work_sta);   //�л���������ѹָʾ
    //                        HMI_TXIconVal(VAR_BT_TC,2*sys_var.Language+sys_var.work_sta);   //Ũ���ַ�״̬
                            Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF ;
                            Valve5 = Valve6 = ON;
                            TIM_Cmd(TIM4, DISABLE);
                            PWM2_OUT(0);

                            RGB_Colour(GREEN);        //���̵�
                        }
                                       
                    }
                    else if(sys_var.Adc_value[vacuum_v]>130)
                    {
                        if(sys_var.work_sta==1) sys_var.work_sta = 0;
                        Dis_CV_BAS(BAS_BT_C,0,77,95,474);
    //                    HMI_PictureCopy_xy(BAS_BT_C,sys_var.Screen,97,388,97+378,388+80);  //Ũ�ȿؼ�
    //                    HMI_TXIconVal(VAR_BT_C,sys_var.work_sta);   //�л���������ѹָʾ
    //                    HMI_TXIconVal(VAR_BT_TC,2*sys_var.Language+sys_var.work_sta);   //Ũ���ַ�״̬
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF ;
                        Valve5 = Valve6 = ON;
                        TIM_Cmd(TIM4, DISABLE);
                        PWM2_OUT(0);

    //                    RGB_Colour(GREEN);        //���̵�
                    }   

                }
            }
        }
        if(bt_value== BT_BT_Vacuo)      //���
        {
            if(sys_var.work_sta!=1)  //����ս�����δ����
            {
                if(sys_var.Adc_value[vacuum_v]>45)        //
                {
                    sys_var.Vac_Open = ! sys_var.Vac_Open;
                    if(sys_var.Vac_Open)
                    {
                        Dis_CV_BAS(BAS_BT_V,1,78,95,474);
    //                    HMI_PictureCopy_xy(BAS_BT_V,sys_var.Screen+1,96,483,96+378,483+80);  //��ѹ�ؼ�
    //                    HMI_TXIconVal(VAR_BT_V,sys_var.Vac_Open);   //�л���������ѹָʾ
    //                    HMI_TXIconVal(VAR_BT_TV,2*sys_var.Language+sys_var.Vac_Open);   //ѹ���ַ�״̬
                        sys_var.Job_step=1;       //ֹͣ���
                    }
                    else
                    {
                        Dis_CV_BAS(BAS_BT_V,0,78,95,474);
    //                    HMI_PictureCopy_xy(BAS_BT_V,sys_var.Screen,96,483,96+378,483+80);  //��ѹ�ؼ�
    //                    HMI_TXIconVal(VAR_BT_V,sys_var.Vac_Open);   //�л���������ѹָʾ
    //                    HMI_TXIconVal(VAR_BT_TV,2*sys_var.Language+sys_var.Vac_Open);   //ѹ���ַ�״̬
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                        Valve5 = Valve6 = ON ;
                        PWM3_OUT(VacCtr_OFF);       //��
                //                sys_var.Job_step=0;       //ֹͣ���
                    }


                }
                else
                {
                    if(sys_var.Vac_Open==1)sys_var.Vac_Open=0;
                    Dis_CV_BAS(BAS_BT_V,0,78,95,474);
    //                HMI_PictureCopy_xy(BAS_BT_V,sys_var.Screen,96,483,96+378,483+80);  //��ѹ�ؼ�
    //                 HMI_TXIconVal(VAR_BT_V,sys_var.Vac_Open);   //�л���������ѹָʾ
    //                HMI_TXIconVal(VAR_BT_TV,2*sys_var.Language+sys_var.Vac_Open);   //ѹ���ַ�״̬
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                    Valve5 = Valve6 = ON ;
                    PWM3_OUT(VacCtr_OFF);       //��
                }
            }
        }
    }
}
//��Һ��
void Screen_IFBAG(unsigned short bt_value)
{
    static u8 V_sta=0;    //�������״̬
    bt_value = bt_value;
    if(bt_value==BT_BG_Work)
    {
        if(input_sta==2)    //����������������
        {
            if(sys_var.Dosage!=0&&Ready!=0)       //������Ϊ0
            {
                sys_var.work_sta = !sys_var.work_sta;
                Dis_SP_BAS(BAS_BG_Work,sys_var.work_sta,598,553);
//                HMI_PictureCopy_xy(BAS_BG_Work,sys_var.Screen+sys_var.work_sta,599,556,599+362,556+88);  //������ͣ�ؼ�
//                HMI_TXIconVal(VAR_BG_C,sys_var.work_sta);   //�л���������ѹָʾ
//                HMI_TXIconVal(AMT_BG_Work,sys_var.work_sta);
                if(sys_var.work_sta==1)
                {
                    sys_var.Job_step = 1;
                }

            }
        }

    }

    if(sys_var.work_sta==0)    //δ��������
    {
        switch(bt_value)
        {
        case BT_BG_0:
        case BT_BG_1:
        case BT_BG_2:
        case BT_BG_3:
        case BT_BG_4:
        case BT_BG_5:
        case BT_BG_6:
        case BT_BG_7:
        case BT_BG_8:
        case BT_BG_9:
            if(input_sta==1)
            {
                if(V_sta==0)    //�������ֵ��Ũ��
                {
                    if((num_value[0]*10 + bt_value-BT_BG_0)<100)
                    {
                        num_value[0] = num_value[0]*10 + bt_value-BT_BG_0;
                    }
                    else
                    {
                        num_value[0] = ( num_value[0] % 10)*10 + bt_value-BT_BG_0;                    
                    }
                    dis_density(sys_var.work_mode,num_value[0]);
                }
                if(V_sta==1)        //�������ֵ�����123
                {
                    if((num_value[V_sta]*10 + bt_value-BT_BG_0)<1000)   //���С��1000
                    {
                        num_value[V_sta] = num_value[V_sta]*10 + bt_value-BT_BG_0;
                    }
                    else
                    {
                        num_value[V_sta] = (num_value[V_sta]-(num_value[V_sta]/100)*100)*10 +bt_value-BT_BG_0;                       
                    }
                    HMI_ShowNumber(TXT_BG_V,num_value[V_sta],0,8);
                }
            }
            break;
        case BT_BG_Back:
            if(input_sta==1)
            {
                if(V_sta==0)    //�������ֵ��Ũ��
                {
                    if(num_value[0] > 0)
                    {
                        num_value[0] = num_value[0]/10;
                        dis_density(sys_var.work_mode,num_value[0]);
                    }
                }
                else
                {
                    if(num_value[1] > 0)
                    {
                        num_value[1] = num_value[1]/10;
                        HMI_ShowNumber(TXT_BG_V,num_value[1],0,8);
                    }
                }
            }
            break;
        case BT_BG_Enter:
            
            if(num_value[0]!=0)
            {
                if((num_value[0]<= 80) && (num_value[1]<=400))
                {
                    
                    Ready = !Ready;
                    HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                
                    if(input_sta==1)
                    {
                        input_sta = 2;
                        HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen,95,313,95+381,313+154);
                        HMI_PictureCopy_xy(BAS_BG_V,sys_var.Screen,179,507,179+252,507+57); //���
//                        HMI_PictureCopy_xy(BAS_BG_Cnum,S_IFBAG,42,188,42+252,188+173);
//                        HMI_PictureCopy_xy(BAS_BG_V,S_IFBAG,162,387,162+158,387+52);
                        sys_var.Density = num_value[0];
                        sys_var.O3bulk = num_value[1];
                        sys_var.Dosage = sys_var.Density*sys_var.O3bulk ;
                        HMI_ShowNumber(TXT_BG_Dosage,sys_var.Dosage,0,8);
                    }
                }
                if(num_value[0]>80)
                {
                    num_value[0] = 0;  //�޶�Ũ�ȴ�СΪ80
                    dis_density(sys_var.work_mode,num_value[0]);//��ʾŨ��
                }
                if(num_value[1]>400)   //�����0~400ml
                {
                    num_value[1]=0;
                    HMI_ShowNumber(TXT_BG_V,num_value[1],0,8);
                }

                

            }
//            if(input_sta==2)
//            {
//                input_sta = 1;
//                HMI_TXIconVal(VAR_SR,sys_var.Language);
//            }
            break;


        case BT_NUM_ET:     //Ũ����ʾ��ť
            if(Ready == 0)
            {
                V_sta = 0;
                input_sta = 1;
                HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen+1,95,313,95+381,313+154);
                            
    //            HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen+1,42,188,42+252,188+173);
                HMI_PictureCopy_xy(BAS_BG_V,sys_var.Screen,179,507,179+252,507+57); //���
    //            HMI_PictureCopy_xy(BAS_BG_Cnum,S_IFBAG+1,42,188,42+252,188+173);
    //            HMI_PictureCopy_xy(BAS_BG_V,S_IFBAG,162,387,162+158,387+52);        
    //            num_value[0] = 0;
                dis_density(sys_var.work_mode,num_value[0]);
            }
            
            break;
        case BT_BG_Vacuo:       //�����ť
            if(Ready == 0)
            {
                V_sta = 1;
                input_sta = 1;
                HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen,95,313,95+381,313+154);
    //            HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen,42,188,42+252,188+173);
                HMI_PictureCopy_xy(BAS_BG_V,sys_var.Screen+1,179,507,179+252,507+57); //���
    //            HMI_PictureCopy_xy(BAS_BG_Cnum,S_IFBAG,42,188,42+252,188+173);
    //            HMI_PictureCopy_xy(BAS_BG_V,S_IFBAG+1,162,387,162+158,387+52);
    //            num_value[1] = 0;
                HMI_ShowNumber(TXT_BG_V,num_value[1],0,8);
            }
            break;
        case BT_BG_Home:
            if(sys_var.Language!=0)
            {
                sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
            }
            else sys_var.Screen = S_HOME;
            V_sta = 0;
            sys_var.work_mode = 0;//����ģʽ
//            if(sys_var.Job_step!=0) Clear();
            HIM_SCR_ID(sys_var.Screen);
//            HMI_PictureCopy_xy(BAS_BG_Cnum,S_IFBAG,42,188,42+252,188+173);
//            HMI_PictureCopy_xy(BAS_BG_V,S_IFBAG,162,387,162+158,387+52);
            break;
        }
    }

}
//����ˮ��
void Screen_O3Hydrate(unsigned short bt_value)
{

    bt_value = bt_value;
    if(bt_value==BT_H_Work)
    {
        if(input_sta==2&&Ready!=0)    //����������������
        {
            sys_var.work_sta = !sys_var.work_sta;
            if(sys_var.work_sta)
            {
               sys_var.Job_step = 1;
            }
            Dis_SP_BAS(BAS_H_Work,sys_var.work_sta,598,553);
//            HMI_PictureCopy_xy(BAS_H_Work,sys_var.Screen+sys_var.work_sta,597,552,597+361,552+90);  //������ͣ�ؼ�
//            HMI_TXIconVal(AMT_H_Work,sys_var.work_sta);
            sys_var.H2O_countdowm ++;
            if(sys_var.H2O_countdowm==3)sys_var.H2O_countdowm=1;
        }
    }
    if(sys_var.work_sta==0)    //δ��������
    {
        switch(bt_value)
        {
        case BT_H_0:
        case BT_H_1:
        case BT_H_2:
        case BT_H_3:
        case BT_H_4:
        case BT_H_5:
        case BT_H_6:
        case BT_H_7:
        case BT_H_8:
        case BT_H_9:
            if(input_sta==1)
            {
                if((num_value[0]*10 + bt_value-BT_H_0)<100)
                {
                    num_value[0] = num_value[0]*10 + bt_value-BT_H_0;
                }
                else
                {
                    num_value[0] = ( num_value[0] % 10)*10 + bt_value-BT_H_0;                    
                }
                dis_density(sys_var.work_mode,num_value[0]);
            }
            break;
        case BT_H_Back:
            if(input_sta==1)
            {
                if(num_value[0] > 0)
                {
                    num_value[0] = num_value[0]/10;
                    dis_density(sys_var.work_mode,num_value[0]);
                }
            }
            break;
        case BT_H_Enter:
            
            if(num_value[0]!=0)
            {
                if(num_value[0]>80)
                {
                    num_value[0] = 0;  //�޶�Ũ�ȴ�СΪ80
                    dis_density(sys_var.work_mode,num_value[0]);
                }
                else
                {
                    Ready = !Ready;
                    HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                    if(input_sta==1)
                    {
                        sys_var.Density = num_value[0];
                        
                        HMI_PictureCopy_xy(BAS_H_Cnum,sys_var.Screen,97,349,97+375,349+223);
//                        HMI_PictureCopy_xy(BAS_H_Cnum,S_O3Hydrate,44,211,44+286,211+236);
                        input_sta = 2;
                    }
                }
            }
            break;
        case BT_NUM_ET:     //Ũ����ʾ��ť
            if(Ready!=1)
            {
                input_sta = 1;
    //            num_value[0] = 0;
                dis_density(sys_var.work_mode,num_value[0]);
                HMI_PictureCopy_xy(BAS_H_Cnum,sys_var.Screen+1,97,349,97+375,349+223);
    //            HMI_PictureCopy_xy(BAS_H_Cnum,S_O3Hydrate+1,44,211,44+286,211+236);
            }
            break;
        case BT_H_Home:
            if(sys_var.work_sta==0)
            {
                if(sys_var.Language!=0)
                {
                    sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
                }
                else sys_var.Screen = S_HOME;
                sys_var.work_mode = 0;
                sys_var.H2O_countdowm = 0;
//                if(sys_var.Job_step!=0) Clear();
                HIM_SCR_ID(sys_var.Screen);
                HMI_PictureCopy_xy(BAS_H_Cnum,sys_var.Screen,97,349,97+375,349+223);
//                HMI_PictureCopy_xy(BAS_H_Cnum,S_O3Hydrate,44,211,44+286,211+236);
            }
            break;
        }
    }
}
//��ѹ�ֱ�
void Screen_SuctionCup(unsigned short bt_value)
{
    bt_value = bt_value;

    if(bt_value==BT_SC_Work)
    {
        if(input_sta==2&&Ready!=0)        //�������
        {

            sys_var.work_sta = !sys_var.work_sta;
            Dis_SP_BAS(BAS_SC_Work,sys_var.work_sta,598,553);
//            HMI_PictureCopy_xy(BAS_SC_Work,sys_var.Screen+sys_var.work_sta,598,553,598+361,553+90);  //������ͣ�ؼ�
//            HMI_TXIconVal(AMT_SC_Work,sys_var.work_sta);
            if(sys_var.work_sta)
            {
                if(sys_var.Job_step!=1)
                {
                    sys_var.Job_step = 1;
                }
            }

        }
    }

    if(sys_var.work_sta==0)    //δ��������
    {

        switch(bt_value)
        {
        case BT_SC_0:
        case BT_SC_1:
        case BT_SC_2:
        case BT_SC_3:
        case BT_SC_4:
        case BT_SC_5:
        case BT_SC_6:
        case BT_SC_7:
        case BT_SC_8:
        case BT_SC_9:
            if(input_sta==1)
            {
                if((num_value[0]*10 + bt_value-BT_SC_0)<100)
                {
                    num_value[0] = num_value[0]*10 + bt_value-BT_SC_0;
                }
                else
                {
                    num_value[0] = ( num_value[0] % 10)*10 + bt_value-BT_SC_0;                    
                }
                dis_density(sys_var.work_mode,num_value[0]);
            }
            break;
        case BT_SC_Back:
            if(input_sta==1)
            {
                if(num_value[0] > 0)
                {
                    num_value[0] = num_value[0]/10;
                    dis_density(sys_var.work_mode,num_value[0]);
                }
            }
            break;
        case BT_SC_Enter:            
            if(num_value[0]!=0)
            {
                if(num_value[0]>80)
                {
                    num_value[0] = 0;  //�޶�Ũ�ȴ�СΪ80
                    dis_density(sys_var.work_mode,num_value[0]);
                }
                else
                {
                    Ready = !Ready;
                    HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                    if(input_sta==1)
                    {
                        HMI_PictureCopy_xy(BAS_SC_Cnum,sys_var.Screen,98,283,98+373,283+148);  //������ʾ�� 
//                        HMI_PictureCopy_xy(BAS_SC_Cnum,S_SuctionCup,53,158,53+280,258+168);
                        sys_var.Density = num_value[0];
                        input_sta = 2;
                    }
                }
            }
            break;

        case BT_NUM_ET:     //Ũ����ʾ��ť
            if(Ready!=1)
            {
                input_sta = 1;
    //            num_value[0] = 0;
                dis_density(sys_var.work_mode,num_value[0]);
                HMI_PictureCopy_xy(BAS_SC_Cnum,sys_var.Screen+1,98,283,98+373,283+148);  //������ʾ�� 
//            HMI_PictureCopy_xy(BAS_SC_Cnum,S_SuctionCup+1,53,158,53+280,258+168);
            }
            break;
        case BT_SC_Home:
            if(sys_var.work_sta ==0)
            {
                if(sys_var.Language!=0)
                {
                    sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
                }
                else sys_var.Screen = S_HOME;
                sys_var.work_mode = 0;
//                if(sys_var.Job_step!=0) Clear();
                HIM_SCR_ID(sys_var.Screen);
                HMI_PictureCopy_xy(BAS_SC_Cnum,sys_var.Screen,98,283,98+373,283+148);  //������ʾ�� 
                HMI_PictureCopy_xy(BAS_SC_Cnum,S_SuctionCup,53,158,53+280,258+168); //Ũ�������λ
                
            }
            break;
        }
    }
//    if(sys_var.Job_step>=3)
//    {
        if(bt_value==BT_SC_DEC )
        {
            if(sys_var.Set_vac<10)
            {
                sys_var.Set_vac ++;
//                PWM3_OUT(500+sys_var.Set_vac*50);
                printf("��ѹ�趨��С��%d\r\n",sys_var.Set_vac);
                HMI_PictureCopy_xy(BAS_SC_Vbar,S_SuctionCup+1,94,535,94+350-map(sys_var.Set_vac,0,10,0,323),535+35);
//                HMI_PictureCopy_xy(BAS_SC_Vbar,S_SuctionCup+1,39,449,39+351-map(sys_var.Set_vac,0,10,0,351),450+43);
            }
        }
        if(bt_value== BT_SC_ADD )
        {
            if(sys_var.Set_vac>0)
            {
                sys_var.Set_vac --;
//                if(sys_var.Set_vac==0)
//                {
//                    PWM3_OUT(0);  
//                }else PWM3_OUT(500+sys_var.Set_vac*50);
                HMI_PictureCopy_xy(BAS_SC_Vbar,S_SuctionCup+1,94,535,94+350-map(sys_var.Set_vac,0,10,0,323),535+35);
//                HMI_PictureCopy_xy(BAS_SC_Vbar,S_SuctionCup+1,39,449,39+351-map(sys_var.Set_vac,0,10,0,351),450+43);
                printf("��ѹ�趨��С��%d\r\n",sys_var.Set_vac);
            }
        }
//    }

}
//��������
void Screen_Ration(unsigned short bt_value)
{

    static u8 V_sta = 0;
    bt_value = bt_value;
    if(bt_value==BT_RT_Work)
    {
        if(input_sta==2&&Ready!=0)    //����������������
        {
            sys_var.work_sta = !sys_var.work_sta;
            Dis_SP_BAS(BAS_RT_Work,sys_var.work_sta,598,553);
//            HMI_PictureCopy_xy(BAS_RT_Work,sys_var.Screen+sys_var.work_sta,599,558,599+362,558+84);  //������ͣ�ؼ�
//            HMI_TXIconVal(AMT_RT_Work,sys_var.work_sta);
            if(sys_var.work_sta==1)sys_var.Job_step = 1;

        }

    }
    if(sys_var.work_sta==0)    //δ��������
    {
        switch(bt_value)
        {
        case BT_RT_0:
        case BT_RT_1:
        case BT_RT_2:
        case BT_RT_3:
        case BT_RT_4:
        case BT_RT_5:
        case BT_RT_6:
        case BT_RT_7:
        case BT_RT_8:
        case BT_RT_9:
            if(input_sta==1)
            {
                if(V_sta==0)    //�������ֵ��Ũ��
                {
                    if((num_value[0]*10 + bt_value-BT_RT_0)<100)
                    {
                        num_value[0] = num_value[0]*10 + bt_value-BT_RT_0;
                    }
                    else
                    {
                        num_value[0] = (num_value[0]%10)*10 + bt_value-BT_RT_0;
                    }
                    dis_density(sys_var.work_mode,num_value[0]);
                }
                if(V_sta==1)        //�������ֵ�����  1234
                {
                    if((num_value[V_sta]*10 +bt_value-BT_RT_0)<10000)  //������9999
                    {
                        num_value[V_sta] = num_value[V_sta]*10 +bt_value-BT_RT_0;
                    }
                    else
                    {
                        num_value[V_sta] = (num_value[V_sta]-(num_value[V_sta]/1000)*1000)*10 +bt_value-BT_RT_0;
                    }
                    HMI_ShowNumber(TXT_RT_V,num_value[V_sta],0,8);
                }
            }
            break;
        case BT_RT_Back:
            if(input_sta==1)
            {
                if(V_sta==0)    //�������ֵ��Ũ��
                {
                    if(num_value[V_sta] > 0)
                    {
                        num_value[V_sta] = num_value[V_sta]/10;
                        dis_density(sys_var.work_mode,num_value[V_sta]);
                    }
                }
                else
                {
                    if(num_value[V_sta] >0)
                    {
                        num_value[V_sta] = num_value[V_sta]/10;
                        HMI_ShowNumber(TXT_RT_V,num_value[V_sta],0,8);
                    }
                }
            }
            break;

        case BT_RT_Enter:
            if(num_value[0]!=0)
            {
                if(num_value[0]>80)
                {
                    num_value[0] = 0;  //�޶�Ũ�ȴ�СΪ80
                    dis_density(sys_var.work_mode,num_value[0]);
                }
                else
                {
                    Ready = !Ready;
                    HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                    if(input_sta==1)
                    {
                        HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen,98,278,96+376,278+155);  //������ʾ��
                        HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen,181,475,181+248,475+44);  //����ʾ��
//                        HMI_PictureCopy_xy(BAS_RT_Cnum,S_Ration,35,167,35+338,167+240);
//                        HMI_PictureCopy_xy(BAS_RT_V,S_Ration,182,427,182+219,427+85);
                        sys_var.Density = num_value[0];
                        sys_var.O3bulk = num_value[1];
                        HMI_ShowNumber(TXT_RT_V,sys_var.O3bulk,0,8);
                        input_sta = 2;
                    }
                }
            }
            break;
        case BT_NUM_ET:     //Ũ����ʾ��ť
            if(Ready!=1)
            {
                input_sta = 1;
                V_sta = 0;
    //            num_value[0] = 0;
                HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen+1,98,278,96+376,278+155);  //������ʾ��
                HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen,181,475,181+248,475+44);  //����ʾ��
    //            HMI_PictureCopy_xy(BAS_RT_Cnum,S_Ration+1,35,167,35+338,167+240);
    //            HMI_PictureCopy_xy(BAS_RT_V,S_Ration,182,427,182+219,427+85);
                dis_density(sys_var.work_mode,num_value[V_sta]);
            }
            break;
        case BT_RT_Home:
        
            if(sys_var.Language!=0)
            {
                sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
            }
            else sys_var.Screen = S_HOME;
            sys_var.work_mode = 0;
            V_sta = 0;
//            if(sys_var.Job_step!=0) Clear();        //�����
            HIM_SCR_ID(sys_var.Screen);
            HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen,98,278,96+376,278+155);  //������ʾ��
            HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen,181,475,181+248,475+44);  //����ʾ��
//            HMI_PictureCopy_xy(BAS_RT_Cnum,S_Ration,35,167,35+338,167+240);
//            HMI_PictureCopy_xy(BAS_RT_V,S_Ration,182,427,182+219,427+85);
            break;

        case BT_RT_V:     //�����ť
            if(Ready!=1)
            {
                V_sta=1;
                input_sta = 1;
                HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen,98,278,96+376,278+155);  //������ʾ��
                HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen+1,181,475,181+248,475+44);  //����ʾ��
    //            HMI_PictureCopy_xy(BAS_RT_Cnum,S_Ration,35,167,35+338,167+240);
    //            HMI_PictureCopy_xy(BAS_RT_V,S_Ration+1,182,427,182+219,427+85);
    //            num_value[1] = 0;
                HMI_ShowNumber(TXT_RT_V,num_value[V_sta],0,8);
            }
            break;
        }
        
//        if(input_sta!=1)
//        {
        switch(bt_value)
        {
        case BT_RT_10ml:
            sys_var.O3bulk=10;
            HMI_ShowNumber(TXT_RT_V,sys_var.O3bulk,0,8);
            num_value[1] = sys_var.O3bulk;
            break;
        case BT_RT_20ml:
            sys_var.O3bulk=20;
            HMI_ShowNumber(TXT_RT_V,sys_var.O3bulk,0,8);
            num_value[1] = sys_var.O3bulk;

            break;
        case BT_RT_50ml:
            sys_var.O3bulk=50;
            HMI_ShowNumber(TXT_RT_V,sys_var.O3bulk,0,8);
            num_value[1] = sys_var.O3bulk;

            break;
        case BT_RT_100ml:
            sys_var.O3bulk=100;
            HMI_ShowNumber(TXT_RT_V,sys_var.O3bulk,0,8);
            num_value[1] = sys_var.O3bulk;

            break;
        }
//        }
    }
    
}
//ע����
void Screen_Injector(unsigned short bt_value)
{

    bt_value = bt_value;

    if(bt_value==BT_IJ_Work)
    {
        if(input_sta==2&&Ready!=0)    //����������������
        {
            sys_var.work_sta = !sys_var.work_sta;
            Dis_SP_BAS(BAS_IJ_Work,sys_var.work_sta,598,553);
//            HMI_PictureCopy_xy(BAS_IJ_Work,sys_var.Screen+sys_var.work_sta,600,558,600+359,558+86);  //������ͣ�ؼ�
//            HMI_TXIconVal(AMT_IJ_Work,sys_var.work_sta);
            if(sys_var.work_sta==1) sys_var.Job_step = 1;

        }

    }
    if(sys_var.work_sta==0)    //δ��������
    {
        switch(bt_value)
        {
        case BT_IJ_0:
        case BT_IJ_1:
        case BT_IJ_2:
        case BT_IJ_3:
        case BT_IJ_4:
        case BT_IJ_5:
        case BT_IJ_6:
        case BT_IJ_7:
        case BT_IJ_8:
        case BT_IJ_9:
            if(input_sta==1)
            {
                if((num_value[0]*10 + bt_value-BT_IJ_0)<100)
                {
                    num_value[0] = num_value[0]*10 + bt_value-BT_IJ_0;
                }
                else
                {
                    num_value[0] = (num_value[0]%10)*10 + bt_value-BT_IJ_0;
                }
                dis_density(sys_var.work_mode,num_value[0]);
            }
            break;
        case BT_IJ_Back:
            if(input_sta==1)
            {
                if(num_value[0] > 0)
                {
                    num_value[0] = num_value[0]/10;
                    dis_density(sys_var.work_mode,num_value[0]);
                }
            }
            break;
        case BT_IJ_Enter:            
            if(num_value[0]>80)
            {
                num_value[0] = 0;  //�޶�Ũ�ȴ�СΪ80
                dis_density(sys_var.work_mode,num_value[0]);
            }
            else
            {
                Ready = !Ready;
                HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                if(input_sta==1)
                {
                    HMI_PictureCopy_xy(BAS_IJ_Cnum,sys_var.Screen,98,352,98+376,352+217);  //������ʾ��
//                        HMI_PictureCopy_xy(BAS_IJ_Cnum,S_Injector,34,168,34+341,168+290);
                    sys_var.Density = num_value[0];
                    input_sta = 2;
                }
//                
            }
            break;
        case BT_NUM_ET:     //Ũ����ʾ��ť
            if(Ready!=1)
            {
                input_sta = 1;
    //            num_value[0] = 0;
                HMI_PictureCopy_xy(BAS_IJ_Cnum,sys_var.Screen+1,98,352,98+376,352+217);  //������ʾ��
    //            HMI_PictureCopy_xy(BAS_IJ_Cnum,S_Injector+1,34,168,34+341,168+290);
                dis_density(sys_var.work_mode,num_value[0]);
            }
            break;

        case BT_IJ_Home:
            if(sys_var.Language!=0)
            {
                sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
            }
            else sys_var.Screen = S_HOME;
            sys_var.work_mode = 0;
//            if(sys_var.Job_step!=0) Clear();   //�����
            HIM_SCR_ID(sys_var.Screen);
            HMI_PictureCopy_xy(BAS_IJ_Cnum,sys_var.Screen,98,352,98+376,352+217);  //������ʾ��
//            HMI_PictureCopy_xy(BAS_IJ_Cnum,S_Injector,34,168,34+341,168+290);
            break;
        }
    }
}
//���ý���
void Screen_Setting(unsigned short bt_value)
{
    bt_value = bt_value;
    switch(bt_value) {
    case BT_ST_Language:
        New_language = sys_var.Language;
        Deal_Language(sys_var.Language);
        sys_var.Screen = S_Language;
        HIM_SCR_ID(S_Language);
        break;
    case BT_ST_Parameter:
//        HMI_TXIconVal(VAR_AM_Adm,sys_var.Language);
//        HMI_TXIconVal(VAR_AM_Login,2*sys_var.Language);

        sys_var.Screen = S_Administrator + 8*sys_var.Language;
        HMI_TXStrToEdit(TXT_AM_User,"     ",8);
        HMI_TXStrToEdit(TXT_AM_Pswd,"     ",8);
        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,180,282,180+296,282+47);    //�˺������
        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,181,370,181+294,370+50);      //���������

        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_ST_Informat:
        sys_var.Screen = S_Information+8*sys_var.Language;
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_ST_Home:
        if(sys_var.Language!=0)
        {
            sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
        }
        else sys_var.Screen = S_HOME;
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_ST_Light:
        Back_Light = BT_KEY;
        HMI_BackLightCtrl(Back_Light);
        break;
    case BT_ST_Voice:
        sys_var.BEEP_sta=!sys_var.BEEP_sta;
        if(sys_var.BEEP_sta==1) {
            HMI_PictureCopy_xy(BAS_ST_Voice,S_Setting+1,860,549,860+92,549+50);
        } else HMI_PictureCopy_xy(BAS_ST_Voice,S_Setting,860,549,860+92,549+50);
        delay_ms(200);
//        HMI_BEEP_ENABLE(sys_var.BEEP_sta);
//        EEPROM_WriteSeq(ERPIP_BEEP,(INT8U*)&sys_var.BEEP_sta,sizeof(sys_var.BEEP_sta));

        break;

    default:
        break;
    }
}
//���Խ���
void Screen_Language(unsigned short bt_value)
{
    
    bt_value = bt_value;
    switch(bt_value)
    {
    case BT_L_English:      //Ӣ
        New_language = Engliah;
        Deal_Language(New_language);
        break;
    case BT_L_Deutsch:      //��
        New_language = Deutush;
        Deal_Language(New_language);
        break;
    case BT_L_Espanol:  //��
        New_language = Espanol;
        Deal_Language(New_language);
        break;
    case BT_L_Pycckn:   //��
        New_language = Pyccknn;
        Deal_Language(New_language);
        break;
    case BT_L_Francais: //��
        New_language = Francaise;
        Deal_Language(New_language);
        break;
    case BT_L_Chinese:  //��
        New_language = Chinese;
        Deal_Language(New_language);
        break;
    case BT_L_OK:
        sys_var.Language =New_language;
        EEPROM_WriteSeq(ERPIP_Language,(INT8U*)&sys_var.Language,sizeof(sys_var.Language));
        if(sys_var.Language!=0)
        {
            sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
        }
        else sys_var.Screen = S_HOME;
        HIM_SCR_ID(sys_var.Screen);
        break;
    default:
        break;
    }

//    printf("����%d\r\n",language);
}






//����Ա����
void Screen_Admi(unsigned short bt_value)
{
    char str[6] = {"      "};
    static char user_enter[6];
    static u8 len_enter=0;
    static u8 sta_enter=0;
    static char pswd_enter[8];
    bt_value = bt_value;
    switch(bt_value)
    {
    case BT_AM_User:
        sta_enter = 1;
        len_enter = 0;
        Str_memset(user_enter,0,6);
        HMI_TXStrToEdit(TXT_AM_User,user_enter,8);
        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen+1,180,282,180+296,282+47);    //�˺������
        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,181,370,181+294,370+50);      //���������

//        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen+1,141,167,141+188,167+62);    //�˺������
//        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,141,279,141+188,279+62);      //���������
        break;
    case BT_AM_Pswd:
        sta_enter = 2;
        len_enter = 0;
        Str_memset(pswd_enter,0,6);
        HMI_TXStrToEdit(TXT_AM_Pswd,pswd_enter,8);
        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,180,282,180+296,282+47);    //�˺������
        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen+1,181,370,181+294,370+50);      //���������

//        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,141,167,141+188,167+62);
//        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen+1,141,279,141+188,279+62);
        break;
    case BT_AM_Login:
        sta_enter = 0;
        len_enter = 0;
        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,180,282,180+296,282+47);    //�˺������
        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,181,370,181+294,370+50);      //���������

    
//        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,141,167,141+188,167+62);    //�˺������
//        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,141,279,141+188,279+62);
        if(compare_array(user_enter,"002",3)==1)
        {
            if(compare_array(pswd_enter,"963215",6)==1)
            {
                sys_var.Screen = S_ProSet +8 * sys_var.Language;
                HMI_TXStrToEdit(TXT_CK_C,"     ",8);
                HMI_TXStrToEdit(TXT_CK_P,"     ",8);
                HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,179,277,179+296,277+54);    //�˺������
                HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,180,372,180+295,372+53);      //���������
//                HMI_PictureCopy_xy(BAS_CK_Check,sys_var.Screen,163,373,163+141,373+54);


                HIM_SCR_ID(sys_var.Screen);

            }
        }
        break;
    case BT_AM_0:
    case BT_AM_1:
    case BT_AM_2:
    case BT_AM_3:
    case BT_AM_4:
    case BT_AM_5:
    case BT_AM_6:
    case BT_AM_7:
    case BT_AM_8:
    case BT_AM_9:
        if(sta_enter==1)
        {
            if(len_enter<3)
            {
                user_enter[len_enter] = bt_value - BT_AM_0 + '0';
                HMI_TXStrToEdit(TXT_AM_User,user_enter,8);
                len_enter++;
            }
        }
        if(sta_enter==2)
        {
            if(len_enter<6)
            {
                pswd_enter[len_enter] = bt_value - BT_AM_0 + '0';
                HMI_TXStrToEdit(TXT_AM_Pswd,pswd_enter,8);
                len_enter++;
            }
        }
        break;
    case BT_AM_Back:
        if(sta_enter==1)
        {
            if(len_enter>0)
            {
                len_enter--;
                user_enter[len_enter] = ' ';
                HMI_TXStrToEdit(TXT_AM_User,user_enter,8);
            }
        }
        else if(sta_enter==2)
        {
            if(len_enter>0)
            {
                len_enter--;
                pswd_enter[len_enter] = ' ';
                HMI_TXStrToEdit(TXT_AM_Pswd,pswd_enter,8);

            }
        }
        break;
    case BT_AM_Enter:
        if(sta_enter==1)
        {
            len_enter = 0;
            sta_enter = 0;
            HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,180,282,180+296,282+47);    //�˺������
            
//            HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,179,277,179+296,277+54);    //�˺������
//            HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,141,167,141+188,167+62);    //�˺������
        }
        if(sta_enter==2)
        {
            len_enter = 0;
            sta_enter = 0;  
            HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,181,370,181+294,370+50);      //���������
            
//            HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,180,372,180+295,372+53);      //���������
//            HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,141,279,141+188,279+62);    //�˺������
        }
        break;
    case BT_AM_Home:
        len_enter = 0;
        sta_enter = 0;
        MemoryCopy(pswd_enter,str,6);
        MemoryCopy(user_enter,str,6);
        if(sys_var.Language!=0)
        {
            sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
        }
        else sys_var.Screen = S_HOME;
        HIM_SCR_ID(sys_var.Screen);
        break;
    default:
        break;

    }

}
//���̲�������
void Screen_ProSet(unsigned short bt_value)
{
    static int enter_c = 0;
    static int enter_p = 0;
    static u8 sta_enter=0;
    static u8 sta_check=0;
    static u16 C_P_data[80];
//    static u16 C_P_Adj_Data[9];
    bt_value = bt_value;
    if( BT_CK_Check == bt_value)
    {
        if(sta_enter == 3)
        {
            sys_var.work_sta = !sys_var.work_sta;
        }
        
        
        if(sys_var.work_sta==1)
        {
//            HMI_PictureCopy_xy(BAS_CK_Check,sys_var.Screen+1,163,373,163+141,373+54);
            Valve1 = Valve2 = Valve3 =ON;
            Valve4 = Valve5 = Valve6 = Valve7 = OFF;
            C_P_data[enter_c-1] = enter_p;
            if((enter_c==1)||(enter_c%10==0))
            {
                Density_Adj_P[enter_c/10] = enter_p;
            }
            TIM_Cmd(TIM4, ENABLE);      //����PWM���
            PWM2_OUT(C_P_data[enter_c-1]);
            
            printf("�����Ƴ���\r\n");
            printf("C=%d  P =%d",enter_c,C_P_data[enter_c-1]);
        }
        else
        {
//            HMI_PictureCopy_xy(BAS_CK_Check,sys_var.Screen,163,373,163+141,373+54);
            Valve1 = Valve2 = Valve3 =OFF;
            Valve4 = Valve5 = Valve6 = Valve7 = OFF;
            TIM_Cmd(TIM4, DISABLE);      //����PWM���
            
            PWM2_OUT(0);
            printf("�رճ���\r\n");
        }
    }
    if(sys_var.work_sta==0)
    {
        switch(bt_value)
        { 
            case BT_CK_C:
                if(sta_check==0)
                {
                    sta_enter = 1;
                    enter_c = 0;
                    HMI_ShowNumber_int(TXT_CK_C,enter_c,2,8);
                    HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen+1,179,277,179+296,277+54);    //�˺������
                    HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,180,372,180+295,372+53);      //���������
//                    HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen+1,141,167,141+188,167+62);    //Ũ�������
//                    HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,141,279,141+188,279+62);      //���������
                }
                break;
            case BT_CK_P:
                sta_enter = 2;
                enter_p = 0;
                HMI_ShowNumber_int(TXT_CK_P,enter_p,4,8);
            
                HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,179,277,179+296,277+54);    //�˺������
                HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen+1,180,372,180+295,372+53);      //���������
//                HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,141,167,141+188,167+62);    //Ũ�������
//                HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen+1,141,279,141+188,279+62);      //���������

                break;
            case BT_CK_0:
            case BT_CK_1:
            case BT_CK_2:
            case BT_CK_3:
            case BT_CK_4:
            case BT_CK_5:
            case BT_CK_6:
            case BT_CK_7:
            case BT_CK_8:
            case BT_CK_9:
                if(sta_enter==1)
                {
                    if((enter_c * 10 + bt_value - BT_CK_0)<100)
                    {
                        enter_c = enter_c * 10 + bt_value - BT_CK_0;
                        if(enter_c > 80) enter_c = 0;
                        HMI_ShowNumber_int(TXT_CK_C,enter_c,2,8);
                        HMI_ShowNumber_int(TXT_CK_P,Density_P[enter_c-1],4,8);
                        
                    }
                }

                if(sta_enter==2)
                {
                    if((enter_p * 10 + bt_value - BT_CK_0)<10000)
                    {
                        enter_p = enter_p * 10 + bt_value - BT_CK_0;
                        HMI_ShowNumber_int(TXT_CK_P,enter_p,4,8);
                    }
                }
                break;
            case BT_CK_Back:
                if(sta_enter==1)
                {
                    if(enter_c>0)
                    {
                        enter_c = enter_c / 10;
                        HMI_ShowNumber_int(TXT_CK_C,enter_c,2,8);
                    }
                }
                if(sta_enter==2)
                {
                    if(enter_p>0)
                    {
                        enter_p = enter_p / 10;
                        HMI_ShowNumber_int(TXT_CK_P,enter_p,4,8);
                    }
                }
                break;
            case BT_CK_Enter:
                if(sta_enter==1)
                {
                    enter_p = Density_P[enter_c-1];
                    sta_enter = 3;
                }
                if(sta_enter==2)
                {
                    sta_enter = 3;
                }
                HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,181,372,180+295,372+53);      //���������
                HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,179,275,179+296,275+54);    //�˺������

                break;
            case BT_CK_Home:
                enter_c = 0;
                enter_p = 0;
                sta_enter = 0;
                if(sys_var.Language!=0)
                {
                    sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
                }
                else sys_var.Screen = S_HOME;
                Map_Density(Density_Adj_P);
                EEPROM_WriteSeq(ERRIP_Density_P,(INT8U*)&Density_Adj_P,sizeof(Density_Adj_P));       
                delay_ms(50);
                HIM_SCR_ID(sys_var.Screen);
                break;

        }
    }
}

//�豸��Ϣ����
void Screen_DevInf(unsigned short bt_value)
{
    bt_value = bt_value;
    if((bt_value==BT_DI_Exit)||(bt_value==BT_DI_Exit2))
    {
        if(sys_var.Language!=0)
        {
            sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
        }
        else sys_var.Screen = S_HOME;
        HIM_SCR_ID(sys_var.Screen);
    }
}

//���Խ���
void Screen_Test(unsigned short bt_value)
{
    static u8 sta = 0;
    bt_value = bt_value;
    if(bt_value == BT_TS_S)
    {
        sys_var.test_sta = 1+sta;
        sta = !sta;
    }
    else if(bt_value == BT_TS_E)
    {
        sys_var.test_sta = 3;
        sys_var.Screen = S_HOME + 24 * sys_var.Language;
        HIM_SCR_ID(sys_var.Screen);
    }
}






//���󱨾�����
void Screen_Error(unsigned short bt_value)      //���Խ��� 
{
    bt_value = bt_value;
    if(bt_value==BT_ERR_Eixt)
    {
        sys_var.Error = 0;
        sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
        HIM_SCR_ID(sys_var.Screen);
    }
}



