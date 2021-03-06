#ifndef  COMMON_H
#define  COMMON_H

#include "includes.h"

//#define ALL         250
#define MAX_PULSE  10000
#define MIN_PULSE  0
#define MAX2_PULUSE 6000
#define Vacuum_value        50      //真空状态值
#define Atmospheric_value   99      //常压
#define VacCtr_ON       900         //
#define VacCtr_OFF      0


//结构体数据
typedef struct System_Variables		//系统变量
{
    u8 Language;		    //当前语言
    u8 BEEP_sta  ;          //屏幕蜂鸣器状态
    u8 Screen;			    //当前页面
    u8 Density;             //浓度
    u8 work_mode;           //工作模式
    u32 O3bulk;             //臭氧体积
    u32 Dosage;             //臭氧剂量
    u16 Countdown;          //倒计时
    u8 Set_vac;             //设定负压大小
    float Adc_value[5];     //ADC采集的数值
    u8 work_sta;            //工作状态 0-待机状态  1-臭氧输出 2-负压开启状态
    u8 H2O_countdowm;       //水化模式倒计时     0的时候表示结束，1-开始 2- 暂停
    u8 test_sta;            //测试状态
    u8 Vac_Open;            //负压开启
    u8 Job_step;            //工作步骤
    u8 Work_Down;           //出臭氧倒计时状态
    u8 work_down_time;      //出臭氧倒计时时间
    u8 clear ;
    u8 Error;
} SYStem_Variables;

volatile extern SYStem_Variables sys_var;


//存储地址
enum SAVE_IP
{
    ERPIP_Language = 8,     //语言
    ERPIP_BEEP      = 16,   //屏幕蜂鸣器状态
    ERRIP_Density_P = 28,   //浓度参数
};


//工作模式
enum Work_Mode
{
    O3Bag = 1,      //三氧套袋
    infusionBottle, //输液瓶
    infusionBag,    //输液袋
    O3Hydrate,      //臭氧水
    suctionCup,     //负压罩杯
    ration,         //定量供气
    injector,       //注射器

};
enum Language           //语言
{
    Engliah = 0,        //英
    Deutush = 1,        //德
    Espanol,            //西
    Pyccknn,            //俄
    Francaise,          //法
    Chinese,            //中
};
//基准界面 （英语）
enum Screen
{
    S_Welcome       = 0,		//欢迎界面
    S_HOME          = 6,	    //HOME界面
    S_O3Bag         = 8,	    //臭氧套袋
    S_IFBottle      = 10,        //输液瓶
    S_IFBAG         = 12,	    //输液袋
    S_O3Hydrate     = 14,	    //臭氧水化
    S_SuctionCup    = 16,	    //负压罩杯
    S_Ration        = 18,		//定量供气
    S_Injector      = 20,		//注射器模式
    S_Setting       = 22,		//设置界面
    S_Language      = 2,		//语言界面
    S_Administrator = 24,       //管理员界面
    S_ProSet        = 26,       //参数修改
    S_Information   = 28,       //设备信息界面
    S_Test          = 92,        //测试界面
    S_ERROR         = 29,       //错误报警界面
};

enum ADC_TypeDef
{
    voltage_5v = 0,         //5V电压
    voltage_24v = 1,        //24V电压
    ozonizer_t  = 2,        //臭氧管温度
    vacuum_v    = 3,        //负压大小
    cooling_fin = 4,        //散热片温度
};


extern u16 Density_P[80];           //浓度参数
extern u16 Density_Adj_P[9];        //校准参数

void SoftDelayms(unsigned short delay);
void ALL_Init(void);		//所有的初始化
void Map_Density(u16 *data);

#endif

