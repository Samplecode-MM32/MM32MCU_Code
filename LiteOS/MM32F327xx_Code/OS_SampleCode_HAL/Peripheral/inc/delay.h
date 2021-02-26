/******************************************************************************
 * @file    delay.h
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
******************************************************************************/


/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __DELAY_H
#define __DELAY_H


#ifdef __cplusplus
extern "C" {
#endif


#undef  EXTERN


#ifdef  __BSP_DELAY_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes -----------------------------------------------------------------*/
#include "sys.h"


/* Exported constants -------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/


/* Exported functions -------------------------------------------------------*/
extern u32 SystemCoreClock;

void delay_init(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);


#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
