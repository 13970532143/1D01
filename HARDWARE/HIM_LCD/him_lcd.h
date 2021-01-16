#ifndef  HIM_LCD_H
#define  HIM_LCD_H
#include "includes.h"

//�й���������Ķ���
/*
˵����
BT ��ͷ��Ϊ�����ؼ�
ED  ��ͷ��Ϊ���ݱ����ؼ�
VAR ��ͷ��Ϊ����ͼ��ؼ�
VAL ��ͷ��Ϊ����ͼ�οؼ�
STR ��ͷ���ı��ؼ�

*/



#define BT_NUM_ET           0x001E  //��ʾ��ť

#define	BT_W_WEL	        0x0001	//�����ؼ���ť
#define BT_W_TEST           0x000F  //������Ա���԰�ť

#define	VAR_SR	            0x0100	//Standby Ready
#define	VAR_Tens	        0x0108	//Ũ����ʾʮλ��
#define	VAR_units	        0x010C	//Ũ����ʾ��λ��
#define ED_Down_time        0x0870

#define TXT_Ver_A           0x0600
#define TXT_Ver_B           0x0610
#define ED_Ver_E            0x0620      //����������ֵ
#define BAS_W_E             0x0630      //����������
#define BAS_W_Bar           0x1400


#define	BT_M_O3Bag	        0x0002	//�����״�ģʽ��ť
#define	BT_M_InfusionBottle	0x0003	//��Һƿ��ť
#define	BT_M_InfusionBag	0x0004	//��Һ����ť
#define	BT_M_O3Hydrate	    0x0005	//����ˮ����ť
#define	BT_M_SuctionCup	    0x0006	//��ѹ�ֱ�ģʽ��ť
#define	BT_M_Ration	        0x0007	//����������ť
#define	BT_M_Injector	    0x0008	//ע����ģʽ��ť
#define	BT_M_Settings	    0x000A	//ϵͳ���ð�ť
//�����״�
#define	BT_OB_0	            0x0010	//����0��ť
#define	BT_OB_1	            0x0011	//����1��ť
#define	BT_OB_2	            0x0012	//����2��ť
#define	BT_OB_3	            0x0013	//����3��ť
#define	BT_OB_4	            0x0014	//����4��ť
#define	BT_OB_5	            0x0015	//����5��ť
#define	BT_OB_6	            0x0016	//����6��ť
#define	BT_OB_7	            0x0017	//����7��ť
#define	BT_OB_8	            0x0018	//����8��ť
#define	BT_OB_9	            0x0019	//����9��ť
#define	BT_OB_Back	        0x001A	//������λ��ť
#define	BT_OB_Enter	        0x001B 	//����enter��ť
#define	BT_OB_Concentration	0x001C	//Ũ�Ȱ�ť
#define	BT_OB_Vacuo	        0x001D	//��հ�ť
#define	BT_OB_Home	        0x001F	//���������水ť
			
//#define	VAR_OB_C	        0x0100	//Ũ��ָʾ��
//#define	VAR_OB_V	        0x0104	//���ָʾ��
//#define	VAR_OB_Tens	        0x0108	//Ũ����ʾʮλ��
//#define	VAR_OB_units	    0x010C	//Ũ����ʾ��λ��


//#define VAR_OB_TC           0x1410       //Ũ���ַ�
//#define VAR_OB_TV           0x0320        //����ַ�

#define BAS_OB_TM           0x1200          //ģʽ��ʾ            
#define	BAS_OB_C	0x0310	//Ũ�ȿؼ�����ͼ��
#define	BAS_OB_V	0x0320	//��տؼ�����ͼ��
#define	BAS_OB_Cnum	        0x1300	//Ũ�ȿؼ�����ͼ��
			
