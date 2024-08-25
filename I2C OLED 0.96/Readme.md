# STM32F103 IICЭ��OLED��Ļ (0.96inch)

## Ŀ¼˵��
* SSD1306
   * Hardware����BSP����
      * inc
         * oledfont.h
         * oled.h
         * led.h
      * src
         * oled.c
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
         * nvic.c�����жϷ��鼰���ȼ�����
         * gpio.c����GPIO����
         * iic.c����IIC���߳�ʼ����ͨѶ����
         * usart.c��������ͨ���������ü��жϷ������
         * stm32f1xx_it.c�����쳣����������
      * Listings
      * OLED.uvprojx����MDK�����ļ�

   * Readme.md����ģ��˵��

## ʹ��˵��
* ASCII�ַ�
   * ASCII�ַ�������oledfont.h�У���ͨ����ӡ�ַ����ķ�ʽֱ�ӵ���
   * ʹ��sprintf�����ɽ����ֵȱ���תΪ�ַ���

* ���ĺ���
   * ȡģ���: PCtoLCD2002
   * ģʽ: �ַ�ģʽ
   * �����ʽ: ����
   * ȡģ��ʽ: ����ʽ
   * ȡģ����: ����(��λ��ǰ)
   * ÿ����ʾ����: 999
   * C51��ʽ

* GPIO����
   * SCL - GPIOB.6
   * SDA - GPIOB.7

