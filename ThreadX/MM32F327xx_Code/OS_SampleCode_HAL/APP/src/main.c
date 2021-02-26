/******************************************************************************
 * @file    
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
#define _MAIN_C_


/* Includes -----------------------------------------------------------------*/
#include "led.h"
#include "delay.h"
#include "uart.h"
#include "tx_api.h"


/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/


/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/


TX_THREAD mm32_thread1;



/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void mm32_thread1_entry(ULONG thread_input)
{
    while(1)
    {
        LED1_TOGGLE();
        printf("\r\nmm32 thread1 running...");

        tx_thread_sleep(1000);
    }
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void tx_application_define(void *first_unused_memory)
{
    /* 创建任务 */
    tx_thread_create(
        &mm32_thread1,      /* 任务控制块地址 */
        "mm32 thread1",     /* 任务名称 */
        mm32_thread1_entry, /* 启动任务函数地址 */
        0,                  /* 传递给任务的参数 */
        first_unused_memory,/* 堆栈基地址 */
        1024,               /* 堆栈空间大小 */
        1,                  /* 任务优先级 */
        1,                  /* 任务抢占阈值 */
        TX_NO_TIME_SLICE,   /* 不开启时间片 */
        TX_AUTO_START       /* 创建后立即启动 */
    );
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
int main(void)
{
    LED_Init();
    delay_init();
    uart_initwBaudRate(115200);
    printf("\r\n\r\neMiniBoard MB-025(MM32F0133C7P) %s %s\r\n\r\n", __DATE__, __TIME__);

    /* 启动内核 */
    tx_kernel_enter();

    while(1) {

    }

}


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
