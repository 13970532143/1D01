#ifndef  HIM_LCD_H
#define  HIM_LCD_H
#include "includes.h"

//有关新瑞达屏的定义
/*
说明：
BT 开头的为按键控件
ED  开头的为数据变量控件
VAR 开头的为变量图标控件
VAL 开头的为基本图形控件
STR 开头的文本控件

*/



#define BT_NUM_ET           0x001E  //显示框按钮

#define	BT_W_WEL	        0x0001	//开机控件按钮
#define BT_W_TEST           0x000F  //生产人员测试按钮

#define	VAR_SR	            0x0100	//Standby Ready
#define	VAR_Tens	        0x0108	//浓度显示十位数
#define	VAR_units	        0x010C	//浓度显示个位数
#define ED_Down_time        0x0870

#define TXT_Ver_A           0x0600
#define TXT_Ver_B           0x0610
#define ED_Ver_E            0x0620      //开机进度数值
#define BAS_W_E             0x0630      //开机进度条
#define BAS_W_Bar           0x1400


#define	BT_M_O3Bag	        0x0002	//三氧套袋模式按钮
#define	BT_M_InfusionBottle	0x0003	//输液瓶按钮
#define	BT_M_InfusionBag	0x0004	//输液袋按钮
#define	BT_M_O3Hydrate	    0x0005	//三氧水化按钮
#define	BT_M_SuctionCup	    0x0006	//负压罩杯模式按钮
#define	BT_M_Ration	        0x0007	//定量供气按钮
#define	BT_M_Injector	    0x0008	//注射器模式按钮
#define	BT_M_Settings	    0x000A	//系统设置按钮
//三氧套袋
#define	BT_OB_0	            0x0010	//键盘0按钮
#define	BT_OB_1	            0x0011	//键盘1按钮
#define	BT_OB_2	            0x0012	//键盘2按钮
#define	BT_OB_3	            0x0013	//键盘3按钮
#define	BT_OB_4	            0x0014	//键盘4按钮
#define	BT_OB_5	            0x0015	//键盘5按钮
#define	BT_OB_6	            0x0016	//键盘6按钮
#define	BT_OB_7	            0x0017	//键盘7按钮
#define	BT_OB_8	            0x0018	//键盘8按钮
#define	BT_OB_9	            0x0019	//键盘9按钮
#define	BT_OB_Back	        0x001A	//键盘退位按钮
#define	BT_OB_Enter	        0x001B 	//键盘enter按钮
#define	BT_OB_Concentration	0x001C	//浓度按钮
#define	BT_OB_Vacuo	        0x001D	//真空按钮
#define	BT_OB_Home	        0x001F	//返回主界面按钮
			
//#define	VAR_OB_C	        0x0100	//浓度指示灯
//#define	VAR_OB_V	        0x0104	//真空指示灯
//#define	VAR_OB_Tens	        0x0108	//浓度显示十位数
//#define	VAR_OB_units	    0x010C	//浓度显示个位数


//#define VAR_OB_TC           0x1410       //浓度字符
//#define VAR_OB_TV           0x0320        //真空字符

#define BAS_OB_TM           0x1200          //模式显示            
#define	BAS_OB_C	0x0310	//浓度控件基本图形
#define	BAS_OB_V	0x0320	//真空控件基本图形
#define	BAS_OB_Cnum	        0x1300	//浓度控件基本图形
			
//输液瓶           
#define	BT_BT_0	            0x0020	//键盘0按钮
#define	BT_BT_1	            0x0021	//键盘1按钮
#define	BT_BT_2	            0x0022	//键盘2按钮
#define	BT_BT_3	            0x0023	//键盘3按钮
#define	BT_BT_4	            0x0024	//键盘4按钮
#define	BT_BT_5	            0x0025	//键盘5按钮
#define	BT_BT_6	            0x0026	//键盘6按钮
#define	BT_BT_7	            0x0027	//键盘7按钮
#define	BT_BT_8	            0x0028	//键盘8按钮
#define	BT_BT_9	            0x0029	//键盘9按钮
#define	BT_BT_Back	        0x002A	//键盘退位按钮
#define	BT_BT_Enter	        0x002B 	//键盘enter按钮
#define	BT_BT_Concentration	0x002C	//浓度按钮
#define	BT_BT_Vacuo	        0x002D	//真空按钮
#define	BT_BT_Home	        0x002F	//返回主界面按钮
			
