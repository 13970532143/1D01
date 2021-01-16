#include "timer.h"
#include "led.h"
#include "usart.h"
//V1.1 20120904
//1,增加TIM4_PWM_Init函数。
//2,增加LED0_PWM_VAL宏定义，控制TIM4_CH2脉宽									  
//////////////////////////////////////////////////////////////////////////////////  
   	  
      
      
      
//通用定时器3中断初始化
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。
//psc：时钟预分频数
//这里使用的是定时器3!
void TIM2_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //时钟使能
	
	//定时器TIM3初始化
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM2, ENABLE);  //使能TIMx					 
}
     





//TIM4 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
////psc：时钟预分频数
void TIM4_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	
// 	TIM_DeInit(TIM4);
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4, ENABLE); //GPIO_PartialRemap_TIM4  Timer3部分重映射  TIM4_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM4 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器3时钟
   //初始化TIM4
   //---------------------------------------------------------------
	//PWM模式	TIM_Pulse--即脉宽 单位us
	//占空比= ( TIM_Pulse / ( TIM_Period + 1) ) * 100%
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM4 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高	
//    TIM_OCInitStructure.TIM_Pulse = 0; 
//    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3   TIM_OCxInit(x=1,2,3,4)  为OC1,2,3,4
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3   TIM_OCxInit(x=1,2,3,4)  为OC1,2,3,4
    TIM_Cmd(TIM4, DISABLE);  
    
	TIM_SetCompare3(TIM4,0);  //使能TIM4在CCR3上的预装载寄存器 TIM_OCxPreloadConfig(x=1,2,3,4)
//	TIM_SetCompare4(TIM4,0);  


}



//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
////psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	
// 	TIM_DeInit(TIM3);
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4, ENABLE); //GPIO_PartialRemap_TIM4  Timer3部分重映射  TIM4_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM4 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
 
    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器3时钟
   //初始化TIM4
   //---------------------------------------------------------------
	//PWM模式	TIM_Pulse--即脉宽 单位us
	//占空比= ( TIM_Pulse / ( TIM_Period + 1) ) * 100%
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM4 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性高	
//    TIM_OCInitStructure.TIM_Pulse = 0; 
//    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3   TIM_OCxInit(x=1,2,3,4)  为OC1,2,3,4
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3   TIM_OCxInit(x=1,2,3,4)  为OC1,2,3,4
    TIM_Cmd(TIM3, ENABLE);  
    
	TIM_SetCompare2(TIM3,0);  //使能TIM4在CCR3上的预装载寄存器 TIM_OCxPreloadConfig(x=1,2,3,4)
//	TIM_SetCompare4(TIM4,0);  
}


void PWM1_OUT(u16 pulse)
{
    TIM_SetCompare2(TIM3,pulse); 
}
void PWM2_OUT(u16 pulse)
{
    TIM_SetCompare3(TIM4,pulse); 
}
void PWM3_OUT(u16 pulse)
{
    TIM_SetCompare2(TIM5,pulse); 
}




//TIM5 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
////psc：时钟预分频数
void TIM5_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	
// 	TIM_DeInit(TIM3);
 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
//	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM4, ENABLE); //GPIO_PartialRemap_TIM4  Timer3部分重映射  TIM4_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM4 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
 
    
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	//使能定时器3时钟
   //初始化TIM4
   //---------------------------------------------------------------
	//PWM模式	TIM_Pulse--即脉宽 单位us
	//占空比= ( TIM_Pulse / ( TIM_Period + 1) ) * 100%
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM4 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高	
//    TIM_OCInitStructure.TIM_Pulse = 0; 
//    TIM_OC4Init(TIM4, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3   TIM_OCxInit(x=1,2,3,4)  为OC1,2,3,4
    TIM_OC2Init(TIM5, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM4 OC3   TIM_OCxInit(x=1,2,3,4)  为OC1,2,3,4
    TIM_Cmd(TIM5, ENABLE);  
    
	TIM_SetCompare2(TIM5,0);  //使能TIM4在CCR3上的预装载寄存器 TIM_OCxPreloadConfig(x=1,2,3,4)
//	TIM_SetCompare4(TIM4,0);  
}


