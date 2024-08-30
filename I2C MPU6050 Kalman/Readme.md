# STM32F103 MPU6050������ (Kalman�˲�) 

## Ŀ¼˵��
* MPU6050
   * Hardware����BSP����
      * inc
         * mpu6050.h
         * inv_mpu.h
         * inv_mpu_dmp_motion_driver.h
         * dmpKey.h
         * dmpmap.h
         * oledfont.h
         * oled.h
         * led.h
      * src
         * mpu6050.c
         * inv_mpu.c
         * inv_mpu_dmp_motion_driver.c
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
         * iic.c����IIC����ģ��ͨѶ����
         * usart.c��������ͨ���������ü��жϷ������
         * stm32f1xx_it.c�����쳣����������
      * Listings
      * MPU.uvprojx����MDK�����ļ�

   * Readme.md����ģ��˵��

## ʹ��˵��
* ���ݸ���Ƶ�ʲ���
   * OLED��Ļ��ˢ��ʱռ�ý϶���Դ������ȥ��OLED��Ļ

* ���ݲ�׼ȷ/û��Ӧ
   * ��ʼ����Ҫ�ϳ�ʱ��
   * ������Ƶ�ʹ���ʱ����������ݸ����ӳ١����ݲ�׼ȷ�����������߲���Ƶ��
   * ƫ��������Ӳ�����ԭ��������Ư�ƣ�����ʹ�ø����ǻ�����
   * �����������㷽ʽ�����˲�

* GPIO����(OLED�������ǹ�����ͬһI2C2������)
   * MPU - OLED - SCL - GPIOB.10
   * MPU - OLED - SDA - GPIOB.11

