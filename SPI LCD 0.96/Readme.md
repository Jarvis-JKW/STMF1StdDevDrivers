# STM32F103 SPIЭ��IPS��Ļ (0.96inch)

## Ŀ¼˵��
* ST7735S
   * Hardware����BSP����
      * inc
         * font.h
         * lcd.h
         * led.h
      * src
         * lcd.c
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
         * spi.c����SPI���߳�ʼ����ͨѶ����
         * usart.c��������ͨ���������ü��жϷ������
         * stm32f1xx_it.c�����쳣����������
      * Listings
      * LCD.uvprojx����MDK�����ļ�

   * Readme.md����ģ��˵��

## ʹ��˵��
* ASCII�ַ�
   * ASCII�ַ�������font.h�У���ͨ����ӡ�ַ����ķ�ʽֱ�ӵ���
   * ʹ��sprintf�����ɽ����ֵȱ���תΪ�ַ���

* ���ĺ���
   * ȡģ���: PCtoLCD2002
   * �����ʽ: ����
   * ȡģ��ʽ: ����ʽ
   * ȡģ����: ����(��λ��ǰ)
   * C51��ʽ(����ǰ׺, �к�׺ΪӢ�İ��",")

* ͼƬ
   * ȡģ���: Image2Lcd
   * �����������: C��������/������
   * ����Ҷ�: 16λ���ɫ
   * ����Ⱥ͸߶�: 160 80
   * ɨ�跽ʽ: ��������, �Զ�����
   * ���ݸ�ʽ: ��λ��ǰ(MSB First)

* GPIO����
   * SCL - PA5
   * SDA - PA7
   * RES - PA3
   * DC  - PA2
   * CS  - PA4
   * BLK - PA1

