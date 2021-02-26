/******************************************************************************
 * @file    delay.c
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
#define _DELAY_C_


/* Includes -----------------------------------------------------------------*/
#include "delay.h"


/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
#define USE_SYSTICK_DELAY 1


/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/
/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/


#if USE_SYSTICK_DELAY
extern u32 SystemCoreClock;
static __IO u32 sTimingDelay;


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void DELAY_Init(void)
{
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
void TimingDelayDecrement(void)
{
    if (sTimingDelay != 0x00) {
        sTimingDelay--;
    }
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void DELAY_Ms(__IO u32 count)
{
    sTimingDelay = count;

    while(sTimingDelay != 0);
}


#else
static __IO u32 sDelayNopNumber;


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void DELAY_Init(void)
{
    //Custom
    sDelayNopNumber = 100;
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void DELAY_Us(__IO u32 count)
{
    u32 i = 0;
    while(count--) {
        i = sDelayNopNumber;
        while(i--);
    }
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void DELAY_Ms(__IO u32 count)
{
    u32 i = 0;
    while(count--) {
        i = sDelayNopNumber * 1000;
        while(i--);
    }
}
#endif


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
