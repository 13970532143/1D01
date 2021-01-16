/*
* 版权所有(C): 黄文基 深圳科医仁科技发展有限公司 2020.6
* 文档说明：触摸屏任务，响应操作者在触摸屏上的操作
*
*/

//LCD UI test

#include "test.h"
volatile SYStem_Variables sys_var;
u32 num_value[2];  //输入长度
u8 input_sta = 0;    //输入状态 0禁止
char versions_B[14]= {"1D01-B-V1.0"};	//版本
char versions_A[14]={"1D01-A-V1.0"};
u8 New_language=0;
u8 Ready=0,Stadby=0;
u16 Back_Light = 100;
void Screen_Welcome(unsigned short bt_value);   //开机界面
void Screen_HOME(unsigned short bt_value);      //模式选择界面
void Screen_O3Bag(unsigned short bt_value);     //三氧套袋界面
void Screen_IFBottle(unsigned short bt_value);  //真空瓶界面
void Screen_IFBAG(unsigned short bt_value);     //输液袋界面
void Screen_O3Hydrate(unsigned short bt_value); //臭氧水界面
void Screen_SuctionCup(unsigned short bt_value);//负压罩杯
void Screen_Ration(unsigned short bt_value);    //定量供气界面
void Screen_Injector(unsigned short bt_value);  //注射器界面
void Screen_Admi(unsigned short bt_value);      //管理员界面
void Screen_Setting(unsigned short bt_value);   //系统配置界面
void Screen_Language(unsigned short bt_value);  //语言界面
void Screen_ProSet(unsigned short bt_value);    //浓度参数设置界面
void Screen_DevInf(unsigned short bt_value);    //设备信息界面
void Screen_Test(unsigned short bt_value);      //测试界面
void Screen_Error(unsigned short bt_value);      //测试界面 

//存储检测
void ERP_Check(void)
{
    EEPROM_ReadSeq(ERPIP_Language,(INT8U*)&sys_var.Language,sizeof(sys_var.Language));
    delay_ms(50);
    if(sys_var.Language>7)      //没有正确读到语言
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





//触摸屏任务入口
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
        printf("握手成功\r\n");
        sys_var.Screen = S_Welcome;
        HIM_SCR_ID(sys_var.Screen);
        delay_ms(50);
        HMI_TXIntToEdit(ED_Ver_E,5);                //显示进度
        HMI_PictureCopy_xy(BAS_W_E,1,16,621,16+45,621+26);     //显示进度条
        HMI_TXStrToEdit(TXT_Ver_A,versions_A,15);      //显示版本号
        HMI_TXStrToEdit(TXT_Ver_B,versions_B,15);
    }
    else
    {
        printf("握手失败\r\n");
        SV17F_MP3_Specify(13);
        goto Rest_LCD;
    }
    delay_ms(50);

     Clear();    //开机清洁·
//    if(sys_var.Language!=0)
//    {
//        sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
//    }
//    else sys_var.Screen = S_HOME;
////    sys_var.Screen = S_Welcome;
//    HIM_SCR_ID(sys_var.Screen);
//    Set_T5HIM_Time(20,8,16,11,31,50);//设置时间，把注释取消，用于更新时间，更新后，需要把此行注释
//    HIM_ADJ();
//    printf("握手成功\r\n");
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
//                printf("界面=%d\r\n",sys_var.Screen);
            }

            
        }
        delay_ms(50);
    }

}

//开机界面
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
//    else if(bt_value==BT_W_TEST)        //测试按钮
//    {
//        cnt++;
//        if(cnt>=5)
//        {
//            cnt = 0;
//            
//        }
//    }
}



