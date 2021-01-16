

#include "test.h"
#include "Function.h"

#define Volume_Tims_K    1              //���������������ʱ��Ĺ�ϵ


OS_TMR   * tmr1;
u8 err=0;
    
    
void tmr1_callback(OS_TMR *ptmr,void *p_arg)        //������ʱ,���ڼ�������ʱ��
{

    if(sys_var.H2O_countdowm==1&&sys_var.Work_Down!=1)    //����ˮ����ʼ����ʱ
    {
        sys_var.Countdown--;
        dis_countdown(sys_var.Countdown);       //��ʾ����ʱ
        if(sys_var.Countdown==0)
        {
            sys_var.Job_step=3;
            sys_var.H2O_countdowm = 0;      //�رճ���ˮ������ʱ
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
//    if(sys_var.work_mode==O3Bag)       //�����״�ģʽ��
//    {
//        if(sys_var.Job_step==5)     //�����״��������������10���ӵ���ʱ
//        {
//            time++;
//            if(time>=30)        //10���ӵ���ʱ����
//            {
//                sys_var.Job_step = 6; //10���ӵ���ʱ����
//                time=0;
//            }
//        }
//    }
    
    

}

//��ʱ��2�жϷ������
void TIM2_IRQHandler(void)   //TIM3�ж�
{
    static u16 Volume=0,time=0;      //���,ʱ��
    static u8 old_work_mod = 0;
    if(old_work_mod!=sys_var.work_mode)     //����ģʽ�ı�󣬽��б�������
    {
        old_work_mod = sys_var.work_mode;
        time = 0;
        Volume=0;
    }
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx�����жϱ�־ 
		if(sys_var.work_mode==infusionBag)      //��Һ��ģʽ
        {
            if(sys_var.Job_step==2&&(sys_var.Work_Down!=1))
            {
                time++;
                 Volume = Volume_Tims_K*time;
                if(Volume>=sys_var.O3bulk)      //����ĳ����ﵽ�趨�ĳ��������ֹͣ������������������
                {
                    sys_var.Job_step = 3;
                    
                    time = 0;
                    Volume = 0;

                }
            }
        }
        if(sys_var.work_mode==ration)       //��������ģʽ��
        {
            if(sys_var.work_sta==1&&(sys_var.Work_Down!=1))     //���ڳ����������״��
            {
                time++;                 //����������
                Volume = Volume_Tims_K*time;
                if(Volume>=sys_var.O3bulk)      //����ĳ����ﵽ�趨�ĳ��������ֹͣ������������������
                {
                    sys_var.Job_step = 3;
                    time = 0;
                    Volume = 0;

                }
            }
            else time = 0;      //ֹͣ�˳������������������
        }
    }
} 

void ctr_task(void *pdata)
{

//    u8 oled_Set_vac=0;
    u16 pulse,cnt=0,time=0;
    u8 old_work_mod = 255;
    u8 oled_work_sta = 255;
    u8 oled_Density = 255;  //֮ǰ�ĳ���Ũ��
    u16 value =0;
      
    pdata = pdata;
    tmr1=OSTmrCreate(0,10,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,0,"tmr1",&err);	//1000mssִ��һ��
    OSTmrStart(tmr1,&err);//����������ʱ��1
//    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
//    
    while(1)
    {
        if(old_work_mod!=sys_var.work_mode)     //����ģʽ�ı�󣬽��б�������
        {
            old_work_mod = sys_var.work_mode;      
//            sys_var.Work_Down = 2;      //�л�ģʽ�󣬵�һ�ο�������ʱ
            time = 0;
            cnt=0;
            sys_var.Job_step = 0;
        }
        if(oled_work_sta!=sys_var.work_sta)
        {
            oled_work_sta=sys_var.work_sta;
            if(sys_var.Screen <= S_ProSet)      //�����޸Ľ������
            {

                if(sys_var.work_sta!=1)     //δ�Ƴ���״̬
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
                else        //�����Ƴ���
                {
                    if(oled_Density != sys_var.Density)     //Ũ�ȷ����ı����Ҫ���¿���5s����ʱ
                    {
                        oled_Density = sys_var.Density;
                        sys_var.Work_Down = 1;
                        sys_var.work_down_time = 5;
                    }
                        
                    HMI_TXIntToEdit(ED_Down_time,sys_var.work_down_time);
                    Valve1 = Valve2 = Valve4 = Valve6 = Valve7 = ON;
                    Valve3 = Valve5 = OFF;
                    
                    TIM_Cmd(TIM4, ENABLE);
                    PWM2_OUT(Density_P[sys_var.Density-1]);
                }
            }
            printf("sys_var.Work_Down=%d\r\n",sys_var.Work_Down);
        }
        switch(sys_var.work_mode)
        {
            case O3Bag:     //�����״�  --1
            
            if(sys_var.Vac_Open==1)//����ѹ������տڳ���գ�
            {
                
                if(sys_var.Job_step==1)     //����
                {
                    
//                        RGB_Colour(GREEN);      //���̵�
                    Valve1 = Valve2 = Valve2 = Valve4 = OFF;
                    Valve5 = Valve6 = Valve7 =  ON;
                    PWM3_OUT(VacCtr_ON);       //��
                    sys_var.Job_step = 2;
                    printf("����\r\n");
                   
                }
                if(sys_var.Adc_value[vacuum_v]<80)       //�ﵽ80Kpa
                {
                    delay_ms(500);  //������ʱ
                    PWM3_OUT(VacCtr_OFF);       //��
                    sys_var.Vac_Open = 0;
                    SV17F_MP3_Specify(11);      //���������ʾ
                    Dis_CV_BAS(BAS_OB_V,0,78,95,522);
//                    HMI_PictureCopy_xy(BAS_OB_V,sys_var.Screen,97,525,97+381,525+94);  //��ѹ�ؼ�
//                    HMI_TXIconVal(VAR_OB_V,sys_var.Vac_Open);   //�л���������ѹָʾ
//                    HMI_TXIconVal(VAR_OB_TV,2*sys_var.Language+sys_var.Vac_Open);   //�л���������ѹָʾ
                    sys_var.Job_step = 3;

                    printf("�ﵽ���\r\n");
                }
                
                
            }
            
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1)) //������
            {
                
                if(sys_var.Job_step == 3)       //�����״̬��
                {
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve6 = ON;
                    Valve3 = Valve7 =  OFF;
                    TIM_Cmd(TIM4, ENABLE);  //������
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
                    PWM2_OUT(Density_P[sys_var.Density-1]);
//                        RGB_Colour(BLUE);
                    sys_var.Job_step = 4;
                    printf("������\r\n");
                    
                }
                if(sys_var.Job_step==4)
                {
                     if(sys_var.Adc_value[vacuum_v]>=135)       //�״��������ѹ����135KPaʱ�ر��Ƴ���
                    {
                        TIM_Cmd(TIM4, DISABLE);  //�س���
                        PWM2_OUT(0);
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                        Valve5 = Valve6 = ON;
                        SV17F_MP3_Specify(12);      //����������ʾ

                        sys_var.Job_step = 5;
                        sys_var.work_sta=0;
                        Dis_CV_BAS(BAS_OB_C,0,77,95,414);
//                        HMI_PictureCopy_xy(BAS_OB_C,sys_var.Screen,93,412,93+382,412+99);  //Ũ�ȿؼ�
//                        HMI_TXIconVal(VAR_OB_C,0);
//                        HMI_TXIconVal(VAR_OB_TC,2*sys_var.Language+sys_var.Vac_Open);   //�л���������ѹָʾ

                        printf("����������\r\n");
                    }
                
                }       
                
            }


            break;
        case infusionBottle:    //��Һƿ --1
            if(sys_var.Vac_Open==1)//����ѹ������տڳ���գ�
            {
                if(sys_var.Job_step==1)     //�������ã���ʼ�����
                {
                    Valve1 = Valve2 = Valve3 = Valve4 = OFF;
                    Valve5 = Valve6 = Valve7 = ON ;
//                    Valve1 = Valve2 = Valve5 = Valve4 = OFF;
//                    Valve3 = Valve6 = Valve7 = ON ;
                    PWM3_OUT(VacCtr_ON);       //����
//                    RGB_Colour(GREEN);      //�̵�
                    sys_var.Job_step=2;
                    printf("����\r\n");
                    
                }
                if(sys_var.Adc_value[vacuum_v]<40)        //�ﵽ���״̬
                {
                    delay_ms(200);  //������ʱ
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF;
                    Valve5 = Valve6 = ON ;
                    PWM3_OUT(VacCtr_OFF);       //��
                    sys_var.Vac_Open = 0;
                    sys_var.Job_step=3;
                    SV17F_MP3_Specify(11);      //���������ʾ
                    Dis_CV_BAS(BAS_BT_V,0,78,95,474);
//                    HMI_PictureCopy_xy(BAS_BT_V,sys_var.Screen,96,483,96+378,483+80);  //��ѹ�ؼ�
//                    HMI_TXIconVal(VAR_BT_V,sys_var.Vac_Open);   //�л���������ѹָʾ
//                    HMI_TXIconVal(VAR_BT_TV,2*sys_var.Language+sys_var.Vac_Open);   //�л���������ѹָʾ

                    printf("�ﵽ���\r\n");
                }
            }
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))     //�Ƴ�������
            {
                
                if(sys_var.Job_step==3)     //������ŷ�����ȡ����,ǰ10s��������ƿ
                {
                    Valve3 = Valve7 = OFF;
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve6 = ON ;
                    PWM3_OUT(VacCtr_OFF);       //��
//                    RGB_Colour(BLUE);      //������
                    sys_var.Job_step=4;
                    TIM_Cmd(TIM4, ENABLE);
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    printf("�����Ƴ���\r\n");
                    
                }
                
                
               if(sys_var.Adc_value[vacuum_v]>135)    //����
                {
                    if(sys_var.Job_step==4)     //�����������ƿ
                    {
//                     
                        delay_ms(500);
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF ;
                        Valve5 = Valve6 = ON;
//                    Valve1 = Valve2 = Valve5 = Valve4 = Valve7 = OFF ;
//                    Valve3  = Valve6 = ON;
                        sys_var.Job_step=6; //���ƿ�ڸ�ѹ�ﵽ130Kpa
                        RGB_Colour(GREEN);
                        TIM_Cmd(TIM4, DISABLE);     //���Ƴ���
                        PWM2_OUT(0);
                        sys_var.work_sta = 0;  
                        Dis_CV_BAS(BAS_BT_C,0,77,95,374);

                        printf("�ﵽ�س���\r\n");
                        printf("Job_step=%d",sys_var.Job_step);
                    }
                }
                
                

            }
            else
            {
                if(sys_var.Job_step==6)     //��Ѫ�׶�
                {
//                        sys_var.Adc_value[vacuum_v] = Get_vac_value();
                    if(sys_var.Adc_value[vacuum_v]<105)   //
                    {
                        Valve1 = Valve2 = Valve3 = Valve4 = Valve7 = OFF ;
                        Valve5 = Valve6 = OFF;
                        sys_var.Job_step = 7;
                        
                        printf("��Ѫ����\r\n");

                    }
//                    Clear();
                }
            }
            time++;
            if(time > 10)
            {
                dis_vac_bar(sys_var.Adc_value[vacuum_v]);     //��ʾѹ����
                time = 0;
                
            }
            break;
        case infusionBag:       //��Һ�� --1
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {
               
                if(sys_var.Job_step==1)     //
                {
                    Valve1 = Valve2 = Valve3 =ON;
                    Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, ENABLE);      //����PWM���
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    sys_var.Job_step=2;     //��ʼ�������
                    
//                    RGB_Colour(BLUE);      //�ص�
                    printf("�����Ƴ���\r\n");
                }
                if(sys_var.Job_step==3)
                {
//                    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);     //�ر�PWM���
                    PWM2_OUT(0);
//                    RGB_Colour(GREEN);      //���̵�
                    sys_var.work_sta = 0;
                    Dis_SP_BAS(BAS_BG_Work,sys_var.work_sta,598,553);
                    sys_var.Job_step = 4;
                    printf("�ﵽ���������ر��Ƴ���\r\n");
                }
            }
            else
            {
                if(sys_var.Job_step > 1)
                {
                    sys_var.Job_step = 1;
////                    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);     //�ر�PWM���
                    PWM2_OUT(0);
                }
//                RGB_Colour(GREEN);      //���̵�
            }
            break;
        case O3Hydrate:     //����ˮ�� --1
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {

                if(sys_var.Job_step==1)
                {
                    PWM3_OUT(VacCtr_OFF);
                    Valve1 = Valve2 = Valve4 = Valve5 = ON;
                    Valve3 = Valve6 = Valve7 =  OFF;
//                    OSTmrStart(tmr1,&err);//����������ʱ��1
                    TIM_Cmd(TIM4,DISABLE);  //������
//                    pulse = map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE);
                    PWM2_OUT(0);
////                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    sys_var.Job_step=2;
                    printf("���Ƴ���\r\n");
                }
                if(sys_var.Job_step == 3)   //��������ʱ����
                {
//                    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
                    sys_var.work_sta =0;
                    Dis_SP_BAS(BAS_H_Work,sys_var.work_sta,598,553);
//                    HMI_PictureCopy_xy(BAS_H_Work,sys_var.Screen+sys_var.work_sta,597,552,597+361,552+90);  //������ͣ�ؼ�
//                    HMI_TXIconVal(AMT_H_Work,sys_var.work_sta);
                    sys_var.Job_step=4;
                    Valve3 =ON;
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);  //�س���
                    PWM2_OUT(0);
                    printf("����ʱ����\r\n");
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
                    Valve1 = Valve2 = Valve3 =OFF;
                    Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);  //�س���
                    PWM2_OUT(0);
