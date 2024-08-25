# STM32F103 DHT11��ʪ�ȴ�����

## Ŀ¼˵��
* FLASH
   * Hardware����BSP����
      * inc
         * dht11.h
         * led.h
      * src
         * dht11.c
         * led.c
   * Library
	  * CMSIS�����ṩ���ں������衢ʵʱ����ϵͳ���м��豸֮���ͨ�ýӿڡ�
         * startup
         * core_cm3.c
         * core_cm3.h
         * stm32f10x.h
         * system_stm32f10x.c
         * system_stm32f10x.h
	  * StdPeriph_Driver����STM32F10x��׼�̼���v3.6.0
         * inc/*.h
         * src/*.c
   * Objects�����������������ļ�
      * ��.crf
      * ��.d
      * ��.o
      * stm32f10x.axf����MDK����ʱ�Զ����ɵİ���������Ϣ���ļ�
      * stm32f10x.htm��������axf�ļ����ɵľ�̬����ͼ
      * stm32f10x.hex�����������ɵļ�¼��FLASH��ַ��ʮ�����Ʒ����ļ�
      * stm32f10x.bin��������axf�ļ����ɵĴ���ӳ��
      * stm32f10x.build_log.htm����������־
   * User���������Ŀ�����ļ�
      * inc
         * main.h������Ŀ�����궨��
         * binary.h������չ����������
         * stm32f10x_conf.h������׼����������
         * ����
      * src
         * main.c��������������ʼ������
         * delay.c������ʱ����������ʹ��SysTick�ͷ�SysTick���ַ�ʽ
         * debug.c�����ض���printf
         * gpio.c����GPIO����
         * usart.c��������ͨ���������ü��жϷ������
         * stm32f1xx_it.c�����쳣����������
      * Listings
      * DHT11.uvprojx����MDK�����ļ�

   * Readme.md����ģ��˵��

## ʹ��˵��
* ʱ��˵��
   * ��ʼ�ź�: ������������18ms - ��������20-40us
   * DHT11����: �͵�ƽ80us - �ߵ�ƽ80us
   * �����ź�: �͵�ƽ50us - ����λ(1:�ߵ�ƽ70us|0:�ߵ�ƽ26-28us)

* ����˵��(��λ->��λ, ��λ�ȳ�)
   * ʪ����������
   * ʪ��С������
   * �¶���������
   * �¶�С������
   * У���

* GPIO����
   * Data - GPIOG.11
   * 3V3 - 510R - LED0 - GPIOB.5

