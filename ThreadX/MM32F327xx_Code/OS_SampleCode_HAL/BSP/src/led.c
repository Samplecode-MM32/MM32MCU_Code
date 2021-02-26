/******************************************************************************
 * @file    led.c
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
#define _LED_C_


/* Includes -----------------------------------------------------------------*/
#include "led.h"
#include "hal_conf.h"


/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/


/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOB, ENABLE);
    GPIO_StructInit(&GPIO_InitStruct);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_15);                      //Disable JTDI   AF to  AF15
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_15);                       //Disable JTDO/TRACESWO   AF to  AF15
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_15);                       //Disable NJRST   AF to  AF15
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_15);                       //Disable AF Funtion   AF to  AF15
    GPIO_InitStruct.GPIO_Pin  =  GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin  = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    LED1_OFF();
    LED2_OFF();
    LED3_OFF();
    LED4_OFF();

    LED1_ON();
    LED2_ON();
    LED3_ON();
    LED4_ON();

}

/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