//                    RGB_Colour(GREEN);
                    printf("���Ƴ���\r\n");
                }

            }
            break;
        case suctionCup:    //��ѹ�ֱ�  --1
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {
                if(sys_var.Job_step==1)     //��ʼ�Ƴ��������
                {
                    Valve5 =  Valve7 = ON;
                    Valve6 = OFF;
                    Valve1 = Valve2 = Valve4 = ON;
                    Valve3 = OFF;
                    TIM_Cmd(TIM4, ENABLE);      //���Ƴ���
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    sys_var.Job_step=4;
                    
                    printf("���Ƴ���\r\n");
//                    delay_ms(500);      //������ʱ
                    
//                    RGB_Colour(GREEN);//�ص�
                    printf("����\r\n");

                }
                if(sys_var.Set_vac!=0)      //��ѹ����
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
                if(sys_var.Job_step == 4)   //�ȹس���
                {
                    Valve1 = Valve2 = Valve4 = Valve5 = Valve7 = ON ;
                    Valve3 = Valve6 = OFF;
                    PWM3_OUT((50+sys_var.Set_vac*50));        //����
                    TIM_Cmd(TIM4, DISABLE);      //���Ƴ���
                    PWM2_OUT(0);
//                    RGB_Colour(GREEN);
                    sys_var.Job_step=5;
                    cnt = 0;    //�������
                    printf("���Ƴ���\r\n");
                    delay_ms(1000);
                    Valve1 = Valve2 = Valve4 = Valve5 = OFF ;
                    Valve3 = Valve6 = Valve7 = OFF;
                    PWM3_OUT(VacCtr_OFF);        //�ر�
                    sys_var.Job_step=6;
//                    SV17F_MP3_Specify(11);
                    printf("�ر�\r\n");
                }
//                if(sys_var.Job_step == 5)   //10s��ظ�ѹ
//                {
//                    cnt++;
//                    if(cnt>100)
//                    {
//                        Valve1 = Valve2 = Valve4 = Valve5 = OFF ;
//                        Valve3 = Valve6 = Valve7 = OFF;
//                        PWM3_OUT(VacCtr_OFF);        //�ر�
//                        cnt = 0;
//                        sys_var.Job_step=6;
//                        SV17F_MP3_Specify(11);
//                        printf("�ر�\r\n");
//                    }
//                }
//                if(sys_var.Job_step == 6)   //����10s���
//                {
//                    cnt++;
//                    if(cnt>200)
//                    {
//                        Valve1 = Valve2 = Valve4 = Valve5 = OFF ;
//                        Valve3 = Valve6 = Valve7 = OFF;
//                        PWM3_OUT(VacCtr_OFF);        //�ر�
//                        cnt = 0;
//                        sys_var.Job_step=7;
//                        printf("10s���\r\n");
//                    }
//                }
            }
            
            