//菜单界面/模式选择界面
void Screen_HOME(unsigned short bt_value)
{
    bt_value = bt_value;
    Ready = 0;
    switch(bt_value)
    {
    case BT_M_O3Bag://三氧套袋
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //输入状态 0禁止
        sys_var.Density = 0;
        sys_var.work_mode = O3Bag;
        dis_density(sys_var.work_mode,sys_var.Density);

        sys_var.Screen = S_O3Bag ;                                            
        HMI_PictureCopy_S_T_xy(BAS_OB_TM,70,0,0+100*sys_var.Language,450-1,100+100*sys_var.Language-1,316,24);
        Dis_CV_BAS(BAS_OB_C,0,77,91,414);
        Dis_CV_BAS(BAS_OB_V,0,78,95,522);
        HMI_TXIconVal(VAR_SR,sys_var.Language);
        HMI_PictureCopy_xy(BAS_OB_Cnum,sys_var.Screen,94,213,94+382,312+158);  //数字显示框
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_InfusionBottle://输液瓶
//            LED1 = !LED1;
        sys_var.Density = 0;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //输入状态 0禁止
        sys_var.work_mode = infusionBottle;
        dis_density(sys_var.work_mode,sys_var.Density);     //显示臭氧浓度



//        dis_vac_bar(100);
        sys_var.Screen = S_IFBottle;
//        HMI_PictureCopy_S_T_xy(BAS_BT_Work,70,0,0+100*sys_var.Language,450-1,100+100*sys_var.Language-1,599,556);
        HMI_PictureCopy_S_T_xy(BAS_BT_TM,71,0,0+100*sys_var.Language,500-2,100+100*sys_var.Language-2,266,29);
        Dis_CV_BAS(BAS_BT_C,0,77,95,374);
        Dis_CV_BAS(BAS_BT_V,0,78,97,474);
        HMI_PictureCopy_xy(BAS_BT_Cnum,sys_var.Screen,89,204,89+384,204+155);  //数字显示框
        HMI_TXIconVal(VAR_SR,sys_var.Language);
        HMI_PictureCopy_xy(BAS_BT_Vbar,sys_var.Screen+1,99,588,120+320*3/5,588+35);  //压力条
        
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_InfusionBag://输液袋
//            LED1 = !LED1;
        sys_var.Density = 0;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //输入状态 0禁止
        sys_var.work_mode = infusionBag;
        dis_density(sys_var.work_mode,sys_var.Density);
        sys_var.O3bulk = 0;
        sys_var.Dosage = 0;
        HMI_ShowNumber(TXT_BG_V,sys_var.O3bulk,0,8);
        HMI_ShowNumber(TXT_BG_Dosage,sys_var.Dosage,0,8);
        sys_var.Screen = S_IFBAG ;
        Dis_SP_BAS(BAS_BG_Work,0,598,553);
        HMI_PictureCopy_S_T_xy(BAS_BG_TM,72,0,0+100*sys_var.Language,450-7,100+100*sys_var.Language-7,266,30);    //模式       
        HMI_PictureCopy_S_T_xy(BAS_BG_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,103,190);    //浓度字符
        HMI_PictureCopy_S_T_xy(BAS_BG_TV,80,501,0+50*sys_var.Language,501+125,50+50*sys_var.Language,46,509);    //浓度字符
        HMI_PictureCopy_S_T_xy(BAS_BG_TQ,80,689,0+50*sys_var.Language,689+125,50+50*sys_var.Language,47,572);    //浓度字符
        
//        HMI_PictureCopy_S_T_xy(BAS_BG_TC,80,0,0+100*5,450-1,100+100*5-2,103,190);    //模式
        HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen,95,313,95+381,313+154);
        HMI_PictureCopy_xy(BAS_BG_V,sys_var.Screen,179,507,179+252,507+57); //体积
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_BG_Work,sys_var.Screen,599,556,599+362,556+88);  //开启暂停控件
        
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_O3Hydrate://三氧水化
//            LED1 = !LED1;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //输入状态 0禁止
        sys_var.Density = 0;
        sys_var.H2O_countdowm = 0;
        sys_var.work_mode = O3Hydrate;

        dis_density(sys_var.work_mode,sys_var.Density);
        sys_var.H2O_countdowm = 0;  //倒计时，模式设置为0


        sys_var.Countdown = 600;
        dis_countdown(sys_var.Countdown);       //显示倒计时
        sys_var.Screen = S_O3Hydrate ;
        HMI_PictureCopy_S_T_xy(BAS_H_TM,73,0,0+100*sys_var.Language,450-2,100+100*sys_var.Language-2,267,29);    //模式       
        HMI_PictureCopy_S_T_xy(BAS_H_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,104,187);    //浓度字符
        
        HMI_PictureCopy_xy(BAS_H_Cnum,sys_var.Screen,97,349,97+375,349+223);
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_H_Work,sys_var.Screen,597,552,597+361,552+90);  //开启暂停控件
        Dis_SP_BAS(BAS_H_Work,0,598,553);
        HIM_SCR_ID(S_O3Hydrate);
        break;
    case BT_M_SuctionCup://负压罩杯
//            LED1 = !LED1;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //输入状态 0禁止
        sys_var.Density = 0;
        sys_var.work_mode = suctionCup;

        dis_density(sys_var.work_mode,sys_var.Density);//显示臭氧浓度
        sys_var.Set_vac = 0;
//        HMI_TXIconVal(AMT_SC_Work,0);       //显示工作状态
        sys_var.Screen = S_SuctionCup ;
        HMI_PictureCopy_S_T_xy(BAS_SC_TM,74,0,2+100*sys_var.Language,500-2,102+100*sys_var.Language-2,266,29);    //模式       
        HMI_PictureCopy_S_T_xy(BAS_SC_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,103,168);    //浓度字符
        HMI_PictureCopy_S_T_xy(BAS_SC_TV,81,34,30+60*sys_var.Language,34+358,30+56+60*sys_var.Language,104,461);    //浓度字符
        
        HMI_PictureCopy_xy(BAS_SC_Cnum,sys_var.Screen,98,283,98+373,283+148);  //数字显示框    
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_SC_Work,sys_var.Screen,598,553,598+361,553+90);  //开启暂停控件
        Dis_SP_BAS(BAS_SC_Work,0,598,553);
        HMI_PictureCopy_xy(BAS_SC_Vbar,S_SuctionCup+1,94,535,94+350,535+35);
        HIM_SCR_ID(S_SuctionCup);         //切换界面
        break;
    case BT_M_Ration://定量供气
