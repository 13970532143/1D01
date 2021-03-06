

#include "test.h"
#include "Function.h"
#include "common.h"
#define Volume_Tims_K    1              //定量供气，体积与时间的关系


OS_TMR   * tmr1;
u8 err=0;
    
    
void tmr1_callback(OS_TMR *ptmr,void *p_arg)        //软件定时,用于计算制冷时间
{

    if(sys_var.H2O_countdowm==1&&sys_var.Work_Down!=1)    //臭氧水化开始倒计时
    {
        sys_var.Countdown--;
        dis_countdown(sys_var.Countdown);       //显示倒计时
        if(sys_var.Countdown==0)
        {
            sys_var.Job_step=3;
            sys_var.H2O_countdowm = 0;      //关闭臭氧水化倒计时
            sys_var.Countdown = 600;
        }
    }
    if(sys_var.Work_Down==1)
    {
        sys_var.work_down_time --;
        HMI_TXIntToEdit(ED_Down_time,sys_var.work_down_time);
        if(sys_var.work_down_time==0)
        {
            sys_var.Work_Down = 0;
            
        }
    }
    
    

}

//定时器2中断服务程序
void TIM2_IRQHandler(void)   //TIM3中断
{
    static u16 Volume=0,time=0;      //体积,时间
    static u8 old_work_mod = 0;
    if(old_work_mod!=sys_var.work_mode)     //工作模式改变后，进行变量清零
    {
        old_work_mod = sys_var.work_mode;
        time = 0;
        Volume=0;
    }
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx更新中断标志 
		if(sys_var.work_mode==infusionBag)      //输液袋模式
        {
            if(sys_var.Job_step==2&&(sys_var.Work_Down!=1))
            {
                time++;
                 Volume = Volume_Tims_K*time;
                if(Volume>=sys_var.O3bulk)      //输出的臭氧达到设定的臭氧体积，停止臭氧输出，清零计数器
                {
                    sys_var.Job_step = 3;
                    
                    time = 0;
                    Volume = 0;

                }
            }
        }
        if(sys_var.work_mode==ration)       //定量供气模式下
        {
            if(sys_var.work_sta==1&&(sys_var.Work_Down!=1))     //处于臭氧输出工作状体
            {
                time++;                 //计数器工作
                Volume = Volume_Tims_K*time;
                if(Volume>=sys_var.O3bulk)      //输出的臭氧达到设定的臭氧体积，停止臭氧输出，清零计数器
                {
                    sys_var.Job_step = 3;
                    time = 0;
                    Volume = 0;

                }
            }
            else time = 0;      //停止了臭氧输出，计数器清零
        }
    }
} 

