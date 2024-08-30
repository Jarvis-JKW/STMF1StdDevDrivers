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
  * @brief  MPU6050��ʼ������
  * @retval SUCCESS | ERROR
  * @note   ִ��ǰ��Ҫ�ȳ�ʼ��IO��Ϊ�������ģʽ
  */
uint8_t MPU6050_Init(void)
{
    MPU_Write(MPU6050_PWR_MGMT1, 0x80);     //����
    delay_ms(100);
    MPU_Write(MPU6050_PWR_MGMT1, 0x00);     //����
    MPU_SetGyroRange(3);                    //�����Ǵ�����,��2000��/s
    MPU_SetAccelRange(0);                   //���ٶȴ�����,��2g
    MPU_SetSamplingRate(50);                //���ò�����50Hz
    MPU_Write(MPU6050_INT_ENABLE, 0x00);    //�ر������ж�
    MPU_Write(MPU6050_USER_CTRL, 0x00);     //I2C��ģʽ�ر�
    MPU_Write(MPU6050_FIFO_EN, 0x00);       //�ر�FIFO
    MPU_Write(MPU6050_INT_PIN_CFG, 0x80);   //INT���ŵ͵�ƽ��Ч

    if(MPU_Read(MPU6050_WHO_AM_I)==(MPU6050_ADDR>>1))
    {
        MPU_Write(MPU6050_PWR_MGMT1, 0x01); //����CLKSEL,PLL X��Ϊ�ο�
        MPU_Write(MPU6050_PWR_MGMT2, 0x00); //���ٶ��������Ƕ�����
        MPU_SetSamplingRate(50);            //���ò�����Ϊ50Hz
        return SUCCESS;
    }
    return ERROR;
}

/* MPU6050 Set functions -----------------------------------------------------*/
/**
  * @brief  �趨�����ǵ�����
  * @param  FS_SEL: New full-scale gyroscope range value
  *           0:    �� 250��/s
  *           1:    �� 500��/s
  *           2:    ��1000��/s
  *           3:    ��2000��/s
  * @retval 0: Success | 1: Fail
  */
uint8_t MPU_SetGyroRange(uint8_t range)
{
    return MPU_Write(MPU6050_GYRO_CFG, range<<3); 
}

/**
  * @brief  �趨���ٶȼƵ�����
  * @param  AFS_SEL: New full-scale accelerometer range value
  *            0:       ��2g
  *            1:       ��4g
  *            2:       ��8g
  *            3:       ��16g
  * @retval 0: Success | 1: Fail
  */
uint8_t MPU_SetAccelRange(uint8_t FullScaleRange_Select)
{
    return MPU_Write(MPU6050_ACCEL_CFG, FullScaleRange_Select<<3);
}

/**
  * @brief  �������ֵ�ͨ�˲���(Digital low-pass filter)
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
  * @brief  ���ò�����
  * @param  frequency: 4Hz~1kHz
  * @retval 0: Success | 1: Fail
  * @note   ����Ƶ�� = ���������Ƶ�� / (1+SMPLRT_DIV)
  * @note   ����ͨ�˲���ʹ��ʱ�����������Ƶ��Ϊ1kHz
  *         ����ͨ�˲�������ʱ�����������Ƶ��Ϊ8kHz
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
  * @brief  �����ڲ��¶�ֵ
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
  * @brief  ����������ֵ(ԭʼֵ)
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
  * @brief  ���¼��ٶ�(ԭʼֵ)
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
  * @brief  MPU6050 DMP�����ʼ������
  * @retval 0: Success | others: Fail
  * @note   ִ��ǰ��Ҫ��ִ��MPU6050��ʼ��
  */
uint8_t DMP_Init(void)
{
    if(mpu_init())
        return 1;
	/* ���ô����� */
    if(mpu_set_sensors(INV_XYZ_GYRO|INV_XYZ_ACCEL))
        return 2;

    /* ����FIFO */
    if(mpu_configure_fifo(INV_XYZ_GYRO|INV_XYZ_ACCEL))
        return 3;

    /* �趨������ */
    if(mpu_set_sample_rate(DEFAULT_MPU_HZ))
        return 4; 

    /* ����DMP�̼� */
    if(dmp_load_motion_driver_firmware())
        return 5;

    /* ���������Ƿ��� */
    if(dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))
        return 6;

    /* ����DMP���� */
    if(dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT|DMP_FEATURE_TAP|DMP_FEATURE_ANDROID_ORIENT
                |DMP_FEATURE_SEND_RAW_ACCEL|DMP_FEATURE_SEND_CAL_GYRO|DMP_FEATURE_GYRO_CAL))
        return 7;

    /* ����DMP�������(������200Hz) */
    if(dmp_set_fifo_rate(DEFAULT_MPU_HZ))
        return 8;

    /* �Լ� */
    if(run_self_test())
        return 9;

    /* ʹ��DMP */
    if(mpu_set_dmp_state(ENABLE))
        return 10;

	return 0;
}


/**
  * @brief  �õ�dmp����������
  * @param  None
  * @retval 0: Success | 1: Fail
  * @attention
  *     pitch: ������  ����:0.1�� ��Χ:-90.0�� ~ +90.0��
  *     roll : �����  ����:0.1�� ��Χ:-180.0��~ +180.0��
  *     yaw  : �����  ����:0.1�� ��Χ:-180.0��~ +180.0��
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
		q0 = quat[0] / q30;	//q30��ʽת��Ϊ������
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