//#define	VAR_BT_C	        0x0110	//浓度指示灯
//#define	VAR_BT_V	        0x0114	//压力指示灯
//#define	VAR_BT_Tens	        0x0118	//浓度显示十位数
//#define	VAR_BT_units	    0x011C	//浓度显示个位数

//#define BAS_BT_TM           0x0338          //模式显示
//#define VAR_BT_TC           0x0330       //浓度字符
//#define VAR_BT_TV           0x0340        //压力字符

#define BAS_BT_TM           0x1210         //模式显示       
#define	BAS_BT_C	0x0330	//浓度控件基本图形
#define	BAS_BT_V	0x0340	//压力控件基本图形
#define	BAS_BT_Vbar	        0x0350	//压力条
#define	BAS_BT_Cnum	        0x1310	//浓度显示框控基本图形	


//输液袋			
#define	BT_BG_0	            0x0030	//键盘0按钮
#define	BT_BG_1	            0x0031	//键盘1按钮
#define	BT_BG_2	            0x0032	//键盘2按钮
#define	BT_BG_3	            0x0033	//键盘3按钮
#define	BT_BG_4	            0x0034	//键盘4按钮
#define	BT_BG_5	            0x0035	//键盘5按钮
#define	BT_BG_6	            0x0036	//键盘6按钮
#define	BT_BG_7	            0x0037	//键盘7按钮
#define	BT_BG_8	            0x0038	//键盘8按钮
#define	BT_BG_9	            0x0039	//键盘9按钮
#define	BT_BG_Back	        0x003A	//键盘退位按钮
#define	BT_BG_Enter	        0x003B 	//键盘enter按钮
//#define	BT_BG_Concentration	0x003C	//浓度按钮
#define	BT_BG_Vacuo	        0x003D	//体积按钮
#define	BT_BG_Work	        0x003C	//切换工作状态按钮
#define	BT_BG_Home	        0x003F	//返回主界面按钮
			
//#define	VAR_BG_C	        0x0120	//浓度指示灯 。。。。。。。。、、、
//#define	VAR_BG_Cnum	        0x0124	//浓度指示灯
//#define	VAR_BG_Tens	        0x0128	//浓度显示十位数
//#define	VAR_BG_units        0x012C	//浓度显示十位数


#define BAS_BG_TC           0x1120       //浓度字符
#define BAS_BG_TV           0x1130        //体积字符
#define BAS_BG_TQ           0x1140        //剂量字符

			
//#define	BAS_BG_C	    0x0360	//浓度控件基本图形

#define BAS_BG_TM           0x1220          //模式显示
#define	BAS_BG_V	        0x0370	//体积控件基本图形
#define	BAS_BG_Cnum	        0x1320	//浓度显示框控基本图形		
    
#define	TXT_BG_V	        0x0500	//体积数值显示文本
#define	TXT_BG_Dosage	    0x0510	//剂量数值显示文本
		
#define	BAS_BG_Work	        0x0700	//工作状态显示
//臭氧水化			
#define	BT_H_0	            0x0040	//键盘0按钮
#define	BT_H_1	            0x0041	//键盘1按钮
#define	BT_H_2	            0x0042	//键盘2按钮
#define	BT_H_3	            0x0043	//键盘3按钮
#define	BT_H_4	            0x0044	//键盘4按钮
#define	BT_H_5	            0x0045	//键盘5按钮
#define	BT_H_6	            0x0046	//键盘6按钮
#define	BT_H_7	            0x0047	//键盘7按钮
#define	BT_H_8	            0x0048	//键盘8按钮
#define	BT_H_9	            0x0049	//键盘9按钮
#define	BT_H_Back	        0x004A	//键盘退位按钮
#define	BT_H_Enter	        0x004B 	//键盘enter按钮
#define	BT_H_Concentration	0x004C	//浓度按钮
#define	BT_H_Work	        0x004E	//切换工作状态按钮
#define	BT_H_Home	        0x004F	//返回主界面按钮
			
