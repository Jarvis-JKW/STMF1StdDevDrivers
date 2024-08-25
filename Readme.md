# STM32F10x MDK模板说明

## 目录说明
* FLASH
   * Hardware——BSP驱动
      * inc/*.h
      * src/*.c
   * Library
	  * CMSIS——提供了内核与外设、实时操作系统和中间设备之间的通用接口。
         * startup
         * core_cm3.c
         * core_cm3.h
         * stm32f10x.h
         * system_stm32f10x.c
         * system_stm32f10x.h
	  * StdPeriph_Driver——STM32F10x标准固件库v3.6.0
         * inc/*.h
         * src/*.c
   * Objects——编译所产生的文件
      * ….crf
      * ….d
      * ….o
      * stm32f10x.axf——MDK编译时自动生成的包含调试信息的文件
	  * stm32f10x.htm——依据axf文件生成的静态调用图
      * stm32f10x.hex——编译生成的记录有FLASH地址的十六进制符号文件
	  * stm32f10x.bin——依据axf文件生成的代码映像
      * stm32f10x.build_log.htm——编译日志
   * User——存放项目公共文件
      * inc
         * sys.h——项目公共宏定义
         * init.h
         * ……
      * src
         * main.c——主函数
         * init.c——包含所需要外设的初始化函数
         * adc.c ——模拟输入
         * dac.c ——模拟输出
         * delay.c——延时函数，包含使用SysTick和非SysTick两种方式
         * exti.c——外部中断配置及中断服务程序
         * iic.c——I2C总线配置，包含使用软件模拟和硬件驱动两种方式
         * rtc.c——RTC时钟配置及中断服务程序
         * spi.c——SPI总线配置
         * sys.c——重定向printf
         * timer.c——定时器配置及中断服务程序
         * usart.c——串口通信总线配置及中断服务程序
         * wdg.c——看门狗配置
         * stm32f1xx_it.c——异常处理服务程序
      * Listings
      * Template.uvprojx——MDK工程文件

   * Readme.md——模板说明

## 使用说明
* 硬件说明
   |   Types   |STM32F103ZET6|STM32F103RCT6|STM32F103RBT6|STM32F103R8T6|
   |:---------:|:-----------:|:-----------:|:-----------:|:-----------:|
   |    Core   |ARM Cortex-M3|ARM Cortex-M3|ARM Cortex-M3|ARM Cortex-M3|
   | Frequency |    72 MHz   |    72 MHz   |    72 MHz   |    72 MHz   |
   |   Flash   |  512 Kbytes |  256 Kbytes |  128 Kbytes |   64 Kbytes |
   |    RAM    |   64 Kbytes |   48 Kbytes |   20 Kbytes |   20 Kbytes |
   |   TIMER   |      8      |      8      |      4      |      4      |
   |  U(S)ART  |    3 + 2    |    3 + 2    |      3      |      3      |
   |    SPI    |      3      |      3      |      2      |      2      |
   |    I2C    |      2      |      2      |      2      |      2      |
   |    ADC    |  3 (12bit)  |  3 (12bit)  |  2 (12bit)  |  2 (12bit)  |
   |    DAC    |  2 (12bit)  |  2 (12bit)  |      0      |      0      |
   |    CAN    |      1      |      1      |      1      |      1      |
   |   SDIO    |      1      |      1      |      0      |      0      |

* 目前工程中已通过测试的驱动有：
   * LED
   * 8段共阳极数码管
   * 8×8 共阳极点阵LED (改进消隐功能待测试)
   * 机械按键
   * 电容按键
   * DHT11直插式温湿度传感器
   * HC-SR04超声波测距（非外部中断）
   * HC-SR051人体红外感应传感器
   * HS-0038红外信号接收模块（NEC解码）
   * 1602 液晶显示屏（4线驱动）
   * LM35直插式温度传感器
   * 光敏二极管感光
   * SG90舵机控制
   * 28BYJ-48步进电机（单四拍、双四拍、单八拍）
   * 24C02 EEPROM使用IIC协议读写（硬件驱动/软件模拟）
   * IIC/I2C协议与EEPROM 24C02进行通信
   * AlienTek TFT-LCD 4.3寸电容屏显示与触摸（NT35510 & GT917S）
   * MPU6050陀螺仪（含DMP解算）

* 以下模块/传感器暂未调通：
   * 3144霍尔传感器
   * 4位8段式共阴/共阳数码管
   * DC电机PID调速
   * 红外寻迹模块

* GPIO占用情况
   |   GPIO   |   占用外设   |   外设类型   |   GPIO    |   占用外设   |   外设类型   |
   |:--------:|:------------:|:------------:|:---------:|:------------:|:------------:|
   |   PA 0   |  KEY_UP按键  |     板载     |    PB 9   |  无源蜂鸣器  |     外接     |
   |   PA 1   | TPAD电容按键 |板载(TPAD-ADC)|PB10 ~ PB11|   MPU6050    |     外接     |
   |   PA 9   |   CH340 TX   |     板载     |    PE 0   | HC SR051红外 |     外接     |
   |   PA10   |   CH340 RX   |     板载     | PE1 ~ PE2 | HC SR04 超声 |     外接     |
   |   PB 5   |    LED 0     |     板载     | PE0 ~ PE7 |  8×8点阵LED  |     外接     |
   |PB6 ~ PB7 | EEPROM 24C02 |     板载     | PE0 ~ PE7 |  LM298N IN   |     外接     |
   |   PB 8   |  有源蜂鸣器  |     板载     | 	 PE 9   | LM298N EN/PA |     外接     |
   |   PB 9   |HS0038红外接收|     板载     | 	 PE11   | LM298N EN/PA |     外接     |
   |   PB12   |FLASH NM25Q128|     板载     | 	 PE13   | LM298N EN/PA |     外接     |
   |   PE 3   |     KEY 1    |     板载     | 	 PE14   | LM298N EN/PA |     外接     |
   |   PE 4   |     KEY 0    |     板载     | PF0 ~ PF7 |   8段数码管  |     外接     |
   |   PE 5   |     LED 1    |     板载     | PF0 ~ PF2 |   LCD1602A   |     外接     |
   |   PF 8   |  光敏传感器  |     板载     | PF4 ~ PF7 |   LCD1602A   |     外接     |
   |   FSMC   |    TFT-LCD   |     外接     |    PF 6   |LM35温度传感器|     外接     |
   |PA2 ~ PA4 |模拟灰度传感器|     外接     | PF8 ~ PF15|  8×8点阵LED  |     外接     |
   |   PA 6   |   SG90舵机   |     外接     |    PG11   | DHT11温湿度计|     外接     |
* TIM占用情况
   |   TIMx   |   占用外设   |   外设类型   |   功能   |   中断   |
   |:--------:|:------------:|:------------:|:--------:|:--------:|
   |   TIM1   |    LM298N    |     外接     |   PWM    |    无    |
   |   TIM2   |   MPU 6050   |     外接     |   定时   | 溢出中断 |
   |   TIM3   |   SG90舵机   |     外接     |   PWM    |    无    |
   |   TIM4   |HS0038红外接收|     板载     |   捕获   | 捕获中断 |
   |   TIM5   | TPAD电容按键 |     板载     |   捕获   |    无    |
   |   TIM6   |     DAC1     | MCU 内部资源 |   定时   |    无    |
   |   TIM7   | HC SR04 超声 |     外接     |   定时   |    无    |
* 使用方法
   1. 使用Keil5打开project；
   2. 使用"Configure target options"配置Devices，如"STM32F103ZE"；
   3. 配置晶振频率，如8MHz；
   4. ARM Complier 选择 "Use default complier version 5"；
   5. 根据需要选择合适的模板，并修改或编写响应的中断服务程序，并将非必要的中断服务程序移除；
   6. 将非必要的驱动文件移除，并在 main.c 中注释相应的头文件包含；
   7. 将非必要的标准库文件移出工程，并在 stm32f10x_conf.h 中注释响应的头文件包含；
   8. 开始编译。

   
