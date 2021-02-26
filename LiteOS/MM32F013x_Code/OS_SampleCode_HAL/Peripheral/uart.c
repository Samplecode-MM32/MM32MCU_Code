/******************************************************************************
 * @file    uart.c
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
#define _UART_C_


/* Includes -----------------------------------------------------------------*/
#include <stdio.h>
#include "uart.h"
#include "hal_conf.h"


/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/


/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/


#ifdef __GNUC__

#define PUTCHAR_PROTOTYPE s32 __io_putchar(s32 ch)
#else
#define PUTCHAR_PROTOTYPE s32 fputc(s32 ch, FILE *f)

#endif

#ifdef USE_IAR
PUTCHAR_PROTOTYPE {
    while((UART1->CSR & UART_IT_TXIEN) == 0); //The loop is sent until it is finished
    UART1->TDR = (ch & (u16)0x00FF);
    return ch;
}


#else


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void _sys_exit(s32 x)
{
    x = x;
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
s32 fputc(s32 ch, FILE* f)
{
    while((UART1->CSR & UART_IT_TXIEN) == 0); //The loop is sent until it is finished
    UART1->TDR = (ch & (u16)0x00FF);
    return ch;
}

#endif


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void CONSOLE_Init(u32 baudrate)
{
    //GPIO port set
    GPIO_InitTypeDef GPIO_InitStructure;
    UART_InitTypeDef UART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_UART1, ENABLE);   //enableUART1,GPIOAclock
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);  //
    //UART initialset
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.UART_BaudRate = baudrate;
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;
    UART_InitStructure.UART_StopBits = UART_StopBits_1;//one stopbit
    UART_InitStructure.UART_Parity = UART_Parity_No;//none odd-even  verify bit
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;//No hardware flow control
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx; // receive and sent  mode

    UART_Init(UART1, &UART_InitStructure); //initial uart 1
    UART_Cmd(UART1, ENABLE);                    //enable uart 1

    //UART1_TX   GPIOA.9
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //UART1_RX    GPIOA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/