//#define	VAR_H_Tens	        0x0130	//浓度显示十位数
//#define	VAR_H_units	        0x0134	//浓度显示个位数
//#define	VAR_H_Cnum	        0x0138	//浓度显示个位数

#define BAS_H_TC            0x1150      //浓度字符


#define BAS_H_TM            0x1230          //模式显示
#define	BAS_H_C	            0x0380	//浓度控件基本图形
#define	BAS_H_Cnum	        0x1330	//浓度显示框控基本图形	

#define	TXT_H_Min	        0x0520	//工作倒计时--分
#define	TXT_H_Sec	        0x0530	//工作倒计时--秒
			
#define	BAS_H_Work	        0x0710	//工作状态显示
//负压罩杯			
#define	BT_SC_0	            0x0050	//键盘0按钮
#define	BT_SC_1	            0x0051	//键盘1按钮
#define	BT_SC_2	            0x0052	//键盘2按钮
#define	BT_SC_3	            0x0053	//键盘3按钮
#define	BT_SC_4	            0x0054	//键盘4按钮
#define	BT_SC_5	            0x0055	//键盘5按钮
#define	BT_SC_6	            0x0056	//键盘6按钮
#define	BT_SC_7	            0x0057	//键盘7按钮
#define	BT_SC_8	            0x0058	//键盘8按钮
#define	BT_SC_9	            0x0059	//键盘9按钮
#define	BT_SC_Back	        0x005A	//键盘退位按钮
#define	BT_SC_Enter	        0x005B 	//键盘enter按钮
#define	BT_SC_Concentration	0x005C	//浓度按钮
#define	BT_SC_V	            0x005D	//压力按钮
#define	BT_SC_Work	        0x005E	//切换工作状态按钮
#define	BT_SC_Home	        0x005F	//返回主界面按钮
#define	BT_SC_ADD	        0x0061	//加按钮
#define	BT_SC_DEC	        0x0060	//减按钮
			
//#define	VAR_SC_Tens	        0x0138	//浓度显示十位数
//#define	VAR_SC_units	    0x013C	//浓度显示个位数


#define BAS_SC_TC           0x1160     //浓度字符
#define BAS_SC_TV           0x1170        //压力字符


//#define	BAS_SC_C	    0x0390	//浓度控件基本图形
//#define	BAS_SC_V	    0x03A0	//压力控件基本图形
#define BAS_SC_TM           0x1240          //模式显示
#define	BAS_SC_Vbar	        0x03B0	//压力条
#define	BAS_SC_Cnum	        0x1340	//浓度显示框控基本图形	

#define	BAS_SC_Work	        0x0720	//工作状态显示
                
//定量供气			
#define	BT_RT_0	            0x0070	//键盘0按钮
#define	BT_RT_1	            0x0071	//键盘1按钮
#define	BT_RT_2	            0x0072	//键盘2按钮
#define	BT_RT_3	            0x0073	//键盘3按钮
#define	BT_RT_4	            0x0074	//键盘4按钮
#define	BT_RT_5	            0x0075	//键盘5按钮
#define	BT_RT_6	            0x0076	//键盘6按钮
#define	BT_RT_7	            0x0077	//键盘7按钮
#define	BT_RT_8	            0x0078	//键盘8按钮
#define	BT_RT_9	            0x0079	//键盘9按钮
#define	BT_RT_Back	        0x007A	//键盘退位按钮
#define	BT_RT_Enter	        0x007B 	//键盘enter按钮
#define	BT_RT_Concentration	0x007C	//浓度按钮
#define	BT_RT_V	            0x007D	//压力按钮
#define	BT_RT_Work	        0x007E	//切换工作状态按钮
#define	BT_RT_Home	        0x007F	//返回主界面按钮
#define	BT_RT_10ml	        0x1380	//10ml按钮
#define	BT_RT_20ml	        0x1381	//20ml按钮
#define	BT_RT_50ml	        0x1382	//50ml按钮
#define	BT_RT_100ml	        0x1383	//100ml按钮
			
