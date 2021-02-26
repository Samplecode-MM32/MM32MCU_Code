/******************************************************************************
 * @file    main.c
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
#define __MAIN_C__


/* Includes -----------------------------------------------------------------*/
#include "main.h"


/* Includes -----------------------------------------------------------------*/
#include "systick.h"
#include "uart.h"
#include <os_task.h>
#include <os_errno.h>
#include <os_assert.h>
#include <os_device.h>
#include <os_irq.h>
#include "board.h"

/* Includes -----------------------------------------------------------------*/
#include "bsp_led.h"


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
static void user_task(void *parameter)
{

    while (1)
    {
        BSP_LED1_TOGGLE();
        BSP_LED2_TOGGLE();
        os_task_msleep(400);     
    }
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
static void user_task1(void *parameter)
{

    while (1)
    {
        BSP_LED3_TOGGLE();
        BSP_LED4_TOGGLE();
        os_task_msleep(200);    
    }
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
int main(void)
{
    os_task_t *task;
    os_task_t *task1;
    /* Init SysTick timer 1ms for SysTick_DelayMs */
    SysTick_Init(1000);

    /* Config UART1 with parameter(115200, N, 8, 1) for printf */
    UARTx_Configure(DEBUG_UART, 115200, UART_WordLength_8b, UART_StopBits_1, UART_Parity_No);

    /* Init LEDs GPIO */
    BSP_LED_Init();

    printf("\r\nMM32F032R8T6 %s %s\r\n", __DATE__, __TIME__);

    task = os_task_create("user", user_task, NULL, 512, 3, 5);
    OS_ASSERT(task);
    os_task_startup(task);
    
    task1 = os_task_create("user1", user_task1, NULL, 512, 3, 5);
    OS_ASSERT(task1);
    os_task_startup(task1);

    return 0;
}


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/

