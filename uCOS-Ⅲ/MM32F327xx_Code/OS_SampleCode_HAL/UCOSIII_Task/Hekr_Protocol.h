/******************************************************************************
 * @file    herk_protocol.h
 * @author  
 * @version 
 * @date    
 * @brief   ......
 ******************************************************************************
 * @attention
 * 
 * THE EXISTING FIRMWARE IS ONLY FOR REFERENCE, WHICH IS DESIGNED TO PROVIDE
 * CUSTOMERS WITH CODING INFORMATION ABOUT THEIR PRODUCTS SO THEY CAN SAVE
 * TIME. THEREFORE, MINDMOTION SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGES ABOUT ANY CLAIMS ARISING OUT OF THE CONTENT OF SUCH
 * HARDWARE AND/OR THE USE OF THE CODING INFORMATION CONTAINED HEREIN IN
 * CONNECTION WITH PRODUCTS MADE BY CUSTOMERS.
 * <H2><CENTER>&COPY; COPYRIGHT 2020 MINDMOTION </CENTER></H2>
******************************************************************************/


/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef	_Hekr_Protocol_H_
#define	_Hekr_Protocol_H_


// Hekr USER API **************************************************************

// ʹ��ǰҪ�����û�����Ҫ���������  
// ����ж������ȳ�����  ȡ�����
// #define User_Max_Len 0x0F

//���봮�ڽ��յ���������  
//����ֵ��ͷ�ļ� RecvData_Handle_Code
//���ݱ����ڶ�Ӧ������ Valid_Data �� Module_Status
//unsigned char Hekr_RecvData_Handle(unsigned char* data);

//���ü���ѯhekrģ��״̬ ������ֵ��ͷ�ļ� Hekr_Module_Control_Code
//״ֵ̬������Module_Status������
//void Hekr_Module_Control(unsigned char data);


//�ϴ��û���Ч����
//���ݴ����Valid_Data������ len Ϊ�û����ݳ���  ����֡����
//void Hekr_ValidData_Upload(unsigned char len);


//����޸Ĵ�������Ҫ�޸Ĵ˺���  ����Ӧͷ�ļ�
//static void Hekr_Send_Byte(unsigned char ch);
//
// Э����ַ  http://docs.hekr.me/protocol/
// BUG ����  pengyu.zhang@hekr.me
//					 965006619@qq.com
//*****************************************************************************


