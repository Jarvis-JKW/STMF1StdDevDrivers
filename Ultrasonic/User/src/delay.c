/**
  ******************************************************************************
  * @file    /User/src/delay.c 
  * @author  Jarvis-JKW
  * @version V1.0c
  * @date    2022��1��22��
  * @brief   ʹ��SysTick����ͨ����ģʽ��CPU���ӳٽ��й���
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "delay.h"

/* Private functions ---------------------------------------------------------*/
#ifdef DELAY_WITH_SYSTICK
/**
  * @brief  ��ʱ������ʼ��
  * @detail SysTick��ʱ�ӹ̶�ΪHCLKʱ�ӵ�1/8
  * @SYSCLK ϵͳʱ��
  */
static uint8_t  fac_us=0;//us��ʱ������			   
static uint16_t fac_ms=0;//ms��ʱ������
void Delay_Init(void)
{
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);   //ѡ���ⲿʱ��  HCLK/8
    fac_us = SystemCoreClock / 8000000;                     //Ϊϵͳʱ�ӵ�1/8
    fac_ms = (uint16_t)fac_us * 1000;                       //����ÿ��ms��Ҫ��SysTickʱ����
}
#endif	/* DELAY_WITH_SYSTICK */


/**
  * @brief  ΢����ʱ����
  * @param	��Ҫ��ʱ��΢����
  */
void delay_us(uint32_t us)
{
#if	defined DELAY_WITH_SYSTICK  /* +83us/ms(����ֵ), <=102us/ms */
    uint32_t temp;

    SysTick->LOAD = us * fac_us;           //ʱ�����	  		 
    SysTick->VAL = 0x00;                    //��ռ�����
    SysTick->CTRL|= SysTick_CTRL_ENABLE_Msk;//��ʼ����	
  
    do
    {
        temp = SysTick->CTRL;
    }while((temp&0x01)&&!(temp&(1<<16)));   //�ȴ�ʱ�䵽��

    SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//�رռ�����
    SysTick->VAL = 0X00;                    //��ռ�����

#else   /* +0.25��s/ms(����ֵ) */
    uint8_t temp;

    while(us--)
    {
        temp = 6;
        while(temp--);
    }
#endif  /* DELAY_WITH_SYSTICK */
}


/**
  * @brief  ������ʱ����
  * @param	��Ҫ��ʱ�ĺ�����
  * @detail ��SysTick��ʱģʽ��, SysTick->LOADΪ24λ�Ĵ���
  *         �����ʱΪ: nms <= 0xffffff*8*1000/SYSCLK[Hz]
  *         SYSCLK=72MHz, nms <= 1864ms
  */
void delay_ms(uint16_t ms)
{
#ifdef DELAY_WITH_SYSTICK  /* +0.93us/s(����ֵ), >=0.69us/s */
    uint32_t temp;

    SysTick->LOAD = (uint32_t)ms * fac_ms;      //ʱ�����(SysTick->LOADΪ24bit)
    SysTick->VAL  = 0x00;                       //��ռ�����
    SysTick->CTRL|= SysTick_CTRL_ENABLE_Msk;    //��ʼ���� 
    
    do
    {
        temp = SysTick->CTRL;
    }while((temp&0x01) && !(temp&(1<<16)));     //�ȴ�ʱ�䵽��

    SysTick->CTRL&= ~SysTick_CTRL_ENABLE_Msk;   //�رռ�����
    SysTick->VAL = 0X00;                        //��ռ�����

#else   /* -27.53us/s(����ֵ) */
    uint16_t temp;

    while(ms--)
    {
        temp=7998;
        while(temp--);
    }
#endif  /* DELAY_WITH_SYSTICK */	
}


/**
  * @brief  ����ʱ����
  * @param	��Ҫ��ʱ������
  * @error  -27.02us/s(CPU����ֵ), +1.16us/s~+1.43us/s(SysTick����ֵ)
  */
void delay_s(uint8_t s)
{
    while(s--)
        delay_ms(1000);
}

/******************************** END OF FILE *********************************/
