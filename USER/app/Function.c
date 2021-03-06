/*
* 版权所有(C): 黄文基 深圳科医仁科技发展有限公司 2020.5
* 文档说明：模块功能函数
*
*/

#include "Function.h"

//显示臭氧浓度数值
void dis_density(u8 mode, u8 nums)
{
    mode =mode;
    HMI_TXIconVal(VAR_Tens,(unsigned short)nums/10);
    HMI_TXIconVal(VAR_units,(unsigned short)nums%10);
    
}

//三氧水化模式下倒计时显示
//times：显示的倒计时 单位s
void dis_countdown(u16 times)
{
    char str[2];
    u8 min=times/60,sec=times%60;
    str[0] = min/10+'0';
    str[1] = min%10+'0';
    HMI_TXStrToEdit(TXT_H_Min,str,5);

    str[0] = sec/10+'0';
    str[1] = sec%10+'0';
    HMI_TXStrToEdit(TXT_H_Sec,str,5);
}
//真空瓶界面压力条显示
void dis_vac_bar(u8 vac_value)
{
    u16 pic_size=0;
    if(vac_value<=38)
        vac_value = 38;
    
    pic_size = map(vac_value,38,140,0,320); 
    printf("剪切大小：%d\r\n",(int)pic_size);
    HMI_PictureCopy_xy(BAS_BT_Vbar,S_IFBottle+1,99,588,124+pic_size,588+35);  //压力条
//    HMI_PictureCopy_xy(BAS_BT_Vbar,S_IFBottle+1,39+vac_value,449,39+260,450+43);
}
//罩杯界面压力条显示
void dis_vac_bar2(u8 vac_value)
{
    u16 value = 0;
    if(vac_value<50)vac_value = 50;
    if(vac_value>100)vac_value = 100;
    value = map(vac_value,50,100,0,351);
    HMI_PictureCopy_xy(BAS_SC_Vbar,S_SuctionCup+1,39,449,39+value,450+43);
}

//负压罩杯模式下负压大小调节
//负压大小0-10
void Adj_vac_value(u8 vac)
{
    HMI_PictureCopy_xy(BAS_SC_Vbar,S_SuctionCup+1,39+351-vac*35,450,39+351,450+43);
}

//处理语言界面控件显示状态变化
void Deal_Language(u8 Language)
{
    static u8 old_language = 254;        //初始化一个语言不可能的值
    if(Language != old_language)
    {
        switch(Language)
        {
        case Engliah:
            HMI_PictureCopy_xy(BAS_L_English+0x10*old_language,S_Language+1,0,0,0,0);
            HMI_PictureCopy_xy(BAS_L_English,S_Language+1,178,168,178+291,168+89);
            break;
        case Deutush:
            HMI_PictureCopy_xy(BAS_L_English+0x10*old_language,S_Language+1,0,0,0,0);
            HMI_PictureCopy_xy(BAS_L_Deutsch,S_Language+1,560,172,560+288,171+79);
            break;
        case Espanol:
            HMI_PictureCopy_xy(BAS_L_English+0x10*old_language,S_Language+1,0,0,0,0);
            HMI_PictureCopy_xy(BAS_L_Espanol,S_Language+1,178,283,178+294,283+78);
            break;
        case Pyccknn:
            HMI_PictureCopy_xy(BAS_L_English+0x10*old_language,S_Language+1,0,0,0,0);
            HMI_PictureCopy_xy(BAS_L_Pycckn,S_Language+1,559,283,599+287,283+78);
            break;
        case Francaise:
            HMI_PictureCopy_xy(BAS_L_English+0x10*old_language,S_Language+1,0,0,0,0);
            HMI_PictureCopy_xy(BAS_L_Francais,S_Language+1,178,388,178+289,388+84);
            break;
        case Chinese:
            HMI_PictureCopy_xy(BAS_L_English+0x10*old_language,S_Language+1,0,0,0,0);
            HMI_PictureCopy_xy(BAS_L_Chinese,S_Language+1,560,391,560+288,391+79);
            break;

        }
        old_language = Language;
    }
}