//            LED1 = !LED1;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //输入状态 0禁止
        sys_var.Density = 0;
        sys_var.work_mode = ration;

//        HMI_TXIconVal(VAR_RT_TM,sys_var.Language);  //显示定量供气字符
//        HMI_TXIconVal(VAR_RT_TC,sys_var.Language);  //显示浓度字符
//        HMI_TXIconVal(VAR_RT_TV,sys_var.Language);  //显示体积字符

        dis_density(sys_var.work_mode,sys_var.Density);//显示臭氧浓度
        sys_var.O3bulk = 0; //体积
        HMI_ShowNumber(TXT_RT_V,sys_var.O3bulk,0,8);    //显示臭氧体积
//        HMI_TXIconVal(AMT_RT_Work,0);       //显示工作状态
        sys_var.Screen = S_Ration;
        
    
        HMI_PictureCopy_S_T_xy(BAS_RT_TM,75,0,0+100*sys_var.Language,500-2,100+100*sys_var.Language-2,266,29);    //模式       
        HMI_PictureCopy_S_T_xy(BAS_RT_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,103,168);    //浓度字符
        HMI_PictureCopy_S_T_xy(BAS_RT_TV,80,501,0+50*sys_var.Language,501+125,50+50*sys_var.Language,48,472);    //浓度字符
       
        HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen,0,0,0,0);  //数字显示框
        HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen,181,475,181+248,475+44);  //体显示框
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_RT_Work,sys_var.Screen,599,558,599+362,558+84);  //开启暂停控件
        Dis_SP_BAS(BAS_RT_Work,0,598,553);    
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_Injector://注射器模式
//          LED1 = !LED1;
        num_value[0]=0 ;
        num_value[1]=0 ;
        input_sta = 0;    //输入状态 0禁止
        sys_var.Density = 0;
        sys_var.work_mode = injector;

//        HMI_TXIconVal(VAR_IJ_TM,sys_var.Language);  //显示注射器气字符
//        HMI_TXIconVal(VAR_IJ_TC,sys_var.Language);  //显示浓度字符

        dis_density(sys_var.work_mode,sys_var.Density); //显示臭氧浓度
//        HMI_TXIconVal(AMT_RT_Work,0);       //显示工作状态
        sys_var.Screen = S_Injector;
        HMI_PictureCopy_S_T_xy(BAS_IJ_TM,76,0,0+100*sys_var.Language,450-2,100+100*sys_var.Language-2,266,29);    //模式       
        HMI_PictureCopy_S_T_xy(BAS_IJ_TC,80,34,30+70*sys_var.Language,34+358,30+56+70*sys_var.Language,104,199);    //浓度字符
           
        HMI_PictureCopy_xy(BAS_IJ_Cnum,sys_var.Screen,98,352,98+376,352+217);  //数字显示框
        HMI_TXIconVal(VAR_SR,sys_var.Language);
//        HMI_PictureCopy_xy(BAS_IJ_Work,sys_var.Screen,600,558,600+359,558+86);  //开启暂停控件
        Dis_SP_BAS(BAS_IJ_Work,0,598,553);    
        
        HIM_SCR_ID(sys_var.Screen);
        break;
    case BT_M_Settings:
        HMI_PictureCopy_xy(BAS_ST_Voice,S_Setting,860,549,860+92,549+50);      //声音状态        
        
        HMI_BackLightCtrl(Back_Light);
        HMI_TXIconVal(BT_ST_Light,Back_Light);       //亮度显示
//            HMI_BackLightCtrl(50);
        sys_var.Screen = S_Setting+8*sys_var.Language;
        HIM_SCR_ID(sys_var.Screen);    //切换系统配置界面
        break;

    default:
        break;
    }

}

