#include "common.h"

u16 Density_P[80];
u16 Density_Adj_P[9] = { 750,1690,2570,3440,4390,5455,6675,8250,9900};
             //对应浓度    1, 10 ,20  ，30 ,40  ,50  ,60  ,70  ,80




void Map_Density(u16 *data)
{
    u8 i =0;
    for(i=0;i<80;i++)
    {
        Density_P[i]=map(i,(i/10)*10,(i/10)*10+9,data[i/10],data[i/10+1]);
        if(i%10==0) printf("\r\n");
        printf("%d ",Density_P[i]);
        
    }
    
}


void SoftDelayms(unsigned short delay)
{
    unsigned short i, j;
    for(i=0; i<delay; i++)
    {
        for(j=7900; j!=0; j--)
            ;
    }
}


void Variables_init(void)
{
    sys_var.work_sta =0;
    sys_var.Density = 0;
    sys_var.test_sta = 0;
    sys_var.Set_vac = 0;
    sys_var.Error = 0;
//    Map_Density(Density_Adj_P);
}

void ALL_Init(void)
{
    LED_Init();
    SystemGPIO();
    IIC_Init();
    W25QXX_Init();			//W25QXX初始化
    KEY_Init();
    TIM4_PWM_Init(10000-1,120-1);	    //控60hz
    TIM3_PWM_Init(1200-1,10-1);         //PWM频率=72000000/(10)/(1200)=6Khz
    TIM5_PWM_Init(1000-1,72-1);         //PWM频率=72000000/(72)/(1000)=1Khz
    TIM_SetCompare2(TIM3,900);          //900/1200
    TIM2_Int_Init(600,7200-1);         ////10Khz的计数频率，计数到600为60ms
    USART3_Init(115200);			//HIM连接
    USART2_Init(9600);
    uart_init(115200); 
    Adc_Init();
    Variables_init();
    //OSTimeDly(5);
}