void Dis_CV_BAS(u16 addr,u8 sta,u16 PageID,u16 S_x,u16 E_y)
{
    if(sta!=1)
    {
        HMI_PictureCopy_S_T_xy(addr,PageID,5,0+100*sys_var.Language,5+382,100+100*sys_var.Language,S_x,E_y);
    }
    else HMI_PictureCopy_S_T_xy(addr,PageID,405,0+100*sys_var.Language,405+382,100+100*sys_var.Language,S_x,E_y);
   
}
void Dis_SP_BAS(u16 addr,u8 sta,u16 S_x,u16 E_y)
{
    if(sta!=1)
    {
        HMI_PictureCopy_S_T_xy(addr,79,37,46+110*sys_var.Language,37+362,46+95+110*sys_var.Language,S_x,E_y);
    }
    else HMI_PictureCopy_S_T_xy(addr,79,441,48+109*sys_var.Language,441+362,48+95+109*sys_var.Language,S_x,E_y);   
}
    
//自清洁
void Clear(void)
{
    sys_var.clear = 1;
    Clear1();
    Clear2();
    Clear3();
    Clear4();
    Clear5();
    sys_var.clear = 0;
}

void Clear1(void)
{
    u8 i = 0,time=0;
    printf("Clear1 排气start\r\n");
    Valve4 = Valve6 = Valve7 = ON;
    PWM3_OUT(VacCtr_ON);
     Valve1 = Valve2 = Valve3 = Valve5 = OFF;
    while(1)
    {
        i++;
        if(i>10)
        {
            i=0;
//            LED_G = !LED_G;//绿灯闪 1s
            time++;
            if(sys_var.Screen==S_Welcome)
            {
                if(time<7)
                {
                    HMI_TXIntToEdit(ED_Ver_E,5+time*2);
                    HMI_PictureCopy_xy(BAS_W_E,S_Welcome+1,16,621,16+45+time*18,621+26);
                }
            }
        }

        if(((int)(sys_var.Adc_value[vacuum_v] )) <= 60)  //50KPa//负压达到-50KPa时自清洁1结束
        {
//            SV17F_MP3_Specify(11);        //真空提醒
            sys_var.Job_step = 1;
            
            if(sys_var.Screen==S_Welcome)
            {
                HMI_TXIntToEdit(ED_Ver_E,sys_var.Job_step*20);
                HMI_PictureCopy_xy(BAS_W_E,S_Welcome+1,16,621,16+9*20,621+26);
            }
            printf("Clear1 排气结束\r\n");
//            RGB_Colour(GREEN);      //开绿灯
            break; //
        }
        delay_ms(50);
    }

}
void Clear2(void)
{
    u8 i=0,time=0;

    printf("Clear2 填充臭氧 start\r\n");
    Valve1 = Valve2 = Valve4 = Valve6 = ON;
    PWM3_OUT(VacCtr_OFF);
    Valve3 = Valve5 = Valve7 = OFF;
    TIM_Cmd(TIM4, ENABLE);  //开臭氧
    PWM2_OUT(map(0,0,80,MIN_PULSE,MAX_PULSE));
    while(1)
    {
        i++;
        if(i>10)
        {
            i=0;
            time++;
            if(time<10)
            {
                
                if(sys_var.Screen==S_Welcome)
                {
                    HMI_TXIntToEdit(ED_Ver_E,sys_var.Job_step*20+time*2);
                    HMI_PictureCopy_xy(BAS_W_E,S_Welcome+1,16,621,16+180+time*18,621+26);
                }
            }
        }

        if(((int)(sys_var.Adc_value[vacuum_v] )) >= 100)  //常压100KPa
        {
            sys_var.Job_step = 2;
            
            if(sys_var.Screen==S_Welcome)
            {
                HMI_TXIntToEdit(ED_Ver_E,sys_var.Job_step*20-1);
                HMI_PictureCopy_xy(BAS_W_E,S_Welcome+1,16,621,16+360,621+26);
            }
            printf("Clear2 达到常压 \r\n");
            break;
        }   
        delay_ms(50);
    }
}
void Clear3(void)
{
    u8 i=0,time = 0;
    printf("Clear3 10S臭氧杀毒\r\n");
    Valve4 = Valve6 = ON;
    PWM3_OUT(VacCtr_OFF);
    Valve1 = Valve2 = Valve3 = Valve5 = Valve7 = OFF;
    TIM_Cmd(TIM4, ENABLE);  //开臭氧
    PWM2_OUT(map(0,0,80,MIN_PULSE,MAX_PULSE));
    while(1)
    {
        i++;
        if(i>10)
        {
            i=0;
            time ++;
//            LED_G = !LED_G;//绿灯闪 1s
            time++;
            
            if(sys_var.Screen==S_Welcome)
            {
                HMI_TXIntToEdit(ED_Ver_E,sys_var.Job_step*20+time*2);
                HMI_PictureCopy_xy(BAS_W_E,S_Welcome+1,16,621,16+360+time*18,621+26);
            }

        }
        if(time==10)
        {
            sys_var.Job_step = 3;
            
            if(sys_var.Screen==S_Welcome)
            {
                HMI_TXIntToEdit(ED_Ver_E,sys_var.Job_step*20);
                HMI_PictureCopy_xy(BAS_W_E,S_Welcome+1,16,621,16+540,621+26);
            }
            printf("Clear3 杀毒结束\r\n");
//            RGB_Colour(GREEN);      //开绿灯
            break;  //10s后退出
        }
        delay_ms(50);
    }
}
void Clear4(void)
{
    u8 i=0,time=0;
    printf("Clear4 排出管内气\r\n");
    Valve4 = Valve6 = Valve7 = ON;
    PWM3_OUT(VacCtr_ON);
    Valve1 = Valve2 = Valve3 = Valve5 = OFF;
    TIM_Cmd(TIM4, ENABLE);  //开臭氧
    PWM2_OUT(map(30,0,80,MIN_PULSE,MAX_PULSE));
    while(1)
    {
        i++;
        if(i>10)
        {
            i=0;
//            LED_G = !LED_G;//绿灯闪 1s
            time++;
            if(time<10)
            {
                
                if(sys_var.Screen==S_Welcome)
                {
                    HMI_TXIntToEdit(ED_Ver_E,sys_var.Job_step*20+time*2);
                    HMI_PictureCopy_xy(BAS_W_E,S_Welcome+1,16,621,16+540+time*18,621+26);
                }
            }
        }
        if(((int)(sys_var.Adc_value[vacuum_v] )) <= 50)  //50KPa //负压达到-50KPa时自清洁1结束
        {
            
            sys_var.Job_step = 4;
            
            if(sys_var.Screen==S_Welcome)
            {
                HMI_TXIntToEdit(ED_Ver_E,sys_var.Job_step*20);
                HMI_PictureCopy_xy(BAS_W_E,S_Welcome+1,16,621,16+720,621+26);
            }
//            RGB_Colour(GREEN);      //开绿灯
            printf("Clear4 达到真空\r\n");
            break; //
        }
        delay_ms(50);
    }
}
void Clear5(void)
{
    u8 i = 0 ;
    printf("Clear5 关闭臭氧 start\r\n");
    PWM3_OUT(VacCtr_OFF);
    Valve1 = Valve2 = Valve3 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
    TIM_Cmd(TIM4, DISABLE);  //开臭氧
    PWM2_OUT(0);
//    LED_G = 1;//绿灯常亮
    sys_var.Job_step = 5;
    delay_ms(500);
//    SV17F_MP3_Specify(11);        //真空提醒
    if(sys_var.Screen==S_Welcome)
    {
        HMI_TXIntToEdit(ED_Ver_E,sys_var.Job_step*20-1);
        HMI_PictureCopy_xy(BAS_W_E,S_Welcome+1,16,621,16+900,621+26);
    }
//    RGB_Colour(GREEN);      //开绿灯
    printf("Clear5 清洁结束\r\n");
}




