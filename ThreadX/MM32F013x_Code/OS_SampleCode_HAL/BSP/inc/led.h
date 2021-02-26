/******************************************************************************
 * @file    led.h
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
#ifndef __LED_H
#define __LED_H


#ifdef __cplusplus
extern "C" {
#endif


#undef  EXTERN


#ifdef  __BSP_LED_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes -----------------------------------------------------------------*/
#include <string.h>
#include "mm32_device.h"
#include "hal_conf.h"


/* Exported constants -------------------------------------------------------*/
#define LED1_Port  GPIOA
#define LED1_Pin   GPIO_Pin_15
#define LED2_Port  GPIOB
#define LED2_Pin   GPIO_Pin_3
#define LED3_Port  GPIOB
#define LED3_Pin   GPIO_Pin_4
#define LED4_Port  GPIOB
#define LED4_Pin   GPIO_Pin_5


#define LED1_ON()  GPIO_ResetBits(LED1_Port,LED1_Pin)
#define LED1_OFF()  GPIO_SetBits(LED1_Port,LED1_Pin)
#define LED1_TOGGLE()  (GPIO_ReadOutputDataBit(LED1_Port,LED1_Pin))?(GPIO_ResetBits(LED1_Port,LED1_Pin)):(GPIO_SetBits(LED1_Port,LED1_Pin))


#define LED2_ON()  GPIO_ResetBits(LED2_Port,LED2_Pin)
#define LED2_OFF()  GPIO_SetBits(LED2_Port,LED2_Pin)
#define LED2_TOGGLE()  (GPIO_ReadOutputDataBit(LED2_Port,LED2_Pin))?(GPIO_ResetBits(LED2_Port,LED2_Pin)):(GPIO_SetBits(LED2_Port,LED2_Pin))


#define LED3_ON()  GPIO_ResetBits(LED3_Port,LED3_Pin)
#define LED3_OFF()  GPIO_SetBits(LED3_Port,LED3_Pin)
#define LED3_TOGGLE()  (GPIO_ReadOutputDataBit(LED3_Port,LED3_Pin))?(GPIO_ResetBits(LED3_Port,LED3_Pin)):(GPIO_SetBits(LED3_Port,LED3_Pin))


#define LED4_ON()  GPIO_ResetBits(LED4_Port,LED4_Pin)
#define LED4_OFF()  GPIO_SetBits(LED4_Port,LED4_Pin)
#define LED4_TOGGLE()  (GPIO_ReadOutputDataBit(LED4_Port,LED4_Pin))?(GPIO_ResetBits(LED4_Port,LED4_Pin)):(GPIO_SetBits(LED4_Port,LED4_Pin))


typedef enum {
    LED1,
    LED2,
    LED3,
    LED4
} Led_TypeDef;


#undef GLOBAL


/* Exported functions -------------------------------------------------------*/
void LED_Init(void);


#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
