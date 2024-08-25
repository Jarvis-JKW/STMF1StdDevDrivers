# STM32F103 7段数码管（带dp）

## 目录说明
* FLASH
   * Hardware——BSP驱动
      * inc/digitaltube.h
      * src/digitaltube.c
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
         * main.h——项目公共宏定义
         * binary.h——拓展二进制数字
         * stm32f10x_conf.h——标准库外设配置
         * ……
      * src
         * main.c——主函数及初始化函数
         * delay.c——延时函数，包含使用SysTick和非SysTick两种方式
         * debug.c——重定向printf
         * gpio.c——GPIO配置
         * usart.c——串口通信总线配置及中断服务程序
         * stm32f1xx_it.c——异常处理服务程序
      * Listings
      * DigitalTube.uvprojx——MDK工程文件

   * Readme.md——模板说明

## 使用说明
* 连接说明
   * 单个数码管仅需连接并初始化GPIOF.0-GPIOF.7
   * 共阴极数码管显示时将字模取反即可
   * 因PCB设计原因，74HC573.LE接VCC，建议改接GPIO，并在不刷新时拉低以实现锁存，节省性能

* GPIO连接
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
