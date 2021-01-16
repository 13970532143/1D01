/*
* 版权所有(C): 黄文基 深圳科医仁科技发展有限公司 2020.5
* 文档说明：UCOSII任务堆栈设置 
*
*/

#ifndef _TEST_H_
#define _TEST_H_

#include "includes.h"
/////////////////////////UCOSII任务堆栈设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务函数接口
void start_task(void *pdata);

//LED任务
//设置任务优先级
#define LED_TASK_PRIO       			4
//设置任务堆栈大小
#define LED_STK_SIZE  		    		64
//任务函数接口
void led_task(void *pdata);


//ADC采集处理任务
//设置任务优先级
#define ADC_TASK_PRIO       			5
//设置任务堆栈大小
#define ADC_STK_SIZE  					64
//任务函数接口
void adc_task(void *pdata);


//负压控制任务
//设置任务优先级
#define VAC_TASK_PRIO       			6
//设置任务堆栈大小
#define VAC_STK_SIZE  					64
//任务函数接口
void vac_task(void *pdata);

//LCD触摸屏任务
//设置任务优先级
#define LCD_TASK_PRIO       			3
//设置任务堆栈大小
#define LCD_STK_SIZE  					512
//任务函数接口
void lcd_task(void *pdata);

//控制任务
//设置任务优先级
#define CTR_TASK_PRIO       			7
//设置任务堆栈大小
#define CTR_STK_SIZE  					128
//任务函数接口
void ctr_task(void *pdata);



#endif