//            time++;
//            if(time > 20)
//            {
//               
////                dis_vac_bar2((int)sys_var.Adc_value[vacuum_v]);     //��ʾѹ����
//                time = 0;

//            }
            break;
        case ration:        //��������
            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {

                if(sys_var.Job_step == 1)       //�����������
                {
                    sys_var.Job_step = 2;
                    Valve1 = Valve2 = Valve4 = Valve5 =ON;
                    Valve3 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, ENABLE);      //����PWM���
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
                    PWM2_OUT(Density_P[sys_var.Density-1]);
                    printf("���Ƴ���\r\n");
                }
                if(sys_var.Job_step == 3)       //�������ﵽҪ��
                {
                    
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);     //�ر�PWM���
                    
////                    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
                    PWM2_OUT(0);
//                    RGB_Colour(GREEN);
                    sys_var.work_sta = 0;
                    sys_var.Job_step = 4;
                    Dis_SP_BAS(BAS_RT_Work,sys_var.work_sta,598,553);
//                    HMI_PictureCopy_xy(BAS_RT_Work,sys_var.Screen,599,558,599+362,558+84);  //������ͣ�ؼ�
//                    HMI_TXIconVal(AMT_RT_Work,sys_var.work_sta);
                    printf("�ﵽ���Ҫ��\r\n");
                    break;
                }
