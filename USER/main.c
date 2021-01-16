	 
#include "includes.h" 


/************************************************/
//���������ջ�ռ�	
OS_STK START_TASK_STK[START_STK_SIZE];
OS_STK LED_TASK_STK[LED_STK_SIZE];
OS_STK ADC_TASK_STK[ADC_STK_SIZE]; 
OS_STK VAC_TASK_STK[VAC_STK_SIZE];	
OS_STK LCD_TASK_STK[LCD_STK_SIZE];	
OS_STK CTR_TASK_STK[CTR_STK_SIZE];
OS_STK CLEAR_TASK_STK[CLEAR_STK_SIZE];

int main(void)
{	 
	delay_init();	    	 //��ʱ������ʼ��	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�   
	ALL_Init();

	OSInit();  	 			//��ʼ��UCOSII		 			  
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );//������ʼ����
	OSStart();	    
}

//��ʼ����
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 		  		 			  
	OSStatInit();					//��ʼ��ͳ������.�������ʱ1��������	
 	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)    
 	OSTaskCreate(led_task,(void *)0,(OS_STK*)&LED_TASK_STK[LED_STK_SIZE-1],LED_TASK_PRIO);			 //LED			    				   
 	OSTaskCreate(adc_task,(void *)0,(OS_STK*)&ADC_TASK_STK[ADC_STK_SIZE-1],ADC_TASK_PRIO);	 		 //adc  
 	OSTaskCreate(lcd_task,(void *)0,(OS_STK*)&LCD_TASK_STK[LCD_STK_SIZE-1],LCD_TASK_PRIO);	         //����������
 	OSTaskCreate(ctr_task,(void *)0,(OS_STK*)&CTR_TASK_STK[CTR_STK_SIZE-1],CTR_TASK_PRIO);	  		 //��������		   
// 	OSTaskCreate(clear_task,(void *)0,(OS_STK*)&CLEAR_TASK_STK[CLEAR_STK_SIZE-1],CLEAR_TASK_PRIO);	 //���������				   
 	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����. 				   
// 	OSTaskSuspend(CLEAR_TASK_PRIO);	//����LCD��ʼ����. 
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}	  

//�Լ���������������
void clear_task(void *pdata)
{	
    RCC_ClocksTypeDef get_rcc_clock;    //��ȡϵͳʱ��״̬
    pdata = pdata;
    delay_ms(500);
    RCC_GetClocksFreq(&get_rcc_clock);  //�����ʱ��Ϳ����ڽṹ��get_rcc_clock�п������������ʱ����
	for(;;)
	{
        Clear1();
        Clear2();
        Clear3();
        Clear4();
        Clear5();
 		delay_ms(500);
        OSTaskResume(LCD_TASK_PRIO);    //�ָ�����
        OSTaskSuspend(CLEAR_TASK_PRIO);	//������ʼ����
	}
}