//��Һƿ           
#define	BT_BT_0	            0x0020	//����0��ť
#define	BT_BT_1	            0x0021	//����1��ť
#define	BT_BT_2	            0x0022	//����2��ť
#define	BT_BT_3	            0x0023	//����3��ť
#define	BT_BT_4	            0x0024	//����4��ť
#define	BT_BT_5	            0x0025	//����5��ť
#define	BT_BT_6	            0x0026	//����6��ť
#define	BT_BT_7	            0x0027	//����7��ť
#define	BT_BT_8	            0x0028	//����8��ť
#define	BT_BT_9	            0x0029	//����9��ť
#define	BT_BT_Back	        0x002A	//������λ��ť
#define	BT_BT_Enter	        0x002B 	//����enter��ť
#define	BT_BT_Concentration	0x002C	//Ũ�Ȱ�ť
#define	BT_BT_Vacuo	        0x002D	//��հ�ť
#define	BT_BT_Home	        0x002F	//���������水ť
			
//#define	VAR_BT_C	        0x0110	//Ũ��ָʾ��
//#define	VAR_BT_V	        0x0114	//ѹ��ָʾ��
//#define	VAR_BT_Tens	        0x0118	//Ũ����ʾʮλ��
//#define	VAR_BT_units	    0x011C	//Ũ����ʾ��λ��

//#define BAS_BT_TM           0x0338          //ģʽ��ʾ
//#define VAR_BT_TC           0x0330       //Ũ���ַ�
//#define VAR_BT_TV           0x0340        //ѹ���ַ�

#define BAS_BT_TM           0x1210         //ģʽ��ʾ       
#define	BAS_BT_C	0x0330	//Ũ�ȿؼ�����ͼ��
#define	BAS_BT_V	0x0340	//ѹ���ؼ�����ͼ��
#define	BAS_BT_Vbar	        0x0350	//ѹ����
#define	BAS_BT_Cnum	        0x1310	//Ũ����ʾ��ػ���ͼ��	


//��Һ��			
#define	BT_BG_0	            0x0030	//����0��ť
#define	BT_BG_1	            0x0031	//����1��ť
#define	BT_BG_2	            0x0032	//����2��ť
#define	BT_BG_3	            0x0033	//����3��ť
#define	BT_BG_4	            0x0034	//����4��ť
#define	BT_BG_5	            0x0035	//����5��ť
#define	BT_BG_6	            0x0036	//����6��ť
#define	BT_BG_7	            0x0037	//����7��ť
#define	BT_BG_8	            0x0038	//����8��ť
#define	BT_BG_9	            0x0039	//����9��ť
#define	BT_BG_Back	        0x003A	//������λ��ť
#define	BT_BG_Enter	        0x003B 	//����enter��ť
//#define	BT_BG_Concentration	0x003C	//Ũ�Ȱ�ť
#define	BT_BG_Vacuo	        0x003D	//�����ť
#define	BT_BG_Work	        0x003C	//�л�����״̬��ť
#define	BT_BG_Home	        0x003F	//���������水ť
			
//#define	VAR_BG_C	        0x0120	//Ũ��ָʾ�� ����������������������
//#define	VAR_BG_Cnum	        0x0124	//Ũ��ָʾ��
//#define	VAR_BG_Tens	        0x0128	//Ũ����ʾʮλ��
//#define	VAR_BG_units        0x012C	//Ũ����ʾʮλ��


#define BAS_BG_TC           0x1120       //Ũ���ַ�
#define BAS_BG_TV           0x1130        //����ַ�
#define BAS_BG_TQ           0x1140        //�����ַ�

			
//#define	BAS_BG_C	    0x0360	//Ũ�ȿؼ�����ͼ��

#define BAS_BG_TM           0x1220          //ģʽ��ʾ
#define	BAS_BG_V	        0x0370	//����ؼ�����ͼ��
#define	BAS_BG_Cnum	        0x1320	//Ũ����ʾ��ػ���ͼ��		
    
#define	TXT_BG_V	        0x0500	//�����ֵ��ʾ�ı�
#define	TXT_BG_Dosage	    0x0510	//������ֵ��ʾ�ı�
		
