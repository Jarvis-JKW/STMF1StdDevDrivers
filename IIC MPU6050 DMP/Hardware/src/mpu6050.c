/**
  ******************************************************************************
  * @file    /User/src/mpu6050.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    11-Aug-2022
  * @brief   MPU6050 driver via IIC simulation.
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mpu6050.h"
#include <math.h>
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"


#define q30             1073741824.0f
#define DEFAULT_MPU_HZ  100


MPU_DataTypedef MPU_DataStruct;
static const int8_t gyro_orientation[9] = {1, 0, 0,
                                           0, 1, 0,
                                           0, 0, 1};

/**
  * @brief  MPU6050初始化程序
  * @retval SUCCESS | ERROR
  * @note   执行前需要先初始化IO口为推挽输出模式
  */
uint8_t MPU6050_Init(void)
{
    MPU_Write(MPU6050_PWR_MGMT1, 0x80);     //休眠
    delay_ms(100);
    MPU_Write(MPU6050_PWR_MGMT1, 0x00);     //唤醒
    MPU_SetGyroRange(3);                    //陀螺仪传感器,±2000°/s
    MPU_SetAccelRange(0);                   //加速度传感器,±2g
    MPU_SetSamplingRate(50);                //设置采样率50Hz
    MPU_Write(MPU6050_INT_ENABLE, 0x00);    //关闭所有中断
    MPU_Write(MPU6050_USER_CTRL, 0x00);     //I2C主模式关闭
    MPU_Write(MPU6050_FIFO_EN, 0x00);       //关闭FIFO
    MPU_Write(MPU6050_INT_PIN_CFG, 0x80);   //INT引脚低电平有效

    if(MPU_Read(MPU6050_WHO_AM_I)==(MPU6050_ADDR>>1))
    {
        MPU_Write(MPU6050_PWR_MGMT1, 0x01); //设置CLKSEL,PLL X轴为参考
        MPU_Write(MPU6050_PWR_MGMT2, 0x00); //加速度与陀螺仪都工作
        MPU_SetSamplingRate(50);            //设置采样率为50Hz
        return SUCCESS;
    }
    return ERROR;
}

/* MPU6050 Set functions -----------------------------------------------------*/
/**
  * @brief  设定陀螺仪的量程
  * @param  FS_SEL: New full-scale gyroscope range value
  *           0:    ± 250°/s
  *           1:    ± 500°/s
  *           2:    ±1000°/s
  *           3:    ±2000°/s
  * @retval 0: Success | 1: Fail
  */
uint8_t MPU_SetGyroRange(uint8_t range)
{
    return MPU_Write(MPU6050_GYRO_CFG, range<<3); 
}

/**
  * @brief  设定加速度计的量程
  * @param  AFS_SEL: New full-scale accelerometer range value
  *            0:       ±2g
  *            1:       ±4g
  *            2:       ±8g
  *            3:       ±16g
  * @retval 0: Success | 1: Fail
  */
uint8_t MPU_SetAccelRange(uint8_t FullScaleRange_Select)
{
    return MPU_Write(MPU6050_ACCEL_CFG, FullScaleRange_Select<<3);
}

/**
  * @brief  设置数字低通滤波器(Digital low-pass filter)
  * @param  frequency: New frequency to filter out
  * @retval 0: Success | 1: Fail
  */
uint8_t MPU_SetFilter(uint16_t frequency)
{
    uint8_t temp = 0;

    if(frequency >= 188)
        temp = 1;
	else if(frequency >= 98)
        temp = 2;
    else if(frequency >= 42)
        temp = 3;
    else if(frequency >= 20)
        temp = 4;
    else if(frequency >= 10)
        temp = 5;
    else
        temp = 6;

    return MPU_Write(MPU6050_CONFIG, temp);
}

/**
  * @brief  设置采样率
  * @param  frequency: 4Hz~1kHz
  * @retval 0: Success | 1: Fail
  * @note   采样频率 = 陀螺仪输出频率 / (1+SMPLRT_DIV)
  * @note   当低通滤波器使能时，陀螺仪输出频率为1kHz
  *         当低通滤波器禁用时，陀螺仪输出频率为8kHz
  */
uint8_t MPU_SetSamplingRate(uint16_t frequency)
{
    if(frequency > 1000)
        frequency = 1000;
    if(frequency < 4)
        frequency = 4;

    MPU_Write(MPU6050_SMPRT_DIV, frequency/1000-1);
    return MPU_SetFilter(frequency>>1);
}


/**
  * @brief  更新内部温度值
  * @param  None
  * @retval None
  */
uint8_t MPU_TempUpdate(void)
{
    uint8_t buf[2];
    short raw;

    if(MPU_ReadBytes(MPU6050_TEMP_OUT_H, buf, 2)!=ERROR)
    {
        raw = ((uint16_t)buf[0]<<8) | buf[1];
        MPU_DataStruct.temperature = 36.53+((double)raw)/340;
        return SUCCESS;
    }
    return ERROR;
}

/**
  * @brief  更新陀螺仪值(原始值)
  * @param  None
  * @retval 0: Success | 1: Fail
  */
