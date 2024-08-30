/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MPU6050_H
#define __MPU6050_H

#include "main.h"
#include "iic.h"

typedef struct
{
    short gyro[3], accel[3];
    float temperature;
    float pitch, roll;
}MPU_DataTypedef;

typedef struct
{
    float Q_angle;
    float Q_gyro;
    float Q_bias, err; 
    float R_angle, dt;
    float K[2], t[2];
    float PCt[2], E;
    float P[4], PP[2][2];
    char C_0;
}Kalman_t;

extern MPU_DataTypedef MPU_DataStruct;

/* MPU6050 Register Address --------------------------------------------------*/
#define MPU6050_SELF_TEST_X         0x0D
#define MPU6050_SELF_TEST_Y         0x0E
#define MPU6050_SELF_TEST_Z         0x0F
#define MPU6050_SELF_TEST_A         0x10

#define MPU6050_SMPRT_DIV           0x19    //采样频率分频器
#define MPU6050_CONFIG              0x1A    //配置（FSYNC引脚采样/低通滤波器）
#define MPU6050_GYRO_CFG            0x1B    //陀螺仪配置
#define MPU6050_ACCEL_CFG           0x1C    //加速度计配置/高通滤波器

#define MPU6050_MOT_DETECT_THR      0x1F    //运动检测阀值

#define MPU6050_INT_PIN_CFG         0x37    //INT引脚/旁路有效
#define MPU6050_INT_ENABLE          0x38    //中断使能
#define MPU6050_INT_STATUS          0x3A    //中断状态
/* 加速度计 */
#define MPU6050_ACCEL_XOUT_H        0x3B
#define MPU6050_ACCEL_XOUT_L        0x3C
#define MPU6050_ACCEL_YOUT_H        0x3D
#define MPU6050_ACCEL_YOUT_L        0x3E
#define MPU6050_ACCEL_ZOUT_H        0x3F
#define MPU6050_ACCEL_ZOUT_L        0x40
/* 温度计 */
#define MPU6050_TEMP_OUT_H          0x41
#define MPU6050_TEMP_OUT_L          0x42
/* 陀螺仪 */
#define MPU6050_GYRO_XOUT_H         0x43
#define MPU6050_GYRO_XOUT_L         0x44
#define MPU6050_GYRO_YOUT_H         0x45
#define MPU6050_GYRO_YOUT_L         0x46
#define MPU6050_GYRO_ZOUT_H         0x47
#define MPU6050_GYRO_ZOUT_L         0x48

#define MPU6050_SIGNAL_PATH_RESET   0x68    //信号通道复位
#define MPU6050_MDT_DETECT_CTRL     0x69    //运动检测控制
#define MPU6050_USER_CTRL           0x6A    //用户控制
#define MPU6050_PWR_MGMT1           0x6B    //电源管理1:电源模式/时钟源/复位/禁用温度传感器
#define MPU6050_PWR_MGMT2           0x6C    //电源管理2:低功耗/待机模式配置

#define MPU6050_WHO_AM_I            0x75    //IIC地址
 
/* Private macro -------------------------------------------------------------*/
#define MPU_Write(addr, data)           I2C_Write(I2C2, MPU6050_ADDR, addr, data)
#define MPU_WriteBytes(addr, data, len) I2C_WriteBytes(I2C2, MPU6050_ADDR, addr, data, len)
#define MPU_Read(addr)                  I2C_Read(I2C2, MPU6050_ADDR, addr)
#define MPU_ReadBytes(addr, data, len)  I2C_ReadBytes(I2C2, MPU6050_ADDR, addr, data, len)
/* Private function prototypes -----------------------------------------------*/
uint8_t MPU6050_Init(void);
uint8_t MPU_GyroUpdate(void);
uint8_t MPU_AccelUpdate(void);
uint8_t MPU_TempUpdate(void);
void Kalman_UpdateData(void);
#endif /* __MPU6050_H */
/******************************** END OF FILE *********************************/
