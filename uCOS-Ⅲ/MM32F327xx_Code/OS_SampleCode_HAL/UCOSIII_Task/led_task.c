/******************************************************************************
 * @file    LED_TASK.c
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


#define _LED_TASK_C_


/* Includes -----------------------------------------------------------------*/
#include "led_task.h"
#include "sys.h"
#include "delay.h"
#include "uart.h"


/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/


/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/


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


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void BSP_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
	//Uart3_init();
    uart_initwBaudRate(115200);
	delay_init();  
	LED_Init();
}

//任务控制块
OS_TCB Led0TaskTCB;
//任务堆栈	
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void led0_task(void *p_arg)
{
	OS_ERR err;
	p_arg = p_arg;
	while(1)
	{
		LED4_TOGGLE();
        UART1_SendChar(0x55);
		OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err); //延时200ms
		LED4_TOGGLE();
		OSTimeDlyHMSM(0,0,0,800,OS_OPT_TIME_HMSM_STRICT,&err); //延时500ms
	}
}


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
