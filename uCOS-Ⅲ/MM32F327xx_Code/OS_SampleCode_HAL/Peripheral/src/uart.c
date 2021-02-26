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


/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/


/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/
u8 Uart3_Recv_Buffer[20];
u8 Uart3_Recv_Count = 0;
u8 Uart3_Recv_STA = 0;


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void UART1_SendChar(u8 ch)
{
	while((UART1->CSR & UART_IT_TXIEN) == 0); //The loop is sent until it is finished
    UART1->TDR = (ch & (u8)0x00FF);
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void uart_initwBaudRate(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    UART_InitTypeDef UART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_UART1, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_7);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_7);

    //UART1_TX   GPIOA.9
    GPIO_StructInit(&GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //UART1_RX    GPIOA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    NVIC_InitStructure.NVIC_IRQChannel = UART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
        
    UART_StructInit(&UART_InitStructure);
    UART_InitStructure.UART_BaudRate = bound;
    UART_InitStructure.UART_WordLength = UART_WordLength_8b;
    UART_InitStructure.UART_StopBits = UART_StopBits_1;                         //one stopbit
    UART_InitStructure.UART_Parity = UART_Parity_No;                            //none odd-even  verify bit
    UART_InitStructure.UART_HardwareFlowControl = UART_HardwareFlowControl_None;//No hardware flow control
    UART_InitStructure.UART_Mode = UART_Mode_Rx | UART_Mode_Tx;                 // receive and sent  mode
    
    UART_ITConfig(UART1,UART_IT_RXIEN,ENABLE);
    UART_Init(UART1, &UART_InitStructure);      //initial uart 1
    UART_Cmd(UART1, ENABLE);                    //enable uart 1
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void UART1_IRQHandler(void)
{
    u8 ch;
	static u8 temp_flag = 0;
	if(UART_GetITStatus(UART1, UART_IT_RXIEN) != RESET) 
	{
		ch =UART_ReceiveData(UART1);
		if(ch == Hekr_Frame_Header)
		{
			temp_flag = 1;
			Uart3_Recv_Count = 0;
		}
		if(temp_flag)
		{
			Uart3_Recv_Buffer[Uart3_Recv_Count++] = ch;
			if(Uart3_Recv_Count > 4 && Uart3_Recv_Count >= Uart3_Recv_Buffer[1])
			{
				Uart3_Recv_STA = 1;
				temp_flag = 0;
				Uart3_Recv_Count = 0;
			}
			if(Uart3_Recv_Count > 15)
			{
				temp_flag = 0;
				Uart3_Recv_Count = 0;
			}
		}
	}
    
}

/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
