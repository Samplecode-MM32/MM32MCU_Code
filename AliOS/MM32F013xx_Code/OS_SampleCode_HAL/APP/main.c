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


/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/


/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/


#include <k_api.h>
#include <k_task.h>
#include <stdio.h>
#include <stdlib.h>


#define DEMO_TASK_STACKSIZE    256 //256*cpu_stack_t = 1024byte
#define DEMO_TASK_PRIORITY     20


extern void stm32_soc_init(void);
static ktask_t demo_task_obj;


static ktask_t Test_Task_t;
static ktask_t Led_Task_t;
cpu_stack_t demo_task_buf1[DEMO_TASK_STACKSIZE];
cpu_stack_t demo_task_buf2[DEMO_TASK_STACKSIZE];
cpu_stack_t demo_task_buf[DEMO_TASK_STACKSIZE];


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void Led1_Task(void* a)
{

	while(1)
	{
        LED3_TOGGLE();
        LED4_TOGGLE();
		krhino_task_sleep(6*RHINO_CONFIG_TICKS_PER_SECOND);
	}
}	


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void Led_Task(void* a)
{
	while(1)
	{
        LED1_TOGGLE();
        LED2_TOGGLE();
		krhino_task_sleep(3*RHINO_CONFIG_TICKS_PER_SECOND);
	}
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void demo_task(void *arg)
{
    LED_Init();
    DELAY_Init();
    CONSOLE_Init(115200);
    printf("demo_task here!\n");
    printf("rhino memory is %d!\n", krhino_global_space_get());
    
    if(krhino_task_create(&Led_Task_t,"LED_TASK",0,DEMO_TASK_PRIORITY, 
        50, demo_task_buf1, DEMO_TASK_STACKSIZE, Led1_Task, 1)!=0)
		printf("Led task create faild\n");
	if(krhino_task_create(&Test_Task_t,"Test_Task",0,DEMO_TASK_PRIORITY, 
        50, demo_task_buf2, DEMO_TASK_STACKSIZE, Led_Task, 1)!=0)
		printf("Test task create faild\n");
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void SysTick_Handler(void)
{			
  krhino_intrpt_enter();
  krhino_tick_proc();
  krhino_intrpt_exit();	
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
int main(void)
{
    krhino_init();
   
#ifdef CONFIG_AOS_CLI
    extern int aos_cli_init(void);
    aos_cli_init();
#endif

    krhino_task_create(&demo_task_obj, "demo_task", 0,DEMO_TASK_PRIORITY, 
        50, demo_task_buf, DEMO_TASK_STACKSIZE, demo_task, 1);

    krhino_start();

    return 0;
}


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
