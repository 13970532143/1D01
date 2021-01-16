#ifndef  COMMON_H
#define  COMMON_H

#include "includes.h"

//#define ALL         250
#define MAX_PULSE  10000
#define MIN_PULSE  0
#define MAX2_PULUSE 6000
#define Vacuum_value        50      //���״ֵ̬
#define Atmospheric_value   99      //��ѹ
#define VacCtr_ON       900         //
#define VacCtr_OFF      0


//�ṹ������
typedef struct System_Variables		//ϵͳ����
{
    u8 Language;		    //��ǰ����
    u8 BEEP_sta  ;          //��Ļ������״̬
    u8 Screen;			    //��ǰҳ��
    u8 Density;             //Ũ��
    u8 work_mode;           //����ģʽ
    u32 O3bulk;             //�������
    u32 Dosage;             //��������
    u16 Countdown;          //����ʱ
    u8 Set_vac;             //�趨��ѹ��С
    float Adc_value[5];     //ADC�ɼ�����ֵ
    u8 work_sta;            //����״̬ 0-����״̬  1-������� 2-��ѹ����״̬
    u8 H2O_countdowm;       //ˮ��ģʽ����ʱ     0��ʱ���ʾ������1-��ʼ 2- ��ͣ
    u8 test_sta;            //����״̬
    u8 Vac_Open;            //��ѹ����
    u8 Job_step;            //��������
    u8 Work_Down;           //����������ʱ״̬
    u8 work_down_time;      //����������ʱʱ��
    u8 clear ;
    u8 Error;
} SYStem_Variables;

volatile extern SYStem_Variables sys_var;


//�洢��ַ
enum SAVE_IP
{
    ERPIP_Language = 8,     //����
    ERPIP_BEEP      = 16,   //��Ļ������״̬
    ERRIP_Density_P = 28,   //Ũ�Ȳ���
};


//����ģʽ
enum Work_Mode
{
    O3Bag = 1,      //�����״�
    infusionBottle, //��Һƿ
    infusionBag,    //��Һ��
    O3Hydrate,      //����ˮ
    suctionCup,     //��ѹ�ֱ�
    ration,         //��������
    injector,       //ע����

};
enum Language           //����
{
    Engliah = 0,        //Ӣ
    Deutush = 1,        //��
    Espanol,            //��
    Pyccknn,            //��
    Francaise,          //��
    Chinese,            //��
};
//��׼���� ��Ӣ�
enum Screen
{
    S_Welcome       = 0,		//��ӭ����
    S_HOME          = 6,	    //HOME����
    S_O3Bag         = 8,	    //�����״�
    S_IFBottle      = 10,        //��Һƿ
    S_IFBAG         = 12,	    //��Һ��
    S_O3Hydrate     = 14,	    //����ˮ��
    S_SuctionCup    = 16,	    //��ѹ�ֱ�
    S_Ration        = 18,		//��������
    S_Injector      = 20,		//ע����ģʽ
    S_Setting       = 22,		//���ý���
    S_Language      = 2,		//���Խ���
    S_Administrator = 24,       //����Ա����
    S_ProSet        = 26,       //�����޸�
    S_Information   = 28,       //�豸��Ϣ����
    S_Test          = 92,        //���Խ���
    S_ERROR         = 29,       //���󱨾�����
};

enum ADC_TypeDef
{
    voltage_5v = 0,         //5V��ѹ
    voltage_24v = 1,        //24V��ѹ
    ozonizer_t  = 2,        //�������¶�
    vacuum_v    = 3,        //��ѹ��С
    cooling_fin = 4,        //ɢ��Ƭ�¶�
};


extern u16 Density_P[80];           //Ũ�Ȳ���
extern u16 Density_Adj_P[9];        //У׼����

void SoftDelayms(unsigned short delay);
void ALL_Init(void);		//���еĳ�ʼ��
void Map_Density(u16 *data);

#endif

