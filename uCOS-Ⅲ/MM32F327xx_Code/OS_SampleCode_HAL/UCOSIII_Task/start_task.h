/******************************************************************************
 * @file    start_task.h
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
#ifndef START_TASK_H_
#define START_TASK_H_


#ifdef __cplusplus
extern "C" {
#endif


#undef  EXTERN


#ifdef  __START_TASK_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes -----------------------------------------------------------------*/
#include "includes.h"


/* Exported constants -------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/


/* Exported functions -------------------------------------------------------*/


//�������ȼ�
#define START_TASK_PRIO		3u
//�����ջ��С	
#define START_STK_SIZE 		512u
//������ƿ�
extern OS_TCB StartTaskTCB;
//�����ջ	
extern CPU_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *p_arg);


#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