//                cnt ++;
//                if(cnt>=10)
//                {
//                    cnt = 0;
//                    LED_B = !LED_B;//������ 1s
//                    LED_G = OFF; //�̵ƹ�
//                }
            }
            else
            {
                if(sys_var.Job_step >1)
                {
                    
////                    OSTmrStop(tmr1,OS_TMR_OPT_PERIODIC,(OS_TMR_CALLBACK)tmr1_callback,&err);
                    sys_var.Job_step = 1;
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);     //�ر�PWM���
                    PWM2_OUT(0);
//                    LED_B = OFF;//���ƹ�
//                    LED_G = ON; //�̵���
                    printf("���Ƴ���\r\n");
                }
            }
            break;
        case injector:      //ע����

            if((sys_var.work_sta==1)&&(sys_var.Work_Down!=1))
            {

                if(sys_var.Job_step == 1)
                {
                    sys_var.Job_step = 2;

                    Valve1 = Valve2 = Valve3 =ON;
                    Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    TIM_Cmd(TIM4, DISABLE);     //�ر�PWM���
//                    PWM2_OUT(map(sys_var.Density,0,80,MIN_PULSE,MAX_PULSE));
//                    if(sys_var.Density!=0)
//                    {
//                        TIM_Cmd(TIM4, ENABLE);      //����PWM���
//                        PWM2_OUT(Density_P[sys_var.Density-1]);
//                    }else
//                    {
//                        TIM_Cmd(TIM4, DISABLE);     //�ر�PWM���
//                        PWM2_OUT(0);
//                    }
                    printf("�����Ƴ���\r\n");
                }
            }
            else
            {
//                cnt = 0;
                if(sys_var.Job_step > 1)
                {
                    sys_var.Job_step = 1;
//                    Valve1 = Valve2 = Valve3 = Valve4 = Valve5 = Valve6 = Valve7 = OFF;
                    Valve1 = Valve2 = Valve3 = Valve4 = Valve6 = Valve7 = OFF;
                    Valve5 = ON;
                    TIM_Cmd(TIM4, DISABLE);     //�ر�PWM���
                    PWM2_OUT(0);
//                    RGB_Colour(GREEN);
                    printf("���Ƴ���\r\n");
                }
            }
            break;
        default:
            break;
        }
        delay_ms(50);
    }

}