/* 三氧套袋界面
*   1. 点击真空，抽真空，负压<50Kpa，停止抽真空
*   2. 输入浓度(1-80,>80时，归零)
*   3. 点击浓度，制臭氧
*/
void Screen_O3Bag(unsigned short bt_value)
{

    bt_value = bt_value;
    if(sys_var.work_sta==0 &&sys_var.Vac_Open==0)    //臭氧未开启
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
        case BT_OB_Back:        //退位
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
                        HMI_PictureCopy_xy(BAS_OB_Cnum,sys_var.Screen,94,213,94+382,312+158);  //数字显示框
    //                        HMI_PictureCopy_xy(BAS_OB_Cnum,S_O3Bag,33,199,33+281,199+196);  //数字显示框
                        input_sta  = 2; //输入确定后不允许输入，除非再次点击浓度输入框
                        
                    }
                }
            }
            break;

        case BT_NUM_ET:     //浓度显示框按钮
            if(Ready==0)
            {
                input_sta = 1;
    //            num_value[0] = 0;
                dis_density(sys_var.work_mode,num_value[0]);
                HMI_PictureCopy_xy(BAS_OB_Cnum,sys_var.Screen+1,94,213,94+382,312+158);  //数字显示框
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
            HMI_PictureCopy_xy(BAS_OB_Cnum,sys_var.Screen,94,213,94+382,312+158);  //数字显示框
            break;
        }
    }
    if(Ready==1)
    {
        if(bt_value==  BT_OB_Concentration)   //臭氧
        {
            if(sys_var.Vac_Open == 0)  //抽真空结束或未进行
            {

                if(input_sta == 2)  //输入结束--按下Enter控件
                {
                    if(sys_var.Adc_value[vacuum_v]<130)       //套袋里面的气压大于130时不能开启制臭氧
                    {
                        sys_var.work_sta = !sys_var.work_sta;
                        if(sys_var.work_sta==1)
                        {
                            Dis_CV_BAS(BAS_OB_C,1,77,91,414);
                            sys_var.Job_step = 3;
                        }
                        else //关臭氧
                        {
                            Dis_CV_BAS(BAS_OB_C,0,77,91,414);

                            PWM3_OUT(VacCtr_OFF);       //泵
                            Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                            Valve5 = Valve6 = ON;
                            TIM_Cmd(TIM4, DISABLE);  //关臭氧
                            PWM2_OUT(0);
                        }
                    }
                    else
                    {
                        if(sys_var.work_sta==1)  sys_var.work_sta = 0;
                        Dis_CV_BAS(BAS_OB_C,0,77,91,414);           //浓度状态
                        PWM3_OUT(VacCtr_OFF);       //泵
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                        Valve5 = Valve6 = ON;
                        TIM_Cmd(TIM4, DISABLE);  //关臭氧
                        PWM2_OUT(0);      //PWM 占空比调为0
                    }
                }
            }
        }
        if(bt_value==  BT_OB_Vacuo)
        {

            if(sys_var.work_sta == 0)  //臭氧未开启
            {
                if(sys_var.Adc_value[vacuum_v]>85)       //当前压力大于85Kpa
                {
                    sys_var.Vac_Open = !sys_var.Vac_Open;       //切换抽负压开启状态
                    if(sys_var.Vac_Open!=0)     //开启抽负压
                    {
                        Dis_CV_BAS(BAS_OB_V,1,78,95,522);       //负压控件按下
                        sys_var.Job_step = 1;

                    }
                    else
                    {
                        Dis_CV_BAS(BAS_OB_V,0,78,95,522);       //负压控件弹起
                        PWM3_OUT(VacCtr_OFF);       //泵
                        Valve6 = ON;       //切换三通状态，维持套袋内部负压

                    }
                }
                else
                {
                    if(sys_var.Vac_Open==1)sys_var.Vac_Open = 0;
                    Dis_CV_BAS(BAS_OB_V,0,78,95,522);   //负压控件弹起
                    PWM3_OUT(VacCtr_OFF);       //泵
                    Valve6 = ON;       //切换三通状态，维持套袋内部负压
                }
            }
        }
    }
}
//输液瓶
void Screen_IFBottle(unsigned short bt_value)
{
    bt_value = bt_value;
    if(sys_var.work_sta==0&&sys_var.Vac_Open!=1)    //机器处于待机状态
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
                    num_value[0] = 0;  //限定浓度大小为80
                    dis_density(sys_var.work_mode,num_value[0]);//显示浓度

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
                        input_sta  = 2; //输入结束
//                        HMI_PictureCopy_xy(BAS_BT_Cnum,S_IFBottle,42,188,42+252,188+173);
                        HMI_PictureCopy_xy(BAS_BT_Cnum,sys_var.Screen,89,204,89+384,204+155);  //数字显示框
                    }
                }
            }
            break;
        case BT_NUM_ET:     //浓度显示框按钮
            if(Ready==0)
            {
                input_sta = 1;
    //            num_value[0] = 0;
    //            HMI_PictureCopy_xy(BAS_BT_Cnum,S_IFBottle+1,43,188,42+252,188+173);
                HMI_PictureCopy_xy(BAS_BT_Cnum,sys_var.Screen+1,89,204,89+384,204+155);  //数字显示框
                dis_density(sys_var.work_mode,num_value[0]);
            }
            break;
        case BT_BT_Home:
            if(sys_var.work_sta==0)  //抽真空结束或臭氧结束
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
            if(sys_var.Vac_Open!=1)  //抽真空结束或未进行
            {

                if(input_sta == 2)  //输入结束--按下Enter控件
                {
                    
                    
                    if(sys_var.Adc_value[vacuum_v]<130)    //
                    {
                        sys_var.work_sta=!sys_var.work_sta;
                        if(sys_var.work_sta)
                        {
                            Dis_CV_BAS(BAS_BT_C,1,77,95,374);
    //                        HMI_PictureCopy_xy(BAS_BT_C,sys_var.Screen+1,97,388,97+378,388+80);  //浓度控件
    //                        HMI_TXIconVal(VAR_BT_C,sys_var.work_sta);   //切换触控屏负压指示
    //                        HMI_TXIconVal(VAR_BT_TC,2*sys_var.Language+sys_var.work_sta);   //浓度字符状态
                            sys_var.Job_step=3;  
                        } 
                        else
                        {
                            Dis_CV_BAS(BAS_BT_C,0,77,95,374);
    //                        HMI_PictureCopy_xy(BAS_BT_C,sys_var.Screen,97,388,97+378,388+80);  //浓度控件
    //                        HMI_TXIconVal(VAR_BT_C,sys_var.work_sta);   //切换触控屏负压指示
    //                        HMI_TXIconVal(VAR_BT_TC,2*sys_var.Language+sys_var.work_sta);   //浓度字符状态
                            Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF ;
                            Valve5 = Valve6 = ON;
                            TIM_Cmd(TIM4, DISABLE);
                            PWM2_OUT(0);

                            RGB_Colour(GREEN);        //开绿灯
                        }
                                       
                    }
                    else if(sys_var.Adc_value[vacuum_v]>130)
                    {
                        if(sys_var.work_sta==1) sys_var.work_sta = 0;
                        Dis_CV_BAS(BAS_BT_C,0,77,95,474);
    //                    HMI_PictureCopy_xy(BAS_BT_C,sys_var.Screen,97,388,97+378,388+80);  //浓度控件
    //                    HMI_TXIconVal(VAR_BT_C,sys_var.work_sta);   //切换触控屏负压指示
    //                    HMI_TXIconVal(VAR_BT_TC,2*sys_var.Language+sys_var.work_sta);   //浓度字符状态
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF ;
                        Valve5 = Valve6 = ON;
                        TIM_Cmd(TIM4, DISABLE);
                        PWM2_OUT(0);

    //                    RGB_Colour(GREEN);        //开绿灯
                    }   

                }
            }
        }
        if(bt_value== BT_BT_Vacuo)      //真空
        {
            if(sys_var.work_sta!=1)  //抽真空结束或未进行
            {
                if(sys_var.Adc_value[vacuum_v]>45)        //
                {
                    sys_var.Vac_Open = ! sys_var.Vac_Open;
                    if(sys_var.Vac_Open)
                    {
                        Dis_CV_BAS(BAS_BT_V,1,78,95,474);
    //                    HMI_PictureCopy_xy(BAS_BT_V,sys_var.Screen+1,96,483,96+378,483+80);  //负压控件
    //                    HMI_TXIconVal(VAR_BT_V,sys_var.Vac_Open);   //切换触控屏负压指示
    //                    HMI_TXIconVal(VAR_BT_TV,2*sys_var.Language+sys_var.Vac_Open);   //压力字符状态
                        sys_var.Job_step=1;       //停止真空
                    }
                    else
                    {
                        Dis_CV_BAS(BAS_BT_V,0,78,95,474);
    //                    HMI_PictureCopy_xy(BAS_BT_V,sys_var.Screen,96,483,96+378,483+80);  //负压控件
    //                    HMI_TXIconVal(VAR_BT_V,sys_var.Vac_Open);   //切换触控屏负压指示
    //                    HMI_TXIconVal(VAR_BT_TV,2*sys_var.Language+sys_var.Vac_Open);   //压力字符状态
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                        Valve5 = Valve6 = ON ;
                        PWM3_OUT(VacCtr_OFF);       //泵
                //                sys_var.Job_step=0;       //停止真空
                    }


                }
                else
                {
                    if(sys_var.Vac_Open==1)sys_var.Vac_Open=0;
                    Dis_CV_BAS(BAS_BT_V,0,78,95,474);
    //                HMI_PictureCopy_xy(BAS_BT_V,sys_var.Screen,96,483,96+378,483+80);  //负压控件
    //                 HMI_TXIconVal(VAR_BT_V,sys_var.Vac_Open);   //切换触控屏负压指示
    //                HMI_TXIconVal(VAR_BT_TV,2*sys_var.Language+sys_var.Vac_Open);   //压力字符状态
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                    Valve5 = Valve6 = ON ;
                    PWM3_OUT(VacCtr_OFF);       //泵
                }
            }
        }
    }
}
//输液袋
void Screen_IFBAG(unsigned short bt_value)
{
    static u8 V_sta=0;    //体积按下状态
    bt_value = bt_value;
    if(bt_value==BT_BG_Work)
    {
        if(input_sta==2)    //输入结束后才允许工作
        {
            if(sys_var.Dosage!=0&&Ready!=0)       //剂量不为0
            {
                sys_var.work_sta = !sys_var.work_sta;
                Dis_SP_BAS(BAS_BG_Work,sys_var.work_sta,598,553);
//                HMI_PictureCopy_xy(BAS_BG_Work,sys_var.Screen+sys_var.work_sta,599,556,599+362,556+88);  //开启暂停控件
//                HMI_TXIconVal(VAR_BG_C,sys_var.work_sta);   //切换触控屏负压指示
//                HMI_TXIconVal(AMT_BG_Work,sys_var.work_sta);
                if(sys_var.work_sta==1)
                {
                    sys_var.Job_step = 1;
                }

            }
        }

    }

    if(sys_var.work_sta==0)    //未开启工作
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
                if(V_sta==0)    //输入的数值是浓度
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
                if(V_sta==1)        //输入的数值是体积123
                {
                    if((num_value[V_sta]*10 + bt_value-BT_BG_0)<1000)   //体积小于1000
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
                if(V_sta==0)    //输入的数值是浓度
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
                        HMI_PictureCopy_xy(BAS_BG_V,sys_var.Screen,179,507,179+252,507+57); //体积
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
                    num_value[0] = 0;  //限定浓度大小为80
                    dis_density(sys_var.work_mode,num_value[0]);//显示浓度
                }
                if(num_value[1]>400)   //体积：0~400ml
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


        case BT_NUM_ET:     //浓度显示框按钮
            if(Ready == 0)
            {
                V_sta = 0;
                input_sta = 1;
                HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen+1,95,313,95+381,313+154);
                            
    //            HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen+1,42,188,42+252,188+173);
                HMI_PictureCopy_xy(BAS_BG_V,sys_var.Screen,179,507,179+252,507+57); //体积
    //            HMI_PictureCopy_xy(BAS_BG_Cnum,S_IFBAG+1,42,188,42+252,188+173);
    //            HMI_PictureCopy_xy(BAS_BG_V,S_IFBAG,162,387,162+158,387+52);        
    //            num_value[0] = 0;
                dis_density(sys_var.work_mode,num_value[0]);
            }
            
            break;
        case BT_BG_Vacuo:       //体积按钮
            if(Ready == 0)
            {
                V_sta = 1;
                input_sta = 1;
                HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen,95,313,95+381,313+154);
    //            HMI_PictureCopy_xy(BAS_BG_Cnum,sys_var.Screen,42,188,42+252,188+173);
                HMI_PictureCopy_xy(BAS_BG_V,sys_var.Screen+1,179,507,179+252,507+57); //体积
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
            sys_var.work_mode = 0;//待机模式