//#define	VAR_RT_Tens	        0x0140	//浓度显示十位数
//#define	VAR_RT_units	    0x0144	//浓度显示个位数


#define BAS_RT_TC           0x1180       //浓度字符
#define BAS_RT_TV           0x1190        //体积字符


//#define	BAS_RT_C	        0x0410	//浓度控件基本图形
#define BAS_RT_TM           0x1250          //模式显示
#define	BAS_RT_V	        0x0420	//体积控件基本图形
#define	BAS_RT_Cnum	        0x1350	//浓度显示框控基本图形	

#define	TXT_RT_V	        0x0540	//体积数值显示文本
		
#define	BAS_RT_Work	        0x0730	//工作状态显示
//注射器			    
#define	BT_IJ_0	            0x0090	//键盘0按钮
#define	BT_IJ_1	            0x0091	//键盘1按钮
#define	BT_IJ_2	            0x0092	//键盘2按钮
#define	BT_IJ_3	            0x0093	//键盘3按钮
#define	BT_IJ_4	            0x0094	//键盘4按钮
#define	BT_IJ_5	            0x0095	//键盘5按钮
#define	BT_IJ_6	            0x0096	//键盘6按钮
#define	BT_IJ_7	            0x0097	//键盘7按钮
#define	BT_IJ_8	            0x0098	//键盘8按钮
#define	BT_IJ_9	            0x0099	//键盘9按钮
#define	BT_IJ_Back	        0x009A	//键盘退位按钮
#define	BT_IJ_Enter	        0x009B 	//键盘enter按钮
#define	BT_IJ_Concentration	0x009C	//浓度按钮
#define	BT_IJ_Work	        0x009E	//切换工作状态按钮
#define	BT_IJ_Home	        0x009F	//返回主界面按钮
			
//#define	VAR_IJ_Tens	        0x0148	//浓度显示十位数
//#define	VAR_IJ_units	    0x014C	//浓度显示个位数

//
#define BAS_IJ_TC           0x11A0       //浓度字符


//#define	BAS_IJ_C	    0x0420	//浓度控件基本图形
#define	BAS_IJ_Cnum	        0x1360	//浓度显示框控基本图形	
#define BAS_IJ_TM           0x0230          //模式显示
#define	BAS_IJ_Work	        0x0740	//工作状态显示
//设置界面			
#define	BT_ST_Language 	    0x1000	//语言按钮
#define	BT_ST_Parameter	    0x1001	//参数设置按钮
#define	BT_ST_Informat	    0x1002	//设备信息
#define	BT_ST_Home	        0x1003	//返回主界面按钮
#define	BT_ST_Voice	        0x1004	//声音控制按钮
#define	BT_ST_Year	        0x0200	//年
#define	TBT_ST_Mon	        0x0204	//月份
#define	BT_ST_Day	        0x0206	//日期
#define	BT_ST_Hours	        0x0208	//时
#define	BT_ST_Min	        0x020A	//分
#define	BT_ST_Sec	        0x020C	//秒


#define	BT_ST_Light	        0x020E	//亮度刻度值

#define	BAS_ST_Voice	    0x0430	//声音基本图形
			



//语言界面			
#define	BT_L_English	    0x1008	//英语控件
#define	BT_L_Deutsch	    0x1009	//德语按钮
#define	BT_L_Espanol	    0x100A 	//西班牙语按钮
#define	BT_L_Pycckn	        0x100B 	//俄语按钮
#define	BT_L_Francais	    0x100C	//法语按钮
#define	BT_L_Chinese	    0x100D	//中文按钮
#define	BT_L_OK	            0x100E	//OK按钮
			
