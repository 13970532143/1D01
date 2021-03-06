/*
* 版权所有(C): 黄文基 深圳科医仁科技发展有限公司 2020.6
* 文档说明：LED任务，系统LED指示， 测试功能的实现,按键功能的实现
*
*/
#include "test.h"


const u8 write_flash[] = "FALSH OK ";
#define SIZE sizeof(write_flash)		//数组长度
#define FLASH_SAVE_ADDR  0X08070000		//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)


void led_task(void *pdata)
{
    
    u8 i=0,err=0,sta = 0 ;
    u8 erprom = 0,flash = 0;
    u8 y=0,reade=0;
    u8 reade_flash[20]="           ";
    u8 NUN=10;
    pdata = pdata;
    delay_ms(100);

//    Valve1=Valve2=Valve4=Valve6=ON;
//    Valve1=ON;
//    Valve2=ON;
//    Valve3=ON;
//    Valve4=ON;
//    Valve5=ON;
//    Valve6=ON;
//    Valve7=ON;
//    Valve8=ON;
    while(1)
    {
//    Valve1=ON;
//    Valve2=ON;
//    Valve3=OFF;
//    Valve4=ON;
//    Valve5=ON;
//    Valve6=OFF;
//    Valve7=OFF;
//    PWM3_OUT(VacCtr_OFF);
        if(i == 10 )
        {
            LED0 = !LED0;
            
                
            if(sys_var.Screen == S_Test)
            {
                HMI_ShowNumber_int(TXT_TS_TEMP,(int)(sys_var.Adc_value[ozonizer_t]*100),4,5);
            }
            i = 0;
            if(sys_var.Error==0)
            {
                if(sys_var.work_sta==1)
                {
                    sta = !sta;
                    if(sta)  LED_B = !LED_B;//蓝灯闪 1s
                    else RGB_Colour(LED_OFF);      //开绿灯
                }
                else
                {
                    if(sys_var.clear==1)
                    {
                       sta = !sta;
                       if(sta) LED_G = !LED_G;
                       else RGB_Colour(LED_OFF);      //关灯
                    }
                    else
                    {
                        RGB_Colour(GREEN);      //开绿灯
                    }
                }            
                if(sys_var.test_sta==1)
                {
    //                printf("NTC温度*100=%d\r\n",(int)(sys_var.Adc_value[ozonizer_t]*100));
    //				printf("负压大小*100 %2d\r\n\r\n",(int)(sys_var.Adc_value[vacuum_v]*10));//(int)sys_var.Adc_value[vacuum_v]);
                    HMI_ShowNumber_int(TXT_TS_VAC,(int)sys_var.Adc_value[vacuum_v],3,5);
                    
                    HMI_ShowNumber_int(TXT_TS_TEMP2,(int)(sys_var.Adc_value[cooling_fin]*100),4,5);
                    HMI_ShowNumber_int(TXT_TS_5V,(int)(sys_var.Adc_value[voltage_5v]*100),4,5);
                    HMI_ShowNumber_int(TXT_TS_24V,(int)(sys_var.Adc_value[voltage_24v]*100),4,5);
                    y++;
                    if(y==1) RGB_Colour(RED);
                    if(y==2) RGB_Colour(GREEN);
                    if(y==3) RGB_Colour(BLUE);
                    if(y>=3)y=0;
                    Valve1=!Valve1;
                    Valve2=!Valve2;
                    Valve3=!Valve3;
                    Valve4=!Valve4;
                    Valve5=!Valve5;
                    Valve6=!Valve6;
                    Valve7=!Valve7;
                    Valve8=!Valve8;
    //                VacCtr = ON;
                    if(erprom!=1)
                    {
                        err=EEPROM_WriteSeq(10,(INT8U*)&NUN,sizeof(NUN));
                        delay_ms(50);
                        err=EEPROM_ReadSeq(10,(INT8U*)&reade,sizeof(reade));
                        delay_ms(50);
                        if(reade==10)
                        {
                            printf("EEPROM OK\r\n");
                            HMI_TXStrToEdit(TXT_TS_EEPROM,"OK",5);

                            erprom = 1;
                        }
                        else
                        {
                            HMI_TXStrToEdit(TXT_TS_EEPROM,"ERROR",5);
                            printf("EEPROM ERR\r\n");
                        }
                    }
                    if(flash!= 1)
                    {
                        W25QXX_Write((u8*)write_flash,FLASH_SAVE_ADDR,SIZE);
                        delay_ms(50);
                        W25QXX_Read((u8*)reade_flash,FLASH_SAVE_ADDR,SIZE);
                        delay_ms(50);
                        if(reade_flash[0] == 'F')
                        {
                            printf("flash read=%s\r\n",reade_flash);
                            HMI_TXStrToEdit(TXT_TS_FLASH,"OK",5);
                            flash = 1;
                        }
                        else
                        {
                            printf("FLASH ERR\r\n");
                            HMI_TXStrToEdit(TXT_TS_FLASH,"ERROR",5);
                        }
                    }
                }
                else if((sys_var.test_sta&0x02)==1)
                {
                flash = 0;
                erprom = 0;
                RGB_Colour(0);
                Valve1=OFF;
                Valve2=OFF;
                Valve3=OFF;
                Valve4=OFF;
                Valve5=OFF;
                Valve6=OFF;
                Valve7=OFF;
                Valve8=OFF;
                //VacCtr = OFF;
            }
            }
            else
            {
                sta = !sta;
                if(sta)  RGB_Colour(RED);      //开绿灯;
                else RGB_Colour(LED_OFF);      //开绿灯
            }
        }
        if(KEY_Scan(0)==WKUP_PRES)
        {
//            delay_ms(200);
            SV17F_MP3_Specify(12);
            
            delay_ms(50);
            sys_var.Screen = S_Test;
            HIM_SCR_ID(92);
            
//            sta = !sta;
//            if(sta == 1)
//            {
//                PWM3_OUT(VacCtr_ON);
//                Valve1 = Valve2 = Valve3 = Valve4 = OFF;
//                Valve5 = Valve6 = Valve7 = ON ; 
//                
//            }
//            else
//            {
//                PWM3_OUT(0);
//                Valve5 = Valve6 = Valve7 = OFF ; 
//            }
//			Valve1=OFF;
//            
//			Valve1=Valve2=Valve3=Valve4=Valve6=sta;
           
//			Clear();

//            duty+=500;
//            if(duty>6000) duty = 100;
//            PWM1_OUT(duty);
        }
        i++;
        delay_ms(50);
    }
}

