# STM32F103 SPI协议IPS屏幕 (0.96inch)

## 目录说明
* ST7735S
   * Hardware——BSP驱动
      * inc
         * font.h
         * lcd.h
         * led.h
      * src
         * lcd.c
         * led.c
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
         * nvic.c——中断分组及优先级配置
         * gpio.c——GPIO配置
         * spi.c——SPI总线初始化与通讯函数
         * usart.c——串口通信总线配置及中断服务程序
         * stm32f1xx_it.c——异常处理服务程序
      * Listings
      * LCD.uvprojx——MDK工程文件

   * Readme.md——模板说明

## 使用说明
* ASCII字符
   * ASCII字符均已在font.h中，可通过打印字符串的方式直接调用
   * 使用sprintf函数可将数字等变量转为字符串

* 中文汉字
   * 取模软件: PCtoLCD2002
   * 点阵格式: 阴码
   * 取模方式: 逐行式
   * 取模走向: 逆向(低位在前)
   * C51格式(无行前缀, 行后缀为英文半角",")

* 图片
   * 取模软件: Image2Lcd
   * 输出数据类型: C语言数组/二进制
   * 输出灰度: 16位真彩色
   * 最大宽度和高度: 160 80
   * 扫描方式: 自左向右, 自顶向下
   * 数据格式: 高位在前(MSB First)

* GPIO连接
   * SCL - PA5
   * SDA - PA7
   * RES - PA3
   * DC  - PA2
   * CS  - PA4
   * BLK - PA1

