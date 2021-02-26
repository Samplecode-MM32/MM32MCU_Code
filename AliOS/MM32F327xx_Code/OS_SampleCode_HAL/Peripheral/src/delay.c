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
/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/
/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/


#if SYSTEM_SUPPORT_OS
#include "includes.h"
#endif


static u8  fac_us = 0;							//us延时倍乘数
static u16 fac_ms = 0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void delay_init()
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
    fac_us = SystemCoreClock / 8000000;				//为系统时钟的1/8
    fac_ms = (u16)fac_us * 1000;					//非OS下,代表每个ms需要的systick时钟数
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void delay_us(u32 nus)
{
    u32 temp;
    SysTick->LOAD = nus * fac_us; 					//时间加载
    SysTick->VAL = 0x00;        					//清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//开始倒数
    do
    {
        temp = SysTick->CTRL;
    }
    while((temp & 0x01) && !(temp & (1 << 16)));		//等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
    SysTick->VAL = 0X00;      					 //清空计数器
}
/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void delay_ms(u16 nms)
{
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;				//时间加载(SysTick->LOAD为24bit)
    SysTick->VAL = 0x00;							//清空计数器
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//开始倒数
    do
    {
        temp = SysTick->CTRL;
    }
    while((temp & 0x01) && !(temp & (1 << 16)));		//等待时间到达
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
    SysTick->VAL = 0X00;       					//清空计数器
}

/*-------------------------(C) COPYRIGHT 2019 MindMotion ----------------------*/