//            if(sys_var.Job_step!=0) Clear();
            HIM_SCR_ID(sys_var.Screen);
//            HMI_PictureCopy_xy(BAS_BG_Cnum,S_IFBAG,42,188,42+252,188+173);
//            HMI_PictureCopy_xy(BAS_BG_V,S_IFBAG,162,387,162+158,387+52);
            break;
        }
    }

}
//臭氧水化
void Screen_O3Hydrate(unsigned short bt_value)
{

    bt_value = bt_value;
    if(bt_value==BT_H_Work)
    {
        if(input_sta==2&&Ready!=0)    //输入结束后才允许工作
        {
            sys_var.work_sta = !sys_var.work_sta;
            if(sys_var.work_sta)
            {
               sys_var.Job_step = 1;
            }
            Dis_SP_BAS(BAS_H_Work,sys_var.work_sta,598,553);
//            HMI_PictureCopy_xy(BAS_H_Work,sys_var.Screen+sys_var.work_sta,597,552,597+361,552+90);  //开启暂停控件
//            HMI_TXIconVal(AMT_H_Work,sys_var.work_sta);
            sys_var.H2O_countdowm ++;
            if(sys_var.H2O_countdowm==3)sys_var.H2O_countdowm=1;
        }
    }
    if(sys_var.work_sta==0)    //未开启工作
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
                    num_value[0] = 0;  //限定浓度大小为80
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
        case BT_NUM_ET:     //浓度显示框按钮
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
//负压罩杯
void Screen_SuctionCup(unsigned short bt_value)
{
    bt_value = bt_value;

    if(bt_value==BT_SC_Work)
    {
        if(input_sta==2&&Ready!=0)        //输入结束
        {

            sys_var.work_sta = !sys_var.work_sta;
            Dis_SP_BAS(BAS_SC_Work,sys_var.work_sta,598,553);
//            HMI_PictureCopy_xy(BAS_SC_Work,sys_var.Screen+sys_var.work_sta,598,553,598+361,553+90);  //开启暂停控件
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

    if(sys_var.work_sta==0)    //未开启工作
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
                    num_value[0] = 0;  //限定浓度大小为80
                    dis_density(sys_var.work_mode,num_value[0]);
                }
                else
                {
                    Ready = !Ready;
                    HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                    if(input_sta==1)
                    {
                        HMI_PictureCopy_xy(BAS_SC_Cnum,sys_var.Screen,98,283,98+373,283+148);  //数字显示框 
//                        HMI_PictureCopy_xy(BAS_SC_Cnum,S_SuctionCup,53,158,53+280,258+168);
                        sys_var.Density = num_value[0];
                        input_sta = 2;
                    }
                }
            }
            break;

        case BT_NUM_ET:     //浓度显示框按钮
            if(Ready!=1)
            {
                input_sta = 1;
    //            num_value[0] = 0;
                dis_density(sys_var.work_mode,num_value[0]);
                HMI_PictureCopy_xy(BAS_SC_Cnum,sys_var.Screen+1,98,283,98+373,283+148);  //数字显示框 
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
                HMI_PictureCopy_xy(BAS_SC_Cnum,sys_var.Screen,98,283,98+373,283+148);  //数字显示框 
                HMI_PictureCopy_xy(BAS_SC_Cnum,S_SuctionCup,53,158,53+280,258+168); //浓度输入框复位
                
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
                printf("负压设定大小：%d\r\n",sys_var.Set_vac);
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
                printf("负压设定大小：%d\r\n",sys_var.Set_vac);
            }
        }
//    }

}
//定量供气
void Screen_Ration(unsigned short bt_value)
{

    static u8 V_sta = 0;
    bt_value = bt_value;
    if(bt_value==BT_RT_Work)
    {
        if(input_sta==2&&Ready!=0)    //输入结束后才允许工作
        {
            sys_var.work_sta = !sys_var.work_sta;
            Dis_SP_BAS(BAS_RT_Work,sys_var.work_sta,598,553);
//            HMI_PictureCopy_xy(BAS_RT_Work,sys_var.Screen+sys_var.work_sta,599,558,599+362,558+84);  //开启暂停控件
//            HMI_TXIconVal(AMT_RT_Work,sys_var.work_sta);
            if(sys_var.work_sta==1)sys_var.Job_step = 1;

        }

    }
    if(sys_var.work_sta==0)    //未开启工作
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
                if(V_sta==0)    //输入的数值是浓度
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
                if(V_sta==1)        //输入的数值是体积  1234
                {
                    if((num_value[V_sta]*10 +bt_value-BT_RT_0)<10000)  //体积最大9999
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
                if(V_sta==0)    //输入的数值是浓度
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
                    num_value[0] = 0;  //限定浓度大小为80
                    dis_density(sys_var.work_mode,num_value[0]);
                }
                else
                {
                    Ready = !Ready;
                    HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                    if(input_sta==1)
                    {
                        HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen,98,278,96+376,278+155);  //数字显示框
                        HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen,181,475,181+248,475+44);  //体显示框
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
        case BT_NUM_ET:     //浓度显示框按钮
            if(Ready!=1)
            {
                input_sta = 1;
                V_sta = 0;
    //            num_value[0] = 0;
                HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen+1,98,278,96+376,278+155);  //数字显示框
                HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen,181,475,181+248,475+44);  //体显示框
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
//            if(sys_var.Job_step!=0) Clear();        //自清洁
            HIM_SCR_ID(sys_var.Screen);
            HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen,98,278,96+376,278+155);  //数字显示框
            HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen,181,475,181+248,475+44);  //体显示框
