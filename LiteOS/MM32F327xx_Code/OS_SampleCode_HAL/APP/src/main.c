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
#include "los_sys.h"
#include "los_task.ph"
#include "los_memory.ph"


UINT32 RX_Task_Handle;
UINT32 TX_Task_Handle;


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
void DELAY_Init(void)
{
    //sDelayNopNumber = 100;
    if (SysTick_Config(SystemCoreClock / 1000)) {
        while (1);
    }
    NVIC_SetPriority(SysTick_IRQn, 0x0);
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
static void Led1Task(void)
{
    while(1) {
        LED1_TOGGLE();
        LED2_TOGGLE();
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
    while(1) {
        LED3_TOGGLE();
        LED4_TOGGLE();
        LOS_TaskDelay(500);
    }
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/


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
	task_init_param.uwStackSize = 512;	
	uwRet = LOS_TaskCreate(&RX_Task_Handle, &task_init_param);
    if (uwRet != LOS_OK)
    {
        printf("Led1Task create failed,%X\n",uwRet);
        return uwRet;
    }
    
    task_init_param.usTaskPrio = 4;	
	task_init_param.pcName = "TxTask";
	task_init_param.pfnTaskEntry = (TSK_ENTRY_FUNC)Led2Task;
	task_init_param.uwStackSize = 512;
	uwRet = LOS_TaskCreate(&TX_Task_Handle, &task_init_param);
    if (uwRet != LOS_OK)
    {
        printf("Led2Task create failed,%X\n",uwRet);
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
int main(void)
{

    UINT32 uwRet = LOS_OK;

    DELAY_Init();

    uart_initwBaudRate(115200);

    LED_Init();//LEDµ∆…¡À∏≤‚ ‘GPIO
    
    LOS_KernelInit();

    uwRet = AppTaskCreate();

    if(uwRet != LOS_OK) {
          printf("LOS Creat task failed\r\n");
          //return LOS_NOK;
    }
      LOS_Start();

}

/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/

