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
#define _MAIN_C_


/* Private includes ----------------------------------------------------------*/
#include "led.h"
#include "delay.h"
#include "uart.h"
#include "los_sys.h"
#include "los_task.ph"
#include "los_memory.ph"


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
static void Led1Task(void)
{
    while(1)
    {
        LED3_TOGGLE();
        LED4_TOGGLE();
        LOS_TaskDelay(1000);
    }
}


/******************************************************************************
 * @brief
 * @param
 * @retval
 * @attention
******************************************************************************/
static void Led2Task(void)
{
    while(1)
    {
        LED1_TOGGLE();
        LED2_TOGGLE();
        LOS_TaskDelay(500);
    }
}
UINT32 RX_Task_Handle;
UINT32 TX_Task_Handle;


/******************************************************************************
 * @brief
 * @param
 * @retval
 * @attention
******************************************************************************/
static UINT32 AppTaskCreate(void)
{
    UINT32 uwRet = LOS_OK;

    TSK_INIT_PARAM_S task_init_param;

    task_init_param.usTaskPrio = 4;
    task_init_param.pcName = "RxTask";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Led1Task;
    task_init_param.uwStackSize = 0x100;
    uwRet = LOS_TaskCreate(&RX_Task_Handle, &task_init_param);
    if(uwRet != LOS_OK)
    {
        printf("Led1Task create failed,%X\n", uwRet);
        return uwRet;
    }

    task_init_param.usTaskPrio = 4;
    task_init_param.pcName = "TxTask";
    task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Led2Task;
    task_init_param.uwStackSize = 0x100;
    uwRet = LOS_TaskCreate(&TX_Task_Handle, &task_init_param);
    if(uwRet != LOS_OK)
    {
        printf("Led2Task create failed,%X\n", uwRet);
        return uwRet;
    }
    return LOS_OK;
}


/******************************************************************************
 * @brief
 * @param
 * @retval
 * @attention
******************************************************************************/
void HardFault_Handler(void)
{
    /* USER CODE BEGIN HardFault_IRQn 0 */

    /* USER CODE END HardFault_IRQn 0 */
    while(1)
    {
        /* USER CODE BEGIN W1_HardFault_IRQn 0 */
        /* USER CODE END W1_HardFault_IRQn 0 */
    }
    /* USER CODE BEGIN HardFault_IRQn 1 */

    /* USER CODE END HardFault_IRQn 1 */
}


/******************************************************************************
 * @brief
 * @param
 * @retval
 * @attention
******************************************************************************/
s32 main(void)
{
    /* USER CODE BEGIN 1 */
    UINT32 uwRet = LOS_OK;
    DELAY_Init();
    LED_Init();
    CONSOLE_Init(115200);
    if(LOS_OK != LOS_KernelInit())
    {
        return LOS_NOK;
    }
    uwRet = AppTaskCreate();
    if(uwRet != LOS_OK)
    {
        printf("LOS Creat task failed\r\n");
    }
    LOS_Start();
}


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/

