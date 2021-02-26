/******************************************************************************
 * @file    led_task.h
 * @author  
 * @version 
 * @date    
 * @brief   ......
 ******************************************************************************
 *  @attention
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
#ifndef LED_TASK_H_
#define LED_TASK_H_


#undef  EXTERN


#ifdef  __BSP_LED_TASK_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes -----------------------------------------------------------------*/
#include "includes.h"

//任务优先级
#define LED0_TASK_PRIO		4u
//任务堆栈大小	
#define LED0_STK_SIZE 		128u
//任务控制块
extern OS_TCB Led0TaskTCB;
//任务堆栈	
extern CPU_STK LED0_TASK_STK[LED0_STK_SIZE];

void led0_task(void *p_arg);
#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/

