/*
* Copyright (C) ���Ļ�.���ڿ�ҽ�ʿƼ���չ���޹�˾
* Time��
 */

#include "test.h"

/*
��ѹ���㹫ʽ
VAC_P = VAC_K * VAC_V + VAC_B
���ڸ�ѹģ����裬ʹ��ѹģ���ڳ�ѹ�����2.5V
2.5V-->100KPa
VAC_V:��õ�ѹ
VAC_K = 500/12
VAC_B = 50/12
*/


/*
��ѹ���㹫ʽ
VAC_P = VAC_K * VAC_V + VAC_B
���ڸ�ѹģ����裬ʹ��ѹģ���ڳ�ѹ�����2.3V
2.3V-->100KPa
VAC_V:��õ�ѹ
VAC_K = 43.796
VAC_B = 0.734
*/




void adc_task(void *pdata)
{
    float voltage[5];
    float ingiter_R=0.0,adc_vac=0.0;
    float ingiter_T=0.0;
    u8 i = 0,time=0,sta=0;
    pdata = pdata;
    
    while(1)
    {


        //5V��ѹ
        adc_vac = Get_AdcValue(voltage_5v);
        voltage[voltage_5v]=(float)((adc_vac*1.0*3.30)/4095);
        sys_var.Adc_value[voltage_5v] = (float)(voltage[voltage_5v] * 1.67);
//        printf("5V��ѹ=%d\r\n",(int)(sys_var.Adc_value[voltage_5v]*100));

        //24V��ѹ
        adc_vac = Get_AdcValue(voltage_24v);
        voltage[voltage_24v]=(float)((adc_vac*1.0*3.30)/4095);
        sys_var.Adc_value[voltage_24v] = (float)(voltage[voltage_24v] * 11);
//        printf("24V��ѹ=%d\r\n",(int)(sys_var.Adc_value[voltage_24v]*100));
        if(sys_var.Adc_value[voltage_24v]<20)
        {
            delay_ms(50);
            if(sys_var.Adc_value[voltage_24v]<20)
            {
                if(sys_var.Error==0)
                {
                    Valve1 = Valve2 = Valve2 = Valve4 = OFF;
                    Valve5 = Valve6 = Valve7 =  OFF;
                    PWM3_OUT(VacCtr_OFF);       //��
                    TIM_Cmd(TIM4, DISABLE);  //�س���
                    PWM2_OUT(0);
                    sys_var.work_sta = 0;
                    sys_var.work_mode = 0;
                    sys_var.Error = 2;
                    RGB_Colour(RED);      //���̵�
                    SV17F_MP3_Specify(13);
                    sys_var.Screen = S_ERROR;
                    HMI_PictureCopy_xy(BAS_ERR_Err,sys_var.Screen+1+sys_var.Language,282,2,282+250,2+59);
    //                HMI_PictureCopy_S_T_xy(BAS_ERR_Ifo,sys_var.Screen+1+sys_var.Language,83,249,83+681,249+91,70,257);       //�¶�
                    HMI_PictureCopy_S_T_xy(BAS_ERR_Ifo,sys_var.Screen+1+sys_var.Language,84,372,84+680,372+111,70,257);        //��ѹ
                    HMI_ChangeScreen(sys_var.Screen); 
                            
                }   
            }
                     
        }
        else
        {
            if(sys_var.Error==2)
            {
//                sys_var.Screen = S_HOME+2*sys_var.Language;
//                HMI_ChangeScreen(sys_var.Screen);
                time=0;
                RGB_Colour(GREEN);      //���̵�
                sys_var.Error = 0;
            }
            
        }
        

        //�������¶�
        adc_vac = Get_AdcValue(ozonizer_t);
        voltage[ozonizer_t]=(float)((adc_vac*1.0*3.30)/4095);
        ingiter_R = (float)(((5/voltage[ozonizer_t])-1)*1000);
        ingiter_T = Get_Temp(ingiter_R);//��ȡ�����ܵ��¶�
        sys_var.Adc_value[ozonizer_t] = ingiter_T;
        if((sys_var.Adc_value[ozonizer_t]>=60)||(sys_var.Adc_value[ozonizer_t]<=10))
        {
            delay_ms(50);
            if((sys_var.Adc_value[ozonizer_t]>=60)||(sys_var.Adc_value[ozonizer_t]<=10))        //�������¶Ȱ���
            {
                if(sys_var.Error==0)
                {
                    Valve1 = Valve2 = Valve2 = Valve4 = OFF;
                    Valve5 = Valve6 = Valve7 =  OFF;
                    PWM3_OUT(VacCtr_OFF);       //��
                    TIM_Cmd(TIM4, DISABLE);  //�س���
                    PWM2_OUT(0);
                    sys_var.work_sta = 0;
                    sys_var.work_mode = 0;
                    sys_var.Error = 1;
                    SV17F_MP3_Specify(13);
                    RGB_Colour(RED);      //���̵�
                    sys_var.Screen = S_ERROR;
                    HMI_PictureCopy_xy(BAS_ERR_Err,sys_var.Screen+1+sys_var.Language,282,2,282+250,2+59);
                    HMI_PictureCopy_S_T_xy(BAS_ERR_Ifo,sys_var.Screen+1+sys_var.Language,83,249,83+681,249+91,70,257);       //�¶�
    //                HMI_PictureCopy_S_T_xy(BAS_ERR_Ifo,sys_var.Screen+1+sys_var.Language,84,372,84+680,372+111,70,257);        //��ѹ
                    HMI_ChangeScreen(sys_var.Screen);
                    
                }
                
                 
            }
                     
        }
        else
        {
            if(sys_var.Error==1)
            {
//                sys_var.Screen = S_HOME+2*sys_var.Language;
//                HMI_ChangeScreen(sys_var.Screen);
                time=0;
                RGB_Colour(GREEN);      //���̵�
                sys_var.Error = 0;
            }
            
        }
        
        if(sys_var.Error!=0)
        {
            time++;
            if(time>=30)
            {
                time = 0;
                SV17F_MP3_Specify(13);
            }
        }

        //��ѹ��С
        adc_vac = Get_AdcValue(vacuum_v);
        voltage[vacuum_v]=(float)((adc_vac*1.0*3.30)/4095);
//        sys_var.Adc_value[vacuum_v] = (float)((voltage[vacuum_v]*500 -50)/12);
        sys_var.Adc_value[vacuum_v] = (float)(voltage[vacuum_v]*43.796-0.734);
        

        //ɢ��Ƭ�¶�
        adc_vac = Get_AdcValue(cooling_fin);
        voltage[cooling_fin]=(float)((adc_vac*1.0*3.30)/4095);
        ingiter_R = (float)(((5/voltage[cooling_fin])-1)*1000);
        ingiter_T = Get_Temp(ingiter_R);//��ȡɢ��Ƭ�¶�
        sys_var.Adc_value[cooling_fin] = ingiter_T;
        i++;
        if(i>10)
        {
            i=0;
            printf("��ѹ��С=%d\r\n",(int)( sys_var.Adc_value[vacuum_v]*100));
             printf("Job_step=%d\r\n",sys_var.Job_step);
//            printf("error ��%d\r\n",sys_var.Error);
//            printf("��ѹ = %d\r\n",(int)(voltage[vacuum_v]*100));
        }            
        
        delay_ms(50);
        
    }
}