//            HMI_PictureCopy_xy(BAS_RT_Cnum,S_Ration,35,167,35+338,167+240);
//            HMI_PictureCopy_xy(BAS_RT_V,S_Ration,182,427,182+219,427+85);
            break;

        case BT_RT_V:     //体积按钮
            if(Ready!=1)
            {
                V_sta=1;
                input_sta = 1;
                HMI_PictureCopy_xy(BAS_RT_Cnum,sys_var.Screen,98,278,96+376,278+155);  //数字显示框
                HMI_PictureCopy_xy(BAS_RT_V,sys_var.Screen+1,181,475,181+248,475+44);  //体显示框
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
//注射器
void Screen_Injector(unsigned short bt_value)
{

    bt_value = bt_value;

    if(bt_value==BT_IJ_Work)
    {
        if(input_sta==2&&Ready!=0)    //输入结束后才允许工作
        {
            sys_var.work_sta = !sys_var.work_sta;
            Dis_SP_BAS(BAS_IJ_Work,sys_var.work_sta,598,553);
//            HMI_PictureCopy_xy(BAS_IJ_Work,sys_var.Screen+sys_var.work_sta,600,558,600+359,558+86);  //开启暂停控件
//            HMI_TXIconVal(AMT_IJ_Work,sys_var.work_sta);
            if(sys_var.work_sta==1) sys_var.Job_step = 1;

        }

    }
    if(sys_var.work_sta==0)    //未开启工作
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
                num_value[0] = 0;  //限定浓度大小为80
                dis_density(sys_var.work_mode,num_value[0]);
            }
            else
            {
                Ready = !Ready;
                HMI_TXIconVal(VAR_SR,sys_var.Language+Ready*6);
                if(input_sta==1)
                {
                    HMI_PictureCopy_xy(BAS_IJ_Cnum,sys_var.Screen,98,352,98+376,352+217);  //数字显示框
//                        HMI_PictureCopy_xy(BAS_IJ_Cnum,S_Injector,34,168,34+341,168+290);
                    sys_var.Density = num_value[0];
                    input_sta = 2;
                }
//                
            }
            break;
        case BT_NUM_ET:     //浓度显示框按钮
            if(Ready!=1)
            {
                input_sta = 1;
    //            num_value[0] = 0;
                HMI_PictureCopy_xy(BAS_IJ_Cnum,sys_var.Screen+1,98,352,98+376,352+217);  //数字显示框
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
//            if(sys_var.Job_step!=0) Clear();   //自清洁
            HIM_SCR_ID(sys_var.Screen);
            HMI_PictureCopy_xy(BAS_IJ_Cnum,sys_var.Screen,98,352,98+376,352+217);  //数字显示框
//            HMI_PictureCopy_xy(BAS_IJ_Cnum,S_Injector,34,168,34+341,168+290);
            break;
        }
    }
}
//设置界面
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
        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,180,282,180+296,282+47);    //账号输入框
        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,181,370,181+294,370+50);      //密码输入框

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
//语言界面
void Screen_Language(unsigned short bt_value)
{
    
    bt_value = bt_value;
    switch(bt_value)
    {
    case BT_L_English:      //英
        New_language = Engliah;
        Deal_Language(New_language);
        break;
    case BT_L_Deutsch:      //德
        New_language = Deutush;
        Deal_Language(New_language);
        break;
    case BT_L_Espanol:  //西
        New_language = Espanol;
        Deal_Language(New_language);
        break;
    case BT_L_Pycckn:   //俄
        New_language = Pyccknn;
        Deal_Language(New_language);
        break;
    case BT_L_Francais: //法
        New_language = Francaise;
        Deal_Language(New_language);
        break;
    case BT_L_Chinese:  //中
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

//    printf("语言%d\r\n",language);
}






//管理员界面
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
        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen+1,180,282,180+296,282+47);    //账号输入框
        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,181,370,181+294,370+50);      //密码输入框

