# STM32F103 7������ܣ���dp��

## Ŀ¼˵��
* FLASH
   * Hardware����BSP����
      * inc/digitaltube.h
      * src/digitaltube.c
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
      * DigitalTube.uvprojx����MDK�����ļ�

   * Readme.md����ģ��˵��

## ʹ��˵��
* ����˵��
   * ��������ܽ������Ӳ���ʼ��GPIOF.0-GPIOF.7
   * �������������ʾʱ����ģȡ������
   * ��PCB���ԭ��74HC573.LE��VCC������Ľ�GPIO�����ڲ�ˢ��ʱ������ʵ�����棬��ʡ����

* GPIO����
   * GPIOF.7 - g
   * GPIOF.6 - f
   * GPIOF.5 - a
   * GPIOF.4 - b
   * GPIOF.0 - e
   * GPIOF.1 - d
   * GPIOF.2 - c
   * GPIOF.3 - dp
   * 74HC573.OE - GND
   * 74HC573.LE - VCC
   * GPIOF.8 - 74HC573.D1 - 74HC573.Q1 - CS1
   * GPIOF.9 - 74HC573.D2 - 74HC573.Q2 - CS2
   * GPIOF.10 - 74HC573.D3 - 74HC573.Q3 - CS3
   * GPIOF.11 - 74HC573.D4 - 74HC573.Q4 - CS4
   * GPIOF.12 - 74HC573.D5 - 74HC573.Q5 - CS5
   * GPIOF.13 - 74HC573.D6 - 74HC573.Q6 - CS6
   * GPIOF.14 - 74HC573.D7 - 74HC573.Q7 - CS7
   * GPIOF.15 - 74HC573.D8 - 74HC573.Q8 - CS8