void ctr_task(void *pdata)
{

//    u8 oled_Set_vac=0;
    u16 pulse,cnt=0,time=0;
    u8 old_work_mod = 255;
    u8 oled_work_sta = 255;
    u8 oled_Density = 255;  //之前的臭氧浓度
    u16 value =0;
      
    pdata = pdata;
    tmr1=OSTmrCreate(0,10,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,0,"tmr1",&err);	//1000mss执行一次
    OSTmrStart(tmr1,&err);//启动软件定时器1
//    
    while(1)
    {
        if(old_work_mod!=sys_var.work_mode)     //工作模式改变后，进行变量清零
        {
            old_work_mod = sys_var.work_mode;      
            time = 0;
            cnt=0;
            sys_var.Job_step = 0;
        }
        if(oled_work_sta!=sys_var.work_sta)
        {
            oled_work_sta=sys_var.work_sta;
            if(sys_var.Screen <= S_ProSet)      //参数修改界面除外
            {

                if(sys_var.work_sta!=1)     //未制臭氧状态
                {
                    sys_var.Work_Down = 0;
                    if(sys_var.work_down_time!=0)
                    {
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                        
                        TIM_Cmd(TIM4, DISABLE);
                        PWM2_OUT(0);
                    }
                    sys_var.work_down_time = 5;
                    HMI_TXIntToEdit(ED_Down_time,sys_var.work_down_time);                    
                }
                else        //开启制臭氧
                {
                    if(oled_Density != sys_var.Density)     //浓度发生改变后，需要重新开启5s倒计时
                    {
                        oled_Density = sys_var.Density;
                        sys_var.Work_Down = 1;
                        sys_var.work_down_time = 5;
                    }
                        
                    HMI_TXIntToEdit(ED_Down_time,sys_var.work_down_time);
                    Valve1 = Valve2 = Valve4 = Valve6 = Valve7 = ON;
                    Valve3 = Valve5 = OFF;
                    
                    TIM_Cmd(TIM4, ENABLE);
//                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    PWM2_OUT(0);
                }
            }
            printf("sys_var.Work_Down=%d\r\n",sys_var.Work_Down);
        }
        switch(sys_var.work_mode)
        {
            case O3Bag:     //三氧套袋  --1
            
            if(sys_var.Vac_Open==1)//开负压，在真空口抽真空，
            {
                
                if(sys_var.Job_step==1)     //开泵
                {
                   
                    Valve1 = Valve2 = Valve2 = Valve4 = OFF;
                    Valve5 = Valve6 = Valve7 =  ON;
                    PWM3_OUT(VacCtr_ON);       //泵
                    sys_var.Job_step = 2;
                    printf("开泵\r\n");
                   
                }
                if(sys_var.Adc_value[vacuum_v]<80)       //达到80Kpa
                {
                    delay_ms(500);  //短暂延时
                    PWM3_OUT(VacCtr_OFF);       //泵
                    sys_var.Vac_Open = 0;
                    SV17F_MP3_Specify(11);      //真空语音提示
                    Dis_CV_BAS(BAS_OB_V,0,78,95,522);
                    sys_var.Job_step = 3;
                    printf("达到真空\r\n");
                }
            }
            
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1)) //开臭氧
            {
                
                if(sys_var.Job_step == 3)         //在真空状态下
                {
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve6 = ON;
                    Valve3 = Valve7 =  OFF;
                    TIM_Cmd(TIM4, ENABLE);  //开臭氧
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
//                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    PWM2_OUT(0); 
                    sys_var.Job_step = 4;
                    printf("开臭氧\r\n");
                    
                }
                if(sys_var.Job_step==4)
                {
                     if(sys_var.Adc_value[vacuum_v]>=135)       //套袋里面的气压大于135KPa时关闭制臭氧
                    {
                        TIM_Cmd(TIM4, DISABLE);  //关臭氧
                        PWM2_OUT(0);
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                        Valve5 = Valve6 = ON;
                        SV17F_MP3_Specify(12);      //充满语音提示

                        sys_var.Job_step = 5;
                        sys_var.work_sta=0;
                        Dis_CV_BAS(BAS_OB_C,0,77,95,414);

                        printf("充满，结束\r\n");
                    }
                
                }       
                
            }
            break;
        case infusionBottle:    //输液瓶 --1
            if(sys_var.Vac_Open==1)//开负压，在真空口抽真空，
            {
                if(sys_var.Job_step==1)     //开阀开泵，开始抽真空
                {
                    Valve1 = Valve2 = Valve3 = Valve4 = OFF;
                    Valve5 = Valve6 = Valve7 = ON ;
                    PWM3_OUT(VacCtr_ON);       //开泵
                    sys_var.Job_step=2;
                    printf("开泵\r\n");
                    
                }
                if(sys_var.Adc_value[vacuum_v]<40)        //达到真空状态
                {
                    delay_ms(200);  //短暂延时
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                    Valve5 = Valve6 = ON ;
                    PWM3_OUT(VacCtr_OFF);       //泵
                    sys_var.Vac_Open = 0;
                    sys_var.Job_step=3;
                    SV17F_MP3_Specify(11);      //真空语音提示
                    Dis_CV_BAS(BAS_BT_V,0,78,95,474);

                    printf("达到真空\r\n");
                }
            }
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))     //制臭氧操作
            {
                
                if(sys_var.Job_step==3)     //开启电磁阀，制取臭氧
                {
                    Valve3 = Valve7 = OFF;
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve6 = ON ;
                    PWM3_OUT(VacCtr_OFF);       //泵
                    sys_var.Job_step=4;
                    TIM_Cmd(TIM4, ENABLE);
//                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    PWM2_OUT(0);
                    printf("开启制臭氧\r\n");
                    
                }
                
                
               if(sys_var.Adc_value[vacuum_v]>135)    //充满
                {
//                     
                    delay_ms(500);
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF ;
                    Valve5 = Valve6 = ON;
                    sys_var.Job_step=6; //真空瓶内负压达到130Kpa
//                    RGB_Colour(GREEN);
                    TIM_Cmd(TIM4, DISABLE);     //关制臭氧
                    PWM2_OUT(0);
                    sys_var.work_sta = 0;  
                    Dis_CV_BAS(BAS_BT_C,0,77,95,374);

                    printf("达到关臭氧\r\n");
                    printf("Job_step=%d",sys_var.Job_step);
                
                }
            }
            else
            {
                if(sys_var.Job_step==6)     //回血阶段
                {
//                        sys_var.Adc_value[vacuum_v] = Get_vac_value();
                    if(sys_var.Adc_value[vacuum_v]<105)   //
                    {
                        Valve5 = ON;
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF ;
                        Valve6 = OFF;
                        sys_var.Job_step = 7;
                        
                        printf("回血结束\r\n");

                    }
//                    Clear();
                }
            }
            time++;
            if(time > 10)
            {
                dis_vac_bar(sys_var.Adc_value[vacuum_v]);     //显示压力条
                time = 0;
                
            }
            break;
        case infusionBag:       //输液袋 --1
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {
               
                if(sys_var.Job_step==1)     //
                {
                    Valve1 = Valve2 = Valve3 =ON;
                    Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, ENABLE);      //开启PWM输出
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
//                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    PWM2_OUT(0);
                    sys_var.Job_step=2;     //开始输出臭氧
                    
//                    RGB_Colour(BLUE);      //关灯
                    printf("开启制臭氧\r\n");
                }
                if(sys_var.Job_step==3)
                {
//                    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
                    Valve3 = ON;
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);     //关闭PWM输出
                    PWM2_OUT(0);
