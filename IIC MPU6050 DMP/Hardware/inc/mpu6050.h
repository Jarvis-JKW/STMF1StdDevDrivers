/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MPU6050_H
#define __MPU6050_H

#include "main.h"
#include "iic.h"

typedef struct
{
    short gyro[3], accel[3];
    float temperature;
    float pitch, roll, yaw;
}MPU_DataTypedef;

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
#define MPU6050_FIFO_EN             0x23    //FIFO使能

#define MPU6050_I2C_MST_CTRL        0x24    //主机控制
/* I2C从机0 */
#define MPU6050_SLV0_ADDR           0x25
#define MPU6050_SLV0_REG            0x26
#define MPU6050_SLV0_CTRL           0x27
#define MPU6050_SLV0_DO             0x63
/* I2C从机0 */
#define MPU6050_SLV1_ADDR           0x28
#define MPU6050_SLV1_REG            0x29
#define MPU6050_SLV1_CTRL           0x2A
#define MPU6050_SLV1_DO             0x64
/* I2C从机1 */
#define MPU6050_SLV2_ADDR           0x2B
#define MPU6050_SLV2_REG            0x2C
#define MPU6050_SLV2_CTRL           0x2D
#define MPU6050_SLV2_DO             0x65
/* I2C从机2 */
#define MPU6050_SLV3_ADDR           0x2E
#define MPU6050_SLV3_REG            0x2F
#define MPU6050_SLV3_CTRL           0x30
#define MPU6050_SLV3_DO             0x66
/* I2C从机3 */
#define MPU6050_SLV4_ADDR           0x31
#define MPU6050_SLV4_REG            0x32
#define MPU6050_SLV4_DO             0x33
#define MPU6050_SLV4_CTRL           0x34
#define MPU6050_SLV4_DI             0x35

#define MPU6050_I2C_MST_STATUS      0x36    //IIC主机状态
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
/* 此处省略若干外部传感器数据寄存器定义 */
#define MPU6050_EXT_SENS_DATA_00    0x49
#define MPU6050_EXT_SENS_DATA_23    0x49+23

#define MPU6050_I2C_MST_DELAY_CTRL  0x67    //IIC主机延时管理
#define MPU6050_SIGNAL_PATH_RESET   0x68    //信号通道复位
#define MPU6050_MDT_DETECT_CTRL     0x69    //运动检测控制
#define MPU6050_USER_CTRL           0x6A    //用户控制
#define MPU6050_PWR_MGMT1           0x6B    //电源管理1:电源模式/时钟源/复位/禁用温度传感器
#define MPU6050_PWR_MGMT2           0x6C    //电源管理2:低功耗/待机模式配置
#define MPU6050_FIFO_COUNT_H        0x72    //FIFO计数
#define MPU6050_FIFO_COUNT_L        0x73
#define MPU6050_FIFO_R_W            0x74    //FIFO读写
#define MPU6050_WHO_AM_I            0x75    //IIC地址
 
/* Private macro -------------------------------------------------------------*/
#define MPU_Write(addr, data)           IIC_Write(&IIC2, MPU6050_ADDR, addr, data)
#define MPU_WriteBytes(addr, data, len) IIC_WriteBytes(&IIC2, MPU6050_ADDR, addr, data, len)
#define MPU_Read(addr)                  IIC_Read(&IIC2, MPU6050_ADDR, addr)
#define MPU_ReadBytes(addr, data, len)  IIC_ReadBytes(&IIC2, MPU6050_ADDR, addr, data, len)
/* Private function prototypes -----------------------------------------------*/
uint8_t MPU6050_Init(void);
uint8_t DMP_Init(void);

uint8_t MPU_SetGyroRange(uint8_t range);
uint8_t MPU_SetAccelRange(uint8_t range);
uint8_t MPU_SetFilter(uint16_t frequency);
uint8_t MPU_SetSamplingRate(uint16_t frequency);

uint8_t MPU_GyroUpdate(void);
uint8_t MPU_AccelUpdate(void);
uint8_t MPU_TempUpdate(void);
uint8_t DMP_Update(void);



#endif /* __MPU6050_H */
/******************************** END OF FILE *********************************/
