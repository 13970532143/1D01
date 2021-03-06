	 
#include "includes.h" 


/************************************************/
//创建任务堆栈空间	
OS_STK START_TASK_STK[START_STK_SIZE];
OS_STK LED_TASK_STK[LED_STK_SIZE];
OS_STK ADC_TASK_STK[ADC_STK_SIZE]; 
OS_STK VAC_TASK_STK[VAC_STK_SIZE];	
OS_STK LCD_TASK_STK[LCD_STK_SIZE];	
OS_STK CTR_TASK_STK[CTR_STK_SIZE];

int main(void)
{	 
	delay_init();	    	 //延时函数初始化	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级   
	ALL_Init();

	OSInit();  	 			//初始化UCOSII		 			  
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//创建起始任务
	OSStart();	    
}

//开始任务
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 		  		 			  
	OSStatInit();					//初始化统计任务.这里会延时1秒钟左右	
 	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);			 //LED			    				   
 	OSTaskCreate(adc_task,(void *)0,(OS_STK*)&ADC_TASK_STK[ADC_STK_SIZE-1],ADC_TASK_PRIO);	 		 //adc  
 	OSTaskCreate(lcd_task,(void *)0,(OS_STK*)&LCD_TASK_STK[LCD_STK_SIZE-1],LCD_TASK_PRIO);	         //触摸屏任务
 	OSTaskCreate(ctr_task,(void *)0,(OS_STK*)&CTR_TASK_STK[CTR_STK_SIZE-1],CTR_TASK_PRIO);	  		 //控制任务		   
 	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务. 				   
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}	  



