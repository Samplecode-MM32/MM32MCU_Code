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
#include "sys.h"
#include "delay.h"
#include "uart.h"
#include "led.h"

#include <os_task.h>
#include <os_errno.h>
#include <os_assert.h>
#include <os_device.h>
#include <os_irq.h>
#include "board.h"


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
        LED1_TOGGLE();
        LED2_TOGGLE();
        os_task_msleep(400);
        //os_task_msleep(200);      
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
        LED3_TOGGLE();
        LED4_TOGGLE();
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

    delay_init();	    	 
    LED_Init();
    
    os_task_t *task;
    os_task_t *task1;

    task = os_task_create("user", user_task, NULL, 512, 3, 5);
    OS_ASSERT(task);
    os_task_startup(task);
    
    task1 = os_task_create("user1", user_task1, NULL, 512, 3, 5);
    OS_ASSERT(task1);
    os_task_startup(task1);

    return 0;
}

/******************* (C) COPYRIGHT 2021  ************************END OF FILE***/
