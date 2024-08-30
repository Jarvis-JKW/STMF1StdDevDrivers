/**
  ******************************************************************************
  * @file    /User/src/mpu6050.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    11-Aug-2022
  * @brief   MPU6050 driver via I2C bus.
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "mpu6050.h"
#include <math.h>

#define PI  3.14159265
MPU_DataTypedef MPU_DataStruct;
Kalman_t KalmanX = 
{       .Q_angle = 1e-3,
        .Q_gyro = 3e-3,
        .R_angle = 0.5,
        .dt = 0.02,
        .C_0 = 1,
        .PP[0][0] = 1,
        .PP[1][1] = 1
};
Kalman_t KalmanY = 
{       .Q_angle = 1e-3,
        .Q_gyro = 3e-3,
        .R_angle = 0.5,
        .dt = 0.02,
        .C_0 = 1,
        .PP[0][0] = 1,
        .PP[1][1] = 1
};
static float temp_gyro[3], temp_accel[3], temp_angleX, temp_angleY;



/**
  * @brief  MPU6050初始化程序
  * @retval SUCCESS | ERROR
  * @note   执行前需要先初始化IO口为推挽输出模式
  */
uint8_t MPU6050_Init(void)
{
    MPU_Write(MPU6050_PWR_MGMT1, 0x00);
    if(MPU_Read(MPU6050_WHO_AM_I)==(MPU6050_ADDR>>1))
    {
        MPU_Write(MPU6050_SMPRT_DIV, 0x07);
        MPU_Write(MPU6050_CONFIG, 0x06);
        MPU_Write(MPU6050_GYRO_CFG, 0x18);
        MPU_Write(MPU6050_ACCEL_CFG, 0x01);
        return SUCCESS;
    }
    return ERROR;
}

/* MPU6050 Set functions -----------------------------------------------------*/
/**
  * @brief  更新内部温度值
  * @param  None
  * @retval SUCCESS | ERROR
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
  * @retval SUCCESS | ERROR
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
  * @retval SUCCESS | ERROR
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


/* Kalman Filter functions ---------------------------------------------------*/

void Kalman_Filter(float accel, float gyro, float* angle, short* target, Kalman_t* Kalman)
{
    /* Estimate */
    *angle += (gyro - Kalman->Q_bias) * Kalman->dt;
    /* Calculate the differential matrix of process covariance matrix */
    Kalman->P[0] = Kalman->Q_angle - Kalman->PP[0][1] - Kalman->PP[1][0];
    Kalman->P[1] = Kalman->P[2] = - Kalman->PP[1][1];
    Kalman->P[3] = Kalman->Q_gyro;
    
    Kalman->PP[0][0] += Kalman->P[0] * Kalman->dt;
    Kalman->PP[0][1] += Kalman->P[1] * Kalman->dt;
    Kalman->PP[1][0] += Kalman->P[2] * Kalman->dt;
    Kalman->PP[1][1] += Kalman->P[3] * Kalman->dt;
    
    Kalman->err = accel - *angle;
    
    /* Calculate Kalman gain */
    Kalman->PCt[0] = Kalman->C_0 * Kalman->PP[0][0];
    Kalman->PCt[1] = Kalman->C_0 * Kalman->PP[1][0];
    
    Kalman->E = Kalman->R_angle + Kalman->C_0 * Kalman->PCt[0];
    Kalman->K[0] = Kalman->PCt[0] / Kalman->E;
    Kalman->K[1] = Kalman->PCt[1] / Kalman->E;
    
    /* Posterior estimation error covariance */
    Kalman->t[0] = Kalman->PCt[0];
    Kalman->t[1] = Kalman->C_0 * Kalman->PP[0][1];
    
    Kalman->PP[0][0] -= Kalman->K[0] * Kalman->t[0];
    Kalman->PP[0][1] -= Kalman->K[0] * Kalman->t[1];
    Kalman->PP[1][0] -= Kalman->K[1] * Kalman->t[0];
    Kalman->PP[1][1] -= Kalman->K[1] * Kalman->t[1];
    
    /* Calculate the optimal angular velocity */
    *angle += Kalman->K[0] * Kalman->err;
    Kalman->Q_bias += Kalman->K[1] * Kalman->err;
    *target = gyro - Kalman->Q_bias;

}


void Kalman_UpdateData(void)
{
    uint8_t i;

    MPU_AccelUpdate();
    MPU_GyroUpdate();
    MPU_TempUpdate();
    
    for(i = 0; i < 3; i++)
    {
        temp_gyro[i] = MPU_DataStruct.gyro[i];
        temp_accel[i] = MPU_DataStruct.accel[i];
    }
    temp_accel[0] = temp_accel[0] < 32768 ? temp_accel[0]/16384:1-(temp_accel[0]-49152)/16384;
    temp_accel[1] = temp_accel[1] < 32768 ? temp_accel[1]/16384:1-(temp_accel[1]-49152)/16384;
    temp_accel[2] = temp_accel[2] < 32768 ? temp_accel[2]/16384:  (temp_accel[2]-49152)/16384;
    
    temp_angleX = (atan(temp_accel[1]/temp_accel[2]))*180/PI;
    temp_angleY = (atan(temp_accel[0]/temp_accel[2]))*180/PI;
    temp_angleX *= MPU_DataStruct.accel[1] < 32764 ? 1:-1;
    temp_angleY *= MPU_DataStruct.accel[0] < 32764 ? 1:-1;
    
    temp_gyro[0] = temp_gyro[0] < 32768 ? -(temp_gyro[0]/16.4):(65535-temp_gyro[0])/16.4;
    temp_gyro[1] = temp_gyro[0] < 32768 ? -(temp_gyro[1]/16.4):(65535-temp_gyro[1])/16.4;
    temp_gyro[2] = temp_gyro[0] < 32768 ? -(temp_gyro[2]/16.4):(65535-temp_gyro[2])/16.4;
    
    Kalman_Filter(temp_angleX, temp_gyro[0], &MPU_DataStruct.pitch, &MPU_DataStruct.gyro[0], &KalmanX);
    Kalman_Filter(temp_angleY, temp_gyro[1], &MPU_DataStruct.roll,  &MPU_DataStruct.gyro[1], &KalmanY);
}



/******************************** END OF FILE *********************************/
