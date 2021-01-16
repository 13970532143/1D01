#include "adc.h"		 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//ADC 驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/6
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
/* define ---------------------------------------------------------------------*/


/* 变量 ----------------------------------------------------------------------*/
__IO uint16_t ADC1ConvertedValue[10][5];


//初始化ADC															   
void  Adc_Init(void)
{    
    ADC_InitTypeDef       ADC_InitStructure;                                        //ADC初始化结构体
    DMA_InitTypeDef       DMA_InitStructure;                                        //DMA初始化结构体
    GPIO_InitTypeDef      GPIO_InitStructure;                                       //GPIO初始化结构体

    
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);
   //初始化输入端口
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1; //采集电压的引脚为PA1
//    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;                                      //模拟输入模式
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //速度为50MHz
//    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//采集电压的引脚为PC0
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;                                        //速度为50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//采集电压的引脚为PC0
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;                                      //模拟输入模式
   GPIO_Init(GPIOB, &GPIO_InitStructure); 
   
	/* 使能 ADC1, DMA2 和 GPIO 时钟 ****************************************/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /* DMA1 Stream1 channe1 配置 **************************************/
	DMA_DeInit(DMA1_Channel1);
	 DMA_InitStructure.DMA_BufferSize=50;         //传输内容的大小                                   //缓存数据个数
	 DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;         //方向(从外设到内存)                       //以外设为数据源
	 DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;                                      //不使用内存到内存
	 DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)ADC1ConvertedValue;; //内存地址            //内存中存储DMA传输过来的数据基地址
	 DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;               //内存数据为半字 16位（ADC精度为12位）
	 DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;                        //内存地址要增加
	 DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;                                   //DMA工作在循环模式
	 DMA_InitStructure.DMA_PeripheralBaseAddr= (uint32_t)&ADC1->DR; //ADC地址                 //数据源地址  ADC数据寄存器地址
	 DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;       //DMA外设数据宽度 
	 DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;                  //外设地址增加
	 DMA_InitStructure.DMA_Priority=DMA_Priority_High; 	                             //DMA优先级高
	 DMA_Init(DMA1_Channel1, &DMA_InitStructure);                                    //DMA初始化
	 DMA_Cmd(DMA1_Channel1, ENABLE);    	                                         //使能DMA
 

  
                                             
    
   

		//ADC1 初始化 ****************************************************************/
		ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;    //开启连续转换模式                              //ADC连续模式开
		ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;          //采集数据右对齐                    //12位数据右对齐
		ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;   //不使用外部触发转换              //外部开启关  由软件开启
		ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;      //独立ADC模式                            //ADC工作在独立模式
		ADC_InitStructure.ADC_NbrOfChannel=5;             //要转换的通道数目                                //开启通道数为4
		ADC_InitStructure.ADC_ScanConvMode=ENABLE;      //允许扫描方式                                   //扫描模式关
		ADC_Init(ADC1, &ADC_InitStructure);	                                              //根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器 
	

        RCC_ADCCLKConfig(RCC_PCLK2_Div6);//配置ADC时钟，为PCLK2的8分频，即9Hz
		
        ADC_RegularChannelConfig(ADC1,ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);      //5V电压
		ADC_RegularChannelConfig(ADC1,ADC_Channel_10, 2, ADC_SampleTime_55Cycles5);     //24V电压
		ADC_RegularChannelConfig(ADC1,ADC_Channel_11, 3, ADC_SampleTime_55Cycles5);     //臭氧管温度
        ADC_RegularChannelConfig(ADC1,ADC_Channel_12, 4, ADC_SampleTime_55Cycles5);     //负压大小
        ADC_RegularChannelConfig(ADC1,ADC_Channel_13, 5, ADC_SampleTime_55Cycles5);     //散热片温度
        

		/* 使能DMA请求(单ADC模式) */
//		ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
			
		/* 使能 ADC1 */
		ADC_Cmd(ADC1, ENABLE);
		
		/* 使能 ADC1 DMA */
		ADC_DMACmd(ADC1, ENABLE);
		
		ADC_ResetCalibration(ADC1);	                //使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	                //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	    //等待校准结束
	 	
	/* 软件启动ADC转换 */ 
    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	   
	
}		

//Rank: 0~4
u16 Get_AdcValue(u8 Rank)
{
    u8 i = 0;
    u32 tempadc = 0;
    for(i=0;i<10;i++)
    {
        tempadc += ADC1ConvertedValue[i][Rank];//采集数据总和
    }
    return tempadc / 10;
}


//获取负压大小
float Get_vac_value(void)
{
    u16 adc_vac = 0;
    float voltage = 0.0;
    adc_vac = Get_AdcValue(1);
    voltage=(float)((adc_vac*1.0*3.33)/4095);
    sys_var.Adc_value[vacuum_v] = (float)((voltage*500 -50)/12);
    return voltage;
}