#define	BAS_BG_Work	        0x0700	//����״̬��ʾ
//����ˮ��			
#define	BT_H_0	            0x0040	//����0��ť
#define	BT_H_1	            0x0041	//����1��ť
#define	BT_H_2	            0x0042	//����2��ť
#define	BT_H_3	            0x0043	//����3��ť
#define	BT_H_4	            0x0044	//����4��ť
#define	BT_H_5	            0x0045	//����5��ť
#define	BT_H_6	            0x0046	//����6��ť
#define	BT_H_7	            0x0047	//����7��ť
#define	BT_H_8	            0x0048	//����8��ť
#define	BT_H_9	            0x0049	//����9��ť
#define	BT_H_Back	        0x004A	//������λ��ť
#define	BT_H_Enter	        0x004B 	//����enter��ť
#define	BT_H_Concentration	0x004C	//Ũ�Ȱ�ť
#define	BT_H_Work	        0x004E	//�л�����״̬��ť
#define	BT_H_Home	        0x004F	//���������水ť
			
//#define	VAR_H_Tens	        0x0130	//Ũ����ʾʮλ��
//#define	VAR_H_units	        0x0134	//Ũ����ʾ��λ��
//#define	VAR_H_Cnum	        0x0138	//Ũ����ʾ��λ��

#define BAS_H_TC            0x1150      //Ũ���ַ�


#define BAS_H_TM            0x1230          //ģʽ��ʾ
#define	BAS_H_C	            0x0380	//Ũ�ȿؼ�����ͼ��
#define	BAS_H_Cnum	        0x1330	//Ũ����ʾ��ػ���ͼ��	

#define	TXT_H_Min	        0x0520	//��������ʱ--��
#define	TXT_H_Sec	        0x0530	//��������ʱ--��
			
#define	BAS_H_Work	        0x0710	//����״̬��ʾ
//��ѹ�ֱ�			
#define	BT_SC_0	            0x0050	//����0��ť
#define	BT_SC_1	            0x0051	//����1��ť
#define	BT_SC_2	            0x0052	//����2��ť
#define	BT_SC_3	            0x0053	//����3��ť
#define	BT_SC_4	            0x0054	//����4��ť
#define	BT_SC_5	            0x0055	//����5��ť
#define	BT_SC_6	            0x0056	//����6��ť
#define	BT_SC_7	            0x0057	//����7��ť
#define	BT_SC_8	            0x0058	//����8��ť
#define	BT_SC_9	            0x0059	//����9��ť
#define	BT_SC_Back	        0x005A	//������λ��ť
#define	BT_SC_Enter	        0x005B 	//����enter��ť
#define	BT_SC_Concentration	0x005C	//Ũ�Ȱ�ť
#define	BT_SC_V	            0x005D	//ѹ����ť
#define	BT_SC_Work	        0x005E	//�л�����״̬��ť
#define	BT_SC_Home	        0x005F	//���������水ť
#define	BT_SC_ADD	        0x0061	//�Ӱ�ť
#define	BT_SC_DEC	        0x0060	//����ť
			
//#define	VAR_SC_Tens	        0x0138	//Ũ����ʾʮλ��
//#define	VAR_SC_units	    0x013C	//Ũ����ʾ��λ��


#define BAS_SC_TC           0x1160     //Ũ���ַ�
#define BAS_SC_TV           0x1170        //ѹ���ַ�


//#define	BAS_SC_C	    0x0390	//Ũ�ȿؼ�����ͼ��
//#define	BAS_SC_V	    0x03A0	//ѹ���ؼ�����ͼ��
#define BAS_SC_TM           0x1240          //ģʽ��ʾ
#define	BAS_SC_Vbar	        0x03B0	//ѹ����
#define	BAS_SC_Cnum	        0x1340	//Ũ����ʾ��ػ���ͼ��	

#define	BAS_SC_Work	        0x0720	//����״̬��ʾ
                
//��������			
#define	BT_RT_0	            0x0070	//����0��ť
#define	BT_RT_1	            0x0071	//����1��ť
#define	BT_RT_2	            0x0072	//����2��ť
#define	BT_RT_3	            0x0073	//����3��ť
#define	BT_RT_4	            0x0074	//����4��ť
#define	BT_RT_5	            0x0075	//����5��ť
#define	BT_RT_6	            0x0076	//����6��ť
#define	BT_RT_7	            0x0077	//����7��ť
#define	BT_RT_8	            0x0078	//����8��ť
#define	BT_RT_9	            0x0079	//����9��ť
#define	BT_RT_Back	        0x007A	//������λ��ť
#define	BT_RT_Enter	        0x007B 	//����enter��ť
#define	BT_RT_Concentration	0x007C	//Ũ�Ȱ�ť
#define	BT_RT_V	            0x007D	//ѹ����ť
#define	BT_RT_Work	        0x007E	//�л�����״̬��ť
#define	BT_RT_Home	        0x007F	//���������水ť
#define	BT_RT_10ml	        0x1380	//10ml��ť
#define	BT_RT_20ml	        0x1381	//20ml��ť
#define	BT_RT_50ml	        0x1382	//50ml��ť
#define	BT_RT_100ml	        0x1383	//100ml��ť
			