#ifdef __cplusplus
extern "C" {
#endif


#undef  EXTERN


#ifdef  __HERK_PROTOCOL_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes -----------------------------------------------------------------*/
#include "HAL_conf.h"
#include "HAL_device.h"


/* Exported constants -------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/


/* Exported functions -------------------------------------------------------*/


#define User_Max_Len 0x0F


extern unsigned char Hekr_Send_Buffer[User_Max_Len+5];
extern unsigned char Valid_Data[User_Max_Len];
extern unsigned char Module_Status[20];

#define Hekr_Frame_Header 0x48u

//*************************************************************************
//Hekr ֡��ʽ
//*************************************************************************

//ͨ��֡ͷ��ʽ 
typedef struct
{
	unsigned char header;
	unsigned char length;
	unsigned char type;
	unsigned char number;
}General_header;

//ģ���ѯ֡��ʽ
typedef struct
{
	//ͨ��֡ͷ
	General_header header;
	//��Ч����
	unsigned char CMD;
	unsigned char Reserved;
	//��У��
	unsigned char SUM;
}Module_Query_Frame; 

//ģ��Ӧ��֡��ʽ
typedef struct
{
	//ͨ��֡ͷ
	General_header header;
	//��Ч����
	unsigned char CMD;
	unsigned char Mode;
	unsigned char WIFI_Status;
	unsigned char Cloud_Status;
	unsigned char Signal_Strength;
	unsigned char Reserved;
	//��У��
	unsigned char SUM;
}Module_Response_Frame; 

//����֡��ʽ
typedef struct
{
	//ͨ��֡ͷ
	General_header header;
	//��Ч����
	unsigned char Error_Code;
	unsigned char Reserved;
	//��У��
	unsigned char SUM;
}Error_Frame; 

//LED ����֡��ʽ
typedef struct
{
	//ͨ��֡ͷ
	General_header header;
	//��Ч����
	unsigned char CMD;
	unsigned char Change_Rate;
	unsigned char Brightness;
	unsigned char Color_Temperature;
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char Reserved;
	//��У��
	unsigned char SUM;
}Led_Control_Frame;


//*************************************************************************
//Hekr ������ֵ
//*************************************************************************

//Hekr��֡����
typedef	enum
{
	Module_Query_Frame_Length = 0x07,
	Module_Response_Frame_Length = 0x0B,
	Led_Control_Frame_Length = 0x0E,
	Error_Frame_Length = 0x07
}All_Frame_Length;

//Hekr��֡����
typedef	enum
{
	Device_Upload_Type = 0x01,
	Module_Download_Type = 0x02,
	Module_Operation_Type = 0xFE,
	Error_Frame_Type = 0xFF
}All_Frame_Type;

//Hekr������ȡֵ
typedef	enum
{
	Error_Operation = 0x01,
	Error_Sum_Check = 0x02,
	Error_Data_Range = 0x03,
	Error_No_CMD = 0xFF
}All_Error_Value;

//Hekr���ݴ�����ֵ
typedef	enum
{
	RecvData_SumCheckErr = 0x01,
	Last_Frame_Send_Err = 0x02,
	MCU_Upload_ACK = 0x03,
	Valid_Data_Update = 0x04,
	RecvData_Useless = 0x05,
	Hekr_Module_State_Update = 0x06
}RecvData_Handle_Code;

//Hekrģ�������
typedef	enum
{
	Module_Query = 0x01,
	Module_Restart = 0x02,
	Module_Recover = 0x03,
	Hekr_Config = 0x04
}Hekr_Module_Control_Code;

//Hekrģ��״̬��
typedef	enum
{
	STA_Mode = 0x01,
	Hekr_Config_Mode = 0x02,
	AP_Mode = 0x03,
	STA_AP_Mode = 0x04,
	RF_OFF_Mode = 0x05
}Hekr_Module_Work_Code;

//Hekr WIFI״̬��
typedef	enum
{
	Router_Connected = 0x01,
	Router_Connected_Fail = 0x02,
	Router_Connecting = 0x03,
	Password_Err = 0x04,
	No_Router = 0x05,
	Router_Time_Over = 0x06
}Hekr_Module_WIFI_Code;

//Hekr Cloud״̬��
typedef	enum
{
	Cloud_Connected = 0x01,
	DNS_Fail = 0x02,
	Cloud_Time_Over = 0x03
}Hekr_Module_Cloud_Code;

/*������������������*/
typedef	enum
{
	LED_Query = 0x00,						      //��ѯ�豸��ǰ״̬
	LED_Preset = 0x01,			          //����������ȫ����Ч���л���Ԥ��״̬
	LED_PowerONOFF = 0x02,				    //���صƾ�
	LED_Bright_Control = 0x03,			  //�������ȵ���Ӧֵ
	LED_Bright_UP = 0x04,			        //��������
	LED_Bright_DOWN = 0x05,			      //��������
	LED_Color_Temperature = 0x06,			//����ɫ�µ���Ӧֵ
	LED_Color_Chroma = 0x07,			    //��ɫ�ʶȵ���Ӧֵ
	LED_Recover_LastShutdown = 0x08	  //�ָ��ϴιر�ʱ��״̬����������ɫ��ɫ��
}LED_Control_Code;

//*************************************************************************
//�����б�
//*************************************************************************

// Hekr USER API 
unsigned char Hekr_RecvData_Handle(unsigned char* data);
void Hekr_Module_Control(unsigned char data);
void Hekr_ValidData_Upload(unsigned char len);

//����޸Ĵ�������Ҫ�޸Ĵ˺���
static void Hekr_Send_Byte(unsigned char ch);

// Static Function
static void Hekr_Send_Frame(unsigned char *data);
static unsigned char Sum_Check_Is_Err(unsigned char* data);
static void Err_Response(unsigned char data);
static unsigned char Sum_Calculate(unsigned char* data);
static void Hekr_ValidData_Copy(unsigned char* data);
static void Hekr_Module_State_Copy(unsigned char* data);

#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
