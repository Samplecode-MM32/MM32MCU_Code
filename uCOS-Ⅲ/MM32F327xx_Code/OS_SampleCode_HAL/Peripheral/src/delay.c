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
#include "includes.h"					//ucos 使用	  


/* Private typedef ----------------------------------------------------------*/
/* Private define -----------------------------------------------------------*/
/* Private macro ------------------------------------------------------------*/
/* Private variables --------------------------------------------------------*/
static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数
extern u32 SystemCoreClock; 	



/* Private function prototypes ----------------------------------------------*/
/* Private functions --------------------------------------------------------*/
/* Exported variables -------------------------------------------------------*/
/* Exported function prototypes ---------------------------------------------*/


//当delay_us/delay_ms需要支持OS的时候需要三个与OS相关的宏定义和函数来支持
//首先是3个宏定义:
//    delay_osrunning:用于表示OS当前是否正在运行,以决定是否可以使用相关函数
//delay_ostickspersec:用于表示OS设定的时钟节拍,delay_init将根据这个参数来初始哈systick
// delay_osintnesting:用于表示OS中断嵌套级别,因为中断里面不可以调度,delay_ms使用该参数来决定如何运行
//然后是3个函数:
//  delay_osschedlock:用于锁定OS任务调度,禁止调度
//delay_osschedunlock:用于解锁OS任务调度,重新开启调度
//    delay_ostimedly:用于OS延时,可以引起任务调度.


#define delay_osrunning		OSRunning			//OS是否运行标记,0,不运行;1,在运行
#define delay_ostickspersec	OSCfg_TickRate_Hz	//OS时钟节拍,即每秒调度次数
#define delay_osintnesting 	OSIntNestingCtr		//中断嵌套级别,即中断嵌套次数




/******************************************************************************
 * @brief    us级延时时,关闭任务调度(防止打断us级延迟)   
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void delay_osschedlock(void)
{
	OS_ERR err; 
	OSSchedLock(&err);							//UCOSIII的方式,禁止调度，防止打断us延时
}


/******************************************************************************
 * @brief    us级延时时,恢复任务调度   
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void delay_osschedunlock(void)
{	
	OS_ERR err; 
	OSSchedUnlock(&err);						//UCOSIII的方式,恢复调度
}


/******************************************************************************
 * @brief    调用OS自带的延时函数延时
 *           ticks:延时的节拍数
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void delay_ostimedly(u32 ticks)
{
	OS_ERR err; 
	OSTimeDly(ticks,OS_OPT_TIME_PERIODIC,&err);	//UCOSIII延时采用周期模式

}
 

/******************************************************************************
 * @brief    systick中断服务函数,使用ucos时用到   
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void SysTick_Handler(void)
{	
	if(delay_osrunning==1)						//OS开始跑了,才执行正常的调度处理
	{
		OSIntEnter();							//进入中断
		OSTimeTick();       					//调用ucos的时钟服务程序               
		OSIntExit();       	 					//触发任务切换软中断
	}
}

			   
/******************************************************************************
 * @brief     初始化延迟函数
 *            当使用OS的时候,此函数会初始化OS的时钟节拍
 *            SYSTICK的时钟固定为HCLK时钟的1/8
 *            SYSCLK:系统时钟
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void delay_init()
{
	u32 reload;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;				//为系统时钟的1/8  
	reload=SystemCoreClock/8000000;				//每秒钟的计数次数 单位为K	   
	reload*=1000000/delay_ostickspersec;		//根据delay_ostickspersec设定溢出时间
												//reload为24位寄存器,最大值:16777216,在72M下,约合1.86s左右	
	fac_ms=1000/delay_ostickspersec;			//代表OS可以延时的最少单位	   

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//开启SYSTICK中断
	SysTick->LOAD=reload; 						//每1/delay_ostickspersec秒中断一次	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//开启SYSTICK    
}								    



/******************************************************************************
 * @brief       //延时nus
 *              //nus为要延时的us数.
 * @param       
 * @retval      
 * @attention   
******************************************************************************/		    								   
void delay_us(u32 nus)
{		
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;					//LOAD的值	    	 
	ticks=nus*fac_us; 							//需要的节拍数	  		 
	tcnt=0;
	delay_osschedlock();						//阻止OS调度，防止打断us延时
	told=SysTick->VAL;        					//刚进入时的计数器值
	while(1)
	{
		tnow=SysTick->VAL;	
		if(tnow!=told)
		{	    
			if(tnow<told)tcnt+=told-tnow;		//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;				//时间超过/等于要延迟的时间,则退出.
		}  
	}
	delay_osschedunlock();						//恢复OS调度									    
}


/******************************************************************************
 * @brief       
 * @param       
 * @retval      
 * @attention   
******************************************************************************/
void delay_ms(u16 nms)
{	
	if(delay_osrunning&&delay_osintnesting==0)	//如果OS已经在跑了,并且不是在中断里面(中断里面不能任务调度)	    
	{		 
		if(nms>=fac_ms)							//延时的时间大于OS的最少时间周期 
		{ 
   			delay_ostimedly(nms/fac_ms);		//OS延时
		}
		nms%=fac_ms;							//OS已经无法提供这么小的延时了,采用普通方式延时    
	}
	delay_us((u32)(nms*1000));					//普通方式延时  
}


/******************* (C) COPYRIGHT 2021 ************************END OF FILE***/
