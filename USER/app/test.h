/*
* ��Ȩ����(C): ���Ļ� ���ڿ�ҽ�ʿƼ���չ���޹�˾ 2020.5
* �ĵ�˵����UCOSII�����ջ���� 
*
*/

#ifndef _TEST_H_
#define _TEST_H_

#include "includes.h"
/////////////////////////UCOSII�����ջ����///////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO      			10 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//�������ӿ�
void start_task(void *pdata);

//LED����
//�����������ȼ�
#define LED_TASK_PRIO       			4
//���������ջ��С
#define LED_STK_SIZE  		    		64
//�������ӿ�
void led_task(void *pdata);


//ADC�ɼ���������
//�����������ȼ�
#define ADC_TASK_PRIO       			5
//���������ջ��С
#define ADC_STK_SIZE  					64
//�������ӿ�
void adc_task(void *pdata);


//��ѹ��������
//�����������ȼ�
#define VAC_TASK_PRIO       			6
//���������ջ��С
#define VAC_STK_SIZE  					64
//�������ӿ�
void vac_task(void *pdata);

//LCD����������
//�����������ȼ�
#define LCD_TASK_PRIO       			3
//���������ջ��С
#define LCD_STK_SIZE  					512
//�������ӿ�
void lcd_task(void *pdata);

//��������
//�����������ȼ�
#define CTR_TASK_PRIO       			7
//���������ջ��С
#define CTR_STK_SIZE  					128
//�������ӿ�
void ctr_task(void *pdata);



#endif