//#define	VAR_RT_Tens	        0x0140	//Ũ����ʾʮλ��
//#define	VAR_RT_units	    0x0144	//Ũ����ʾ��λ��


#define BAS_RT_TC           0x1180       //Ũ���ַ�
#define BAS_RT_TV           0x1190        //����ַ�


//#define	BAS_RT_C	        0x0410	//Ũ�ȿؼ�����ͼ��
#define BAS_RT_TM           0x1250          //ģʽ��ʾ
#define	BAS_RT_V	        0x0420	//����ؼ�����ͼ��
#define	BAS_RT_Cnum	        0x1350	//Ũ����ʾ��ػ���ͼ��	

#define	TXT_RT_V	        0x0540	//�����ֵ��ʾ�ı�
		
#define	BAS_RT_Work	        0x0730	//����״̬��ʾ
//ע����			    
#define	BT_IJ_0	            0x0090	//����0��ť
#define	BT_IJ_1	            0x0091	//����1��ť
#define	BT_IJ_2	            0x0092	//����2��ť
#define	BT_IJ_3	            0x0093	//����3��ť
#define	BT_IJ_4	            0x0094	//����4��ť
#define	BT_IJ_5	            0x0095	//����5��ť
#define	BT_IJ_6	            0x0096	//����6��ť
#define	BT_IJ_7	            0x0097	//����7��ť
#define	BT_IJ_8	            0x0098	//����8��ť
#define	BT_IJ_9	            0x0099	//����9��ť
#define	BT_IJ_Back	        0x009A	//������λ��ť
#define	BT_IJ_Enter	        0x009B 	//����enter��ť
#define	BT_IJ_Concentration	0x009C	//Ũ�Ȱ�ť
#define	BT_IJ_Work	        0x009E	//�л�����״̬��ť
#define	BT_IJ_Home	        0x009F	//���������水ť
			
//#define	VAR_IJ_Tens	        0x0148	//Ũ����ʾʮλ��
//#define	VAR_IJ_units	    0x014C	//Ũ����ʾ��λ��

//
#define BAS_IJ_TC           0x11A0       //Ũ���ַ�


//#define	BAS_IJ_C	    0x0420	//Ũ�ȿؼ�����ͼ��
#define	BAS_IJ_Cnum	        0x1360	//Ũ����ʾ��ػ���ͼ��	
#define BAS_IJ_TM           0x0230          //ģʽ��ʾ
#define	BAS_IJ_Work	        0x0740	//����״̬��ʾ
//���ý���			
#define	BT_ST_Language 	    0x1000	//���԰�ť
#define	BT_ST_Parameter	    0x1001	//�������ð�ť
#define	BT_ST_Informat	    0x1002	//�豸��Ϣ
#define	BT_ST_Home	        0x1003	//���������水ť
#define	BT_ST_Voice	        0x1004	//�������ư�ť
#define	BT_ST_Year	        0x0200	//��
#define	TBT_ST_Mon	        0x0204	//�·�
#define	BT_ST_Day	        0x0206	//����
#define	BT_ST_Hours	        0x0208	//ʱ
#define	BT_ST_Min	        0x020A	//��
#define	BT_ST_Sec	        0x020C	//��


#define	BT_ST_Light	        0x020E	//���ȿ̶�ֵ

#define	BAS_ST_Voice	    0x0430	//��������ͼ��
			



