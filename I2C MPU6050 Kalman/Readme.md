# STM32F103 MPU6050陀螺仪 (Kalman滤波) 

## 目录说明
* MPU6050
   * Hardware——BSP驱动
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
         * iic.c——IIC总线模拟通讯函数
         * usart.c——串口通信总线配置及中断服务程序
         * stm32f1xx_it.c——异常处理服务程序
      * Listings
      * MPU.uvprojx——MDK工程文件

   * Readme.md——模板说明

## 使用说明
* 数据更新频率不足
   * OLED屏幕在刷屏时占用较多资源，尝试去掉OLED屏幕

* 数据不准确/没反应
   * 初始化需要较长时间
   * 当采样频率过低时，会出现数据更新延迟、数据不准确的情况，请提高采样频率
   * 偏航角由于硬件设计原因存在零点漂移，尝试使用俯仰角或横滚角
   * 采用其它解算方式进行滤波

* GPIO连接(OLED与陀螺仪挂载在同一I2C2总线上)
   * MPU - OLED - SCL - GPIOB.10
   * MPU - OLED - SDA - GPIOB.11

