/******************************************************************************
 * @file    uart.h
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
******************************************************************************/


/* Define to prevent recursive inclusion ------------------------------------*/
#ifndef __UART_H__
#define __UART_H__


#ifdef __cplusplus
extern "C" {
#endif


#undef  EXTERN


#ifdef  __UART_C__
#define EXTERN
#else
#define EXTERN extern
#endif


/* Includes -----------------------------------------------------------------*/
#include "config.h"


/* Exported constants -------------------------------------------------------*/
/* Exported types -----------------------------------------------------------*/
/* Exported macro -----------------------------------------------------------*/


/* Exported functions -------------------------------------------------------*/
EXTERN void UARTx_Configure(UART_TypeDef           *UARTx,
                            uint32_t                BaudRate,
                            UART_WordLength_TypeDef WordLength,
                            UART_Stop_Bits_TypeDef  StopBits,
                            UART_Parity_TypeDef     Parity);


#ifdef __cplusplus
}
#endif


#endif


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/