//���Խ���			
#define	BT_L_English	    0x1008	//Ӣ��ؼ�
#define	BT_L_Deutsch	    0x1009	//���ﰴť
#define	BT_L_Espanol	    0x100A 	//�������ﰴť
#define	BT_L_Pycckn	        0x100B 	//���ﰴť
#define	BT_L_Francais	    0x100C	//���ﰴť
#define	BT_L_Chinese	    0x100D	//���İ�ť
#define	BT_L_OK	            0x100E	//OK��ť
			
#define	BAS_L_English	    0x0450	//Ӣ��ͼ��
#define	BAS_L_Deutsch	    0x0460	//����ͼ��
#define	BAS_L_Espanol	    0x0470	//��������ͼ��
#define	BAS_L_Pycckn	    0x0480	//����ͼ��
#define	BAS_L_Francais	    0x0490	//����ͼ��
#define	BAS_L_Chinese	    0x04A0	//����ͼ��


//����Ա����
#define BT_AM_User          0x108C
#define BT_AM_Pswd          0x108D  //����
#define BT_AM_Login         0x108E  //��¼

#define	BT_AM_0	            0x1080	//����0��ť
#define	BT_AM_1	            0x1081	//����1��ť
#define	BT_AM_2	            0x1082	//����2��ť
#define	BT_AM_3	            0x1083	//����3��ť
#define	BT_AM_4	            0x1084	//����4��ť
#define	BT_AM_5	            0x1085	//����5��ť
#define	BT_AM_6	            0x1086	//����6��ť
#define	BT_AM_7	            0x1087	//����7��ť
#define	BT_AM_8	            0x1088	//����8��ť
#define	BT_AM_9	            0x1089	//����9��ť
#define	BT_AM_Back	        0x108A	//������λ��ť
#define	BT_AM_Enter	        0x108B 	//����enter��ť
#define	BT_AM_Home	        0x108F 	//����home��ť

//#define VAR_AM_Adm          0x0244   //����Ա�ַ�
//#define VAR_AM_Login        0x0248   //��¼�ַ�

#define BAS_AM_User         0x0900
#define BAS_AM_Pswd         0x0910

#define TXT_AM_User         0x05B0
#define TXT_AM_Pswd         0x05C0



//Ũ��У׼����
#define BT_CK_C             0x109C     //Ũ��
#define BT_CK_P             0x109D  //����
#define BT_CK_Check         0x109E  //У��

#define	BT_CK_0             0x1090	//����0��ť
#define	BT_CK_1	            0x1091	//����1��ť
#define	BT_CK_2	            0x1092	//����2��ť
#define	BT_CK_3	            0x1093	//����3��ť
#define	BT_CK_4	            0x1094	//����4��ť
#define	BT_CK_5	            0x1095	//����5��ť
#define	BT_CK_6	            0x1096	//����6��ť
#define	BT_CK_7	            0x1097	//����7��ť
#define	BT_CK_8	            0x1098	//����8��ť
#define	BT_CK_9	            0x1099	//����9��ť
#define	BT_CK_Back	        0x109A	//������λ��ť
#define	BT_CK_Enter	        0x109B 	//����enter��ť
#define	BT_CK_Home	        0x109F 	//����home��ť

//#define VAR_CK_Adm        0x0240   //����Ա�ַ�
//#define VAR_CK_Login      0x0244   //��¼�ַ�

#define BAS_CK_C            0x0920
#define BAS_CK_P            0x0930
//#define BAS_CK_Check        0x0940


#define TXT_CK_C            0x05D0
#define TXT_CK_P            0x05E0

//�豸��Ϣ����
#define BT_DI_Exit          0x1100
#define BT_DI_Exit2         0x1110


//���Խ���
#define BT_TS_S             0x1070  
#define BT_TS_E             0x1071
#define TXT_TS_FLASH        0x0800  
#define TXT_TS_EEPROM       0x0810
#define TXT_TS_VAC          0x0820
#define TXT_TS_TEMP         0x0830
#define TXT_TS_TEMP2        0x0840
#define TXT_TS_5V           0x0850
#define TXT_TS_24V          0x0860


//��������
#define BT_ERR_Eixt         0x1112
#define BAS_ERR_Err         0x0950
#define BAS_ERR_Ifo         0x0960



#endif



