#include "SysIO_Init.h" 

void SystemGPIO(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD ,ENABLE);	 //使能PC端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    //开启AFIO功能
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);   // 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，禁用JTAG-DP，启用SW-DP
    //阀初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	             // 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;		 //IO口速度为50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
    GPIO_SetBits(GPIOA,GPIO_Pin_15);
    
    //阀初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_9;	             // 端口配置
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
    GPIO_SetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_9);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;	             // 端口配置
    GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
    GPIO_SetBits(GPIOC,GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	             // 端口配置
    GPIO_Init(GPIOD, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
    GPIO_SetBits(GPIOD,GPIO_Pin_2);
   
    
}












