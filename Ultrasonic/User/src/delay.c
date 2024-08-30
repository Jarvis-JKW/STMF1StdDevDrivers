/**
  ******************************************************************************
  * @file    /User/src/delay.c 
  * @author  Jarvis-JKW
  * @version V1.0c
  * @date    2022年1月22日
  * @brief   使用SysTick的普通计数模式或CPU对延迟进行管理
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "delay.h"

/* Private functions ---------------------------------------------------------*/
#ifdef DELAY_WITH_SYSTICK
/**
  * @brief  延时函数初始化
  * @detail SysTick的时钟固定为HCLK时钟的1/8
  * @SYSCLK 系统时钟
  */
static uint8_t  fac_us=0;//us延时倍乘数			   
static uint16_t fac_ms=0;//ms延时倍乘数
void Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   //选择外部时钟  HCLK/8
    fac_us = SystemCoreClock / 8000000;                     //为系统时钟的1/8
    fac_ms = (uint16_t)fac_us * 1000;                       //代表每个ms需要的SysTick时钟数
}
#endif	/* DELAY_WITH_SYSTICK */


/**
  * @brief  微秒延时函数
  * @param	需要延时的微秒数
  */
void delay_us(uint32_t us)
{
#if	defined DELAY_WITH_SYSTICK  /* +83us/ms(典型值), <=102us/ms */
    uint32_t temp;

    SysTick->LOAD = us * fac_us;           //时间加载	  		 
    SysTick->VAL = 0x00;                    //清空计数器
    SysTick->CTRL|= SysTick_CTRL_ENABLE_Msk;//开始倒数	
  
    do
    {
        temp = SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));   //等待时间到达

    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭计数器
    SysTick->VAL = 0X00;                    //清空计数器

#else   /* +0.25μs/ms(典型值) */
    uint8_t temp;

    while(us--)
    {
        temp = 6;
        while(temp--);
    }
#endif  /* DELAY_WITH_SYSTICK */
}


/**
  * @brief  毫秒延时函数
  * @param	需要延时的毫秒数
  * @detail 在SysTick定时模式下, SysTick->LOAD为24位寄存器
  *         最大延时为: nms <= 0xffffff*8*1000/SYSCLK[Hz]
  *         SYSCLK=72MHz, nms <= 1864ms
  */
void delay_ms(uint16_t ms)
{
#ifdef DELAY_WITH_SYSTICK  /* +0.93us/s(典型值), >=0.69us/s */
    uint32_t temp;

    SysTick->LOAD = (uint32_t)ms * fac_ms;      //时间加载(SysTick->LOAD为24bit)
    SysTick->VAL  = 0x00;                       //清空计数器
    SysTick->CTRL|= SysTick_CTRL_ENABLE_Msk;    //开始倒数 
    
    do
    {
        temp = SysTick->CTRL;
    }while((temp&0x01) && !(temp&(1<<16)));     //等待时间到达

    SysTick->CTRL&= ~SysTick_CTRL_ENABLE_Msk;   //关闭计数器
    SysTick->VAL = 0X00;                        //清空计数器

#else   /* -27.53us/s(典型值) */
    uint16_t temp;

    while(ms--)
    {
        temp=7998;
        while(temp--);
    }
#endif  /* DELAY_WITH_SYSTICK */	
}


/**
  * @brief  秒延时函数
  * @param	需要延时的秒数
  * @error  -27.02us/s(CPU典型值), +1.16us/s~+1.43us/s(SysTick典型值)
  */
void delay_s(uint8_t s)
{
    while(s--)
        delay_ms(1000);
}

/******************************** END OF FILE *********************************/