//                    RGB_Colour(GREEN);      //开绿灯
                    sys_var.work_sta = 0;
                    Dis_SP_BAS(BAS_BG_Work,sys_var.work_sta,598,553);
                    sys_var.Job_step = 4;
                    printf("达到输出体积，关闭制臭氧\r\n");
                }
            }
            else
            {
                if(sys_var.Job_step > 1)
                {
                    sys_var.Job_step = 1;
////                    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
                    Valve3 = ON;
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);     //关闭PWM输出
                    PWM2_OUT(0);
                }
//                RGB_Colour(GREEN);      //开绿灯
            }
            break;
        case O3Hydrate:     //臭氧水化 --1
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {

                if(sys_var.Job_step==1)
                {
                    PWM3_OUT(VacCtr_OFF);
                    Valve1 = Valve2 = Valve4 = Valve5 = ON;
                    Valve3 = Valve6 = Valve7 =  OFF;
                    TIM_Cmd(TIM4,DISABLE);  //开臭氧
//                    pulse = map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE);
                    PWM2_OUT(0);
////                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    sys_var.Job_step=2;
                    printf("开制臭氧\r\n");
                }
                if(sys_var.Job_step == 3)   //臭氧倒计时结束
                {
//                    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
                    sys_var.work_sta =0;
                    Dis_SP_BAS(BAS_H_Work,sys_var.work_sta,598,553);
//                    HMI_PictureCopy_xy(BAS_H_Work,sys_var.Screen+sys_var.work_sta,597,552,597+361,552+90);  //开启暂停控件
//                    HMI_TXIconVal(AMT_H_Work,sys_var.work_sta);
                    sys_var.Job_step=4;
                    Valve5 =ON;
                    Valve1 = Valve2 = Valve4 = Valve3  = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);  //关臭氧
                    PWM2_OUT(0);
                    printf("倒计时结束\r\n");
                    SV17F_MP3_Specify(11);
                    delay_ms(500);
                    SV17F_MP3_Specify(11);
                    delay_ms(500);
                    SV17F_MP3_Specify(11);
                }
            }
            else
            {
                if(sys_var.Job_step > 1)
                {
//                    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
                    sys_var.Job_step=1;
                    Valve3 = ON;
                    Valve1 = Valve2 = OFF;
                    Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);  //关臭氧
                    PWM2_OUT(0);
//                    RGB_Colour(GREEN);
                    printf("关制臭氧\r\n");
                }

            }
            break;
        case suctionCup:    //负压罩杯  --1
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {
                if(sys_var.Job_step==1)     //开始制臭氧抽真空
                {
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve7 = ON;
                    Valve3 = Valve6 = OFF;
                      
                    TIM_Cmd(TIM4, ENABLE);      //开制臭氧
//                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    PWM2_OUT(0);
                    sys_var.Job_step=4;
                    
                    printf("开制臭氧\r\n");
                    printf("开泵\r\n");

                }
                if(sys_var.Set_vac!=0)      //负压调节
                {
                    Valve6=OFF;
                    Valve7=ON;
                    if(sys_var.Adc_value[vacuum_v]>(100-sys_var.Set_vac*5+2))
                    {
                        PWM3_OUT(500+sys_var.Set_vac*50);
                    }
                    else if(sys_var.Adc_value[vacuum_v]<(100-sys_var.Set_vac*5-2))
                    {
                        delay_ms(500);
                        PWM3_OUT(500);
                    }
                }
                else
                {
                    Valve7=OFF;
                    PWM3_OUT(0);                     
                }
                
            }
            else
            {
                if(sys_var.Job_step == 4)   //先关臭氧
                {
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve7 = ON ;
                    Valve3 = Valve6 = OFF;
                    PWM3_OUT((50+sys_var.Set_vac*50));        //开泵
                    TIM_Cmd(TIM4, DISABLE);      //关制臭氧
                    PWM2_OUT(0);
//                    RGB_Colour(GREEN);
                    sys_var.Job_step=5;
                    cnt = 0;    //清零计数
                    printf("关制臭氧\r\n");
                    delay_ms(1000);
                    Valve5 = ON;
                    Valve1 = Valve2 = Valve4 =  OFF ;
                    Valve3 = Valve6 = Valve7 = OFF;
                    PWM3_OUT(VacCtr_OFF);        //关泵
                    sys_var.Job_step=6;
//                    SV17F_MP3_Specify(11);
                    printf("关泵\r\n");
                }
            }
            break;
        case ration:        //定量供气
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {

                if(sys_var.Job_step == 1)       //开启臭氧输出
                {
                    sys_var.Job_step = 2;
                    Valve1 = Valve2 = Valve4 = Valve5 =ON;
                    Valve3 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, ENABLE);      //开启PWM输出
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
                    PWM2_OUT(0);
                    printf("开制臭氧\r\n");
                }
                if(sys_var.Job_step == 3)       //输出体积达到要求
                {
                    Valve5 = ON;
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);     //关闭PWM输出
                    
                    PWM2_OUT(0);
                    sys_var.work_sta = 0;
                    sys_var.Job_step = 4;
                    Dis_SP_BAS(BAS_RT_Work,sys_var.work_sta,598,553);
                    printf("达到输出要求\r\n");
                    break;
                }
            }
            else
            {
                if(sys_var.Job_step >1)
                {
                    sys_var.Job_step = 1;
                    Valve3 = ON;
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);     //关闭PWM输出
                    PWM2_OUT(0);
                    printf("关制臭氧\r\n");
                }
            }
            break;
        case injector:      //注射器
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {

                if(sys_var.Job_step == 1)
                {
                    sys_var.Job_step = 2;

                    Valve1 = Valve2 = Valve3 =ON;
                    Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, ENABLE);     //关闭PWM输出
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
                    PWM2_OUT(0);
                    printf("开启制臭氧\r\n");
                }
            }
            else
            {
//                cnt = 0;
                if(sys_var.Job_step > 1)
                {
                    sys_var.Job_step = 1;
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve6 = Valve7 = OFF;
                    Valve5 = ON;
                    TIM_Cmd(TIM4, DISABLE);     //关闭PWM输出
                    PWM2_OUT(0);
//                    RGB_Colour(GREEN);
                    printf("关制臭氧\r\n");
                }
            }
            break;
        default:
            break;
        }
        delay_ms(50);
    }

}