uint8_t MPU_GyroUpdate(void)
{
    uint8_t buf[6];

	if(MPU_ReadBytes(MPU6050_GYRO_XOUT_H, buf, 6)!=ERROR)
	{
		MPU_DataStruct.gyro[0] = ((uint16_t)buf[0]<<8)|buf[1];
		MPU_DataStruct.gyro[1] = ((uint16_t)buf[2]<<8)|buf[3];
		MPU_DataStruct.gyro[2] = ((uint16_t)buf[4]<<8)|buf[5];
        return SUCCESS;
    }
    return ERROR;
}

/**
  * @brief  更新加速度(原始值)
  * @param  None
  * @retval 0: Success | 1: Fail
  */
uint8_t MPU_AccelUpdate(void)
{
    uint8_t buf[6];

	if(MPU_ReadBytes(MPU6050_ACCEL_XOUT_H, buf, 6)!=ERROR)
	{
		MPU_DataStruct.accel[0] = ((uint16_t)buf[0]<<8)|buf[1];  
		MPU_DataStruct.accel[1] = ((uint16_t)buf[2]<<8)|buf[3];  
		MPU_DataStruct.accel[2] = ((uint16_t)buf[4]<<8)|buf[5];
        return SUCCESS;
    }
    return ERROR;
}


/* DMP functions -------------------------------------------------------------*/
/**
  * @brief  MPU6050 DMP解算初始化程序
  * @retval 0: Success | others: Fail
  * @note   执行前需要先执行MPU6050初始化
  */
uint8_t DMP_Init(void)
{
    if(mpu_init())
        return 1;
	/* 设置传感器 */
    if(mpu_set_sensors(INV_XYZ_GYRO|INV_XYZ_ACCEL))
        return 2;

    /* 设置FIFO */
    if(mpu_configure_fifo(INV_XYZ_GYRO|INV_XYZ_ACCEL))
        return 3;

    /* 设定采样率 */
    if(mpu_set_sample_rate(DEFAULT_MPU_HZ))
        return 4; 

    /* 加载DMP固件 */
    if(dmp_load_motion_driver_firmware())
        return 5;

    /* 设置陀螺仪方向 */
    if(dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))
        return 6;

    /* 设置DMP功能 */
    if(dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT|DMP_FEATURE_TAP|DMP_FEATURE_ANDROID_ORIENT
                |DMP_FEATURE_SEND_RAW_ACCEL|DMP_FEATURE_SEND_CAL_GYRO|DMP_FEATURE_GYRO_CAL))
        return 7;

    /* 设置DMP输出速率(不超过200Hz) */
    if(dmp_set_fifo_rate(DEFAULT_MPU_HZ))
        return 8;

    /* 自检 */
    if(run_self_test())
        return 9;

    /* 使能DMP */
    if(mpu_set_dmp_state(ENABLE))
        return 10;

	return 0;
}


/**
  * @brief  得到dmp处理后的数据
  * @param  None
  * @retval 0: Success | 1: Fail
  * @attention
  *     pitch: 俯仰角  精度:0.1° 范围:-90.0° ~ +90.0°
  *     roll : 横滚角  精度:0.1° 范围:-180.0°~ +180.0°
  *     yaw  : 航向角  精度:0.1° 范围:-180.0°~ +180.0°
  */
uint8_t DMP_Update(void)
{
	float q0=1.0f, q1=0.0f, q2=0.0f, q3=0.0f;
	unsigned long timestamp;
	short sensors;
	unsigned char more;
	long quat[4];

	if(dmp_read_fifo(MPU_DataStruct.gyro, MPU_DataStruct.accel, quat, &timestamp, &sensors, &more))
        return ERROR;	 
	/* Gyro and accel data are written to the FIFO by the DMP in chip frame and hardware units.
	 * This behavior is convenient because it keeps the gyro and accel outputs of dmp_read_fifo and mpu_read_fifo consistent.
	**/
	/*if (sensors & INV_XYZ_GYRO )
	send_packet(PACKET_TYPE_GYRO, gyro);
	if (sensors & INV_XYZ_ACCEL)
	send_packet(PACKET_TYPE_ACCEL, accel); */
	/* Unlike gyro and accel, quaternions are written to the FIFO in the body frame, q30.
	 * The orientation is set by the scalar passed to dmp_set_orientation during initialization. 
	**/
	if(sensors & INV_WXYZ_QUAT) 
	{
		q0 = quat[0] / q30;	//q30格式转换为浮点数
		q1 = quat[1] / q30;
		q2 = quat[2] / q30;
		q3 = quat[3] / q30;


		MPU_DataStruct.pitch = asin(-2*q1*q3 + 2*q0*q2) * 57.3;
		MPU_DataStruct.roll  = atan2(2*q2*q3 + 2*q0*q1, -2*q1*q1 - 2*q2*q2 + 1) * 57.3;
		MPU_DataStruct.yaw   = atan2(2*(q1*q2 + q0*q3), q0*q0 + q1*q1 - q2*q2 - q3*q3) * 57.3;
        return SUCCESS;
	}
    return ERROR;
}


/******************************** END OF FILE *********************************/