#define	BAS_L_English	    0x0450	//英语图标
#define	BAS_L_Deutsch	    0x0460	//德语图标
#define	BAS_L_Espanol	    0x0470	//西班牙语图标
#define	BAS_L_Pycckn	    0x0480	//俄语图标
#define	BAS_L_Francais	    0x0490	//法语图标
#define	BAS_L_Chinese	    0x04A0	//中文图标


//管理员界面
#define BT_AM_User          0x108C
#define BT_AM_Pswd          0x108D  //密码
#define BT_AM_Login         0x108E  //登录

#define	BT_AM_0	            0x1080	//键盘0按钮
#define	BT_AM_1	            0x1081	//键盘1按钮
#define	BT_AM_2	            0x1082	//键盘2按钮
#define	BT_AM_3	            0x1083	//键盘3按钮
#define	BT_AM_4	            0x1084	//键盘4按钮
#define	BT_AM_5	            0x1085	//键盘5按钮
#define	BT_AM_6	            0x1086	//键盘6按钮
#define	BT_AM_7	            0x1087	//键盘7按钮
#define	BT_AM_8	            0x1088	//键盘8按钮
#define	BT_AM_9	            0x1089	//键盘9按钮
#define	BT_AM_Back	        0x108A	//键盘退位按钮
#define	BT_AM_Enter	        0x108B 	//键盘enter按钮
#define	BT_AM_Home	        0x108F 	//键盘home按钮

//#define VAR_AM_Adm          0x0244   //管理员字符
//#define VAR_AM_Login        0x0248   //登录字符

#define BAS_AM_User         0x0900
#define BAS_AM_Pswd         0x0910

#define TXT_AM_User         0x05B0
#define TXT_AM_Pswd         0x05C0



//浓度校准界面
#define BT_CK_C             0x109C     //浓度
#define BT_CK_P             0x109D  //参数
#define BT_CK_Check         0x109E  //校验

#define	BT_CK_0             0x1090	//键盘0按钮
#define	BT_CK_1	            0x1091	//键盘1按钮
#define	BT_CK_2	            0x1092	//键盘2按钮
#define	BT_CK_3	            0x1093	//键盘3按钮
#define	BT_CK_4	            0x1094	//键盘4按钮
#define	BT_CK_5	            0x1095	//键盘5按钮
#define	BT_CK_6	            0x1096	//键盘6按钮
#define	BT_CK_7	            0x1097	//键盘7按钮
#define	BT_CK_8	            0x1098	//键盘8按钮
#define	BT_CK_9	            0x1099	//键盘9按钮
#define	BT_CK_Back	        0x109A	//键盘退位按钮
#define	BT_CK_Enter	        0x109B 	//键盘enter按钮
#define	BT_CK_Home	        0x109F 	//键盘home按钮

//#define VAR_CK_Adm        0x0240   //管理员字符
//#define VAR_CK_Login      0x0244   //登录字符

#define BAS_CK_C            0x0920
#define BAS_CK_P            0x0930
//#define BAS_CK_Check        0x0940


#define TXT_CK_C            0x05D0
#define TXT_CK_P            0x05E0

//设备信息界面
#define BT_DI_Exit          0x1100
#define BT_DI_Exit2         0x1110


//测试界面
#define BT_TS_S             0x1070  
#define BT_TS_E             0x1071
#define TXT_TS_FLASH        0x0800  
#define TXT_TS_EEPROM       0x0810
#define TXT_TS_VAC          0x0820
#define TXT_TS_TEMP         0x0830
#define TXT_TS_TEMP2        0x0840
#define TXT_TS_5V           0x0850
#define TXT_TS_24V          0x0860


//报警界面
#define BT_ERR_Eixt         0x1112
#define BAS_ERR_Err         0x0950
#define BAS_ERR_Ifo         0x0960



#endif