//        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen+1,141,167,141+188,167+62);    //账号输入框
//        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,141,279,141+188,279+62);      //密码输入框
        break;
    case BT_AM_Pswd:
        sta_enter = 2;
        len_enter = 0;
        Str_memset(pswd_enter,0,6);
        HMI_TXStrToEdit(TXT_AM_Pswd,pswd_enter,8);
        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,180,282,180+296,282+47);    //账号输入框
        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen+1,181,370,181+294,370+50);      //密码输入框

//        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,141,167,141+188,167+62);
//        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen+1,141,279,141+188,279+62);
        break;
    case BT_AM_Login:
        sta_enter = 0;
        len_enter = 0;
        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,180,282,180+296,282+47);    //账号输入框
        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,181,370,181+294,370+50);      //密码输入框

    
//        HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,141,167,141+188,167+62);    //账号输入框
//        HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,141,279,141+188,279+62);
        if(compare_array(user_enter,"002",3)==1)
        {
            if(compare_array(pswd_enter,"963215",6)==1)
            {
                sys_var.Screen = S_ProSet +8 * sys_var.Language;
                HMI_TXStrToEdit(TXT_CK_C,"     ",8);
                HMI_TXStrToEdit(TXT_CK_P,"     ",8);
                HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,179,277,179+296,277+54);    //账号输入框
                HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,180,372,180+295,372+53);      //密码输入框
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
            HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,180,282,180+296,282+47);    //账号输入框
            
