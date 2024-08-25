# STM32F103 DHT11温湿度传感器

## 目录说明
* FLASH
   * Hardware——BSP驱动
      * inc
         * dht11.h
         * led.h
      * src
         * dht11.c
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
         * gpio.c——GPIO配置
         * usart.c——串口通信总线配置及中断服务程序
         * stm32f1xx_it.c——异常处理服务程序
      * Listings
      * DHT11.uvprojx——MDK工程文件

   * Readme.md——模板说明

## 使用说明
* 时序说明
   * 开始信号: 主机拉低至少18ms - 主机拉高20-40us
   * DHT11回声: 低电平80us - 高电平80us
   * 数据信号: 低电平50us - 数据位(1:高电平70us|0:高电平26-28us)

* 数据说明(高位->低位, 高位先出)
   * 湿度整数部分
   * 湿度小数部分
   * 温度整数部分
   * 温度小数部分
   * 校验和

* GPIO连接
   * Data - GPIOG.11
   * 3V3 - 510R - LED0 - GPIOB.5

