#include "adc.h"		 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ADC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/6
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
/* define ---------------------------------------------------------------------*/


/* ���� ----------------------------------------------------------------------*/
__IO uint16_t ADC1ConvertedValue[10][5];


//��ʼ��ADC															   
void  Adc_Init(void)
{    
    ADC_InitTypeDef       ADC_InitStructure;                                        //ADC��ʼ���ṹ��
    DMA_InitTypeDef       DMA_InitStructure;                                        //DMA��ʼ���ṹ��
    GPIO_InitTypeDef      GPIO_InitStructure;                                       //GPIO��ʼ���ṹ��

    
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB, ENABLE);
   //��ʼ������˿�
//    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1; //�ɼ���ѹ������ΪPA1
//    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;                                      //ģ������ģʽ
////    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                                //�ٶ�Ϊ50MHz
//    GPIO_Init(GPIOA, &GPIO_InitStructure);  
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;//�ɼ���ѹ������ΪPC0
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;                                        //�ٶ�Ϊ50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure); 
    
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;//�ɼ���ѹ������ΪPC0
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;                                      //ģ������ģʽ
   GPIO_Init(GPIOB, &GPIO_InitStructure); 
   
	/* ʹ�� ADC1, DMA2 �� GPIO ʱ�� ****************************************/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /* DMA1 Stream1 channe1 ���� **************************************/
	DMA_DeInit(DMA1_Channel1);
	 DMA_InitStructure.DMA_BufferSize=50;         //�������ݵĴ�С                                   //�������ݸ���
	 DMA_InitStructure.DMA_DIR=DMA_DIR_PeripheralSRC;         //����(�����赽�ڴ�)                       //������Ϊ����Դ
	 DMA_InitStructure.DMA_M2M=DMA_M2M_Disable;                                      //��ʹ���ڴ浽�ڴ�
	 DMA_InitStructure.DMA_MemoryBaseAddr=(uint32_t)ADC1ConvertedValue;; //�ڴ��ַ            //�ڴ��д洢DMA������������ݻ���ַ
	 DMA_InitStructure.DMA_MemoryDataSize=DMA_MemoryDataSize_HalfWord;               //�ڴ�����Ϊ���� 16λ��ADC����Ϊ12λ��
	 DMA_InitStructure.DMA_MemoryInc=DMA_MemoryInc_Enable;                        //�ڴ��ַҪ����
	 DMA_InitStructure.DMA_Mode=DMA_Mode_Circular;                                   //DMA������ѭ��ģʽ
	 DMA_InitStructure.DMA_PeripheralBaseAddr= (uint32_t)&ADC1->DR; //ADC��ַ                 //����Դ��ַ  ADC���ݼĴ�����ַ
	 DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;       //DMA�������ݿ�� 
	 DMA_InitStructure.DMA_PeripheralInc=DMA_PeripheralInc_Disable;                  //�����ַ����
	 DMA_InitStructure.DMA_Priority=DMA_Priority_High; 	                             //DMA���ȼ���
	 DMA_Init(DMA1_Channel1, &DMA_InitStructure);                                    //DMA��ʼ��
	 DMA_Cmd(DMA1_Channel1, ENABLE);    	                                         //ʹ��DMA
 

  
                                             
    
   

		//ADC1 ��ʼ�� ****************************************************************/
		ADC_InitStructure.ADC_ContinuousConvMode=ENABLE;    //��������ת��ģʽ                              //ADC����ģʽ��
		ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;          //�ɼ������Ҷ���                    //12λ�����Ҷ���
		ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;   //��ʹ���ⲿ����ת��              //�ⲿ������  ���������
		ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;      //����ADCģʽ                            //ADC�����ڶ���ģʽ
		ADC_InitStructure.ADC_NbrOfChannel=5;             //Ҫת����ͨ����Ŀ                                //����ͨ����Ϊ4
		ADC_InitStructure.ADC_ScanConvMode=ENABLE;      //����ɨ�跽ʽ                                   //ɨ��ģʽ��
		ADC_Init(ADC1, &ADC_InitStructure);	                                              //����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ��� 
	

        RCC_ADCCLKConfig(RCC_PCLK2_Div6);//����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9Hz
		
        ADC_RegularChannelConfig(ADC1,ADC_Channel_8, 1, ADC_SampleTime_55Cycles5);      //5V��ѹ
		ADC_RegularChannelConfig(ADC1,ADC_Channel_10, 2, ADC_SampleTime_55Cycles5);     //24V��ѹ
		ADC_RegularChannelConfig(ADC1,ADC_Channel_11, 3, ADC_SampleTime_55Cycles5);     //�������¶�
        ADC_RegularChannelConfig(ADC1,ADC_Channel_12, 4, ADC_SampleTime_55Cycles5);     //��ѹ��С
        ADC_RegularChannelConfig(ADC1,ADC_Channel_13, 5, ADC_SampleTime_55Cycles5);     //ɢ��Ƭ�¶�
        

		/* ʹ��DMA����(��ADCģʽ) */
//		ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
			
		/* ʹ�� ADC1 */
		ADC_Cmd(ADC1, ENABLE);
		
		/* ʹ�� ADC1 DMA */
		ADC_DMACmd(ADC1, ENABLE);
		
		ADC_ResetCalibration(ADC1);	                //ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	                //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	    //�ȴ�У׼����
	 	
	/* �������ADCת�� */ 
    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	   
	
}		

//Rank: 0~4
u16 Get_AdcValue(u8 Rank)
{
    u8 i = 0;
    u32 tempadc = 0;
    for(i=0;i<10;i++)
    {
        tempadc += ADC1ConvertedValue[i][Rank];//�ɼ������ܺ�
    }
    return tempadc / 10;
}


//��ȡ��ѹ��С
float Get_vac_value(void)
{
    u16 adc_vac = 0;
    float voltage = 0.0;
    adc_vac = Get_AdcValue(1);
    voltage=(float)((adc_vac*1.0*3.33)/4095);
    sys_var.Adc_value[vacuum_v] = (float)((voltage*500 -50)/12);
    return voltage;
}