//            HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,179,277,179+296,277+54);    //账号输入框
//            HMI_PictureCopy_xy(BAS_AM_User,sys_var.Screen,141,167,141+188,167+62);    //账号输入框
        }
        if(sta_enter==2)
        {
            len_enter = 0;
            sta_enter = 0;  
            HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,181,370,181+294,370+50);      //密码输入框
            
//            HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,180,372,180+295,372+53);      //密码输入框
//            HMI_PictureCopy_xy(BAS_AM_Pswd,sys_var.Screen,141,279,141+188,279+62);    //账号输入框
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
//工程参数设置
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
            TIM_Cmd(TIM4, ENABLE);      //开启PWM输出
            PWM2_OUT(C_P_data[enter_c-1]);
            
            printf("开启制臭氧\r\n");
            printf("C=%d  P =%d",enter_c,C_P_data[enter_c-1]);
        }
        else
        {
//            HMI_PictureCopy_xy(BAS_CK_Check,sys_var.Screen,163,373,163+141,373+54);
            Valve1 = Valve2 = Valve3 =OFF;
            Valve4 = Valve5 = Valve6 = Valve7 = OFF;
            TIM_Cmd(TIM4, DISABLE);      //开启PWM输出
            
            PWM2_OUT(0);
            printf("关闭臭氧\r\n");
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
                    HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen+1,179,277,179+296,277+54);    //账号输入框
                    HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,180,372,180+295,372+53);      //密码输入框
//                    HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen+1,141,167,141+188,167+62);    //浓度输入框
//                    HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,141,279,141+188,279+62);      //参数输入框
                }
                break;
            case BT_CK_P:
                sta_enter = 2;
                enter_p = 0;
                HMI_ShowNumber_int(TXT_CK_P,enter_p,4,8);
            
                HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,179,277,179+296,277+54);    //账号输入框
                HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen+1,180,372,180+295,372+53);      //密码输入框
//                HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,141,167,141+188,167+62);    //浓度输入框
//                HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen+1,141,279,141+188,279+62);      //参数输入框

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
                HMI_PictureCopy_xy(BAS_CK_P,sys_var.Screen,181,372,180+295,372+53);      //密码输入框
                HMI_PictureCopy_xy(BAS_CK_C,sys_var.Screen,179,275,179+296,275+54);    //账号输入框

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

//设备信息界面
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

//测试界面
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






//错误报警界面
void Screen_Error(unsigned short bt_value)      //测试界面 
{
    bt_value = bt_value;
    if(bt_value==BT_ERR_Eixt)
    {
        sys_var.Error = 0;
        sys_var.Screen = S_HOME+74 + 2 * sys_var.Language;
        HIM_SCR_ID(sys_var.Screen);
    }
}



