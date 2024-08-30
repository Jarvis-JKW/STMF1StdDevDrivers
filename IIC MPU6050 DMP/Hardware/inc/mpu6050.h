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

#define MPU6050_SMPRT_DIV           0x19    //����Ƶ�ʷ�Ƶ��
#define MPU6050_CONFIG              0x1A    //���ã�FSYNC���Ų���/��ͨ�˲�����
#define MPU6050_GYRO_CFG            0x1B    //����������
#define MPU6050_ACCEL_CFG           0x1C    //���ٶȼ�����/��ͨ�˲���

#define MPU6050_MOT_DETECT_THR      0x1F    //�˶���ֵⷧ
#define MPU6050_FIFO_EN             0x23    //FIFOʹ��

#define MPU6050_I2C_MST_CTRL        0x24    //��������
/* I2C�ӻ�0 */
#define MPU6050_SLV0_ADDR           0x25
#define MPU6050_SLV0_REG            0x26
#define MPU6050_SLV0_CTRL           0x27
#define MPU6050_SLV0_DO             0x63
/* I2C�ӻ�0 */
#define MPU6050_SLV1_ADDR           0x28
#define MPU6050_SLV1_REG            0x29
#define MPU6050_SLV1_CTRL           0x2A
#define MPU6050_SLV1_DO             0x64
/* I2C�ӻ�1 */
#define MPU6050_SLV2_ADDR           0x2B
#define MPU6050_SLV2_REG            0x2C
#define MPU6050_SLV2_CTRL           0x2D
#define MPU6050_SLV2_DO             0x65
/* I2C�ӻ�2 */
#define MPU6050_SLV3_ADDR           0x2E
#define MPU6050_SLV3_REG            0x2F
#define MPU6050_SLV3_CTRL           0x30
#define MPU6050_SLV3_DO             0x66
/* I2C�ӻ�3 */
#define MPU6050_SLV4_ADDR           0x31
#define MPU6050_SLV4_REG            0x32
#define MPU6050_SLV4_DO             0x33
#define MPU6050_SLV4_CTRL           0x34
#define MPU6050_SLV4_DI             0x35

#define MPU6050_I2C_MST_STATUS      0x36    //IIC����״̬
#define MPU6050_INT_PIN_CFG         0x37    //INT����/��·��Ч
#define MPU6050_INT_ENABLE          0x38    //�ж�ʹ��
#define MPU6050_INT_STATUS          0x3A    //�ж�״̬
/* ���ٶȼ� */
#define MPU6050_ACCEL_XOUT_H        0x3B
#define MPU6050_ACCEL_XOUT_L        0x3C
#define MPU6050_ACCEL_YOUT_H        0x3D
#define MPU6050_ACCEL_YOUT_L        0x3E
#define MPU6050_ACCEL_ZOUT_H        0x3F
#define MPU6050_ACCEL_ZOUT_L        0x40
/* �¶ȼ� */
#define MPU6050_TEMP_OUT_H          0x41
#define MPU6050_TEMP_OUT_L          0x42
/* ������ */
#define MPU6050_GYRO_XOUT_H         0x43
#define MPU6050_GYRO_XOUT_L         0x44
#define MPU6050_GYRO_YOUT_H         0x45
#define MPU6050_GYRO_YOUT_L         0x46
#define MPU6050_GYRO_ZOUT_H         0x47
#define MPU6050_GYRO_ZOUT_L         0x48
/* �˴�ʡ�������ⲿ���������ݼĴ������� */
#define MPU6050_EXT_SENS_DATA_00    0x49
#define MPU6050_EXT_SENS_DATA_23    0x49+23

#define MPU6050_I2C_MST_DELAY_CTRL  0x67    //IIC������ʱ����
#define MPU6050_SIGNAL_PATH_RESET   0x68    //�ź�ͨ����λ
#define MPU6050_MDT_DETECT_CTRL     0x69    //�˶�������
#define MPU6050_USER_CTRL           0x6A    //�û�����
#define MPU6050_PWR_MGMT1           0x6B    //��Դ����1:��Դģʽ/ʱ��Դ/��λ/�����¶ȴ�����
#define MPU6050_PWR_MGMT2           0x6C    //��Դ����2:�͹���/����ģʽ����
#define MPU6050_FIFO_COUNT_H        0x72    //FIFO����
#define MPU6050_FIFO_COUNT_L        0x73
#define MPU6050_FIFO_R_W            0x74    //FIFO��д
#define MPU6050_WHO_AM_I            0x75    //IIC��ַ
 
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
