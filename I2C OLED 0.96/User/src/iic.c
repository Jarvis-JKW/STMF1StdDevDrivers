/**
  ******************************************************************************
  * @file    /User/src/iic.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    10-Aug-2022
  * @brief   IIC communication program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * ��Buffer Write����������Ҫ�ֽڶ�������ҳ���ƣ��ʽ����滻Ϊ���ֽ���һд��
  * ������: 7λ��ַ�豸��8λ�ڲ�Ѱַ�ռ��豸
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "iic.h"

/* Private define ------------------------------------------------------------*/
/**
  * @brief  I2C Init program.
  * @param  None
  * @retval None
  */
void I2C_Config(void)
{
    I2C_InitTypeDef I2C_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    I2C_DeInit(I2C1);
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = 400000;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_OwnAddress1 = 0xC0;
    I2C_Init(I2C1, &I2C_InitStructure);

    I2C_Cmd(I2C1, ENABLE);
}



/**
  * @brief  write a byte via I2Cx
  * @param  I2Cx: I2C1 | I2C2
  *         slaveAddr: 8 bit device address
  *         regAddr: word address
  *         data: the byte to be written
  * @retval SUCCESS | ERROR
  */
uint8_t I2C_Write(I2C_TypeDef* I2Cx ,uint8_t slaveAddr, uint8_t regAddr, uint8_t data)
{
    uint8_t time = 0;

    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2Cx, ENABLE);
    while(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);

    /* ����������ַ + д���� */
    I2C_Send7bitAddress(I2Cx, slaveAddr, I2C_Direction_Transmitter);
    while(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS)
    {
        if(time++>250)
            goto timeout;
    }
    time = 0;

    /* д�Ĵ�����ַ */
    I2C_SendData(I2Cx, regAddr);
    while(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS)
    {
        if(time++>250)
            goto timeout;
    }
    time = 0;

    /* �������� */
    I2C_SendData(I2Cx, data);
    while(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS)
    {
        if(time++>250)
            goto timeout;
    }
    I2C_GenerateSTOP(I2Cx, ENABLE);

    return SUCCESS;

timeout:
    I2C_GenerateSTOP(I2Cx, ENABLE);
    return ERROR;
}


/**
  * @brief  write len bytes via I2Cx
  * @param  I2Cx: I2C1 | I2C2 
  *         slaveAddr: 8 bit device address
  *         regAddr: word address
  *         data: array that stores data to be written
  *         len: number of bytes
  * @retval SUCCESS | ERROR
  */
uint8_t I2C_WriteBytes(I2C_TypeDef* I2Cx, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint8_t len)
{
    uint8_t time = 0;

    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));

    I2C_GenerateSTART(I2Cx, ENABLE);
    while(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)!=SUCCESS);

    I2C_Send7bitAddress(I2Cx, slaveAddr, I2C_Direction_Transmitter);
    while(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)!=SUCCESS)
    {
        if(time++>250)
            goto timeout;
    }
    time = 0;

    I2C_SendData(I2Cx, regAddr);
    while(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS)
    {
        if(time++>250)
            goto timeout;
    }
    time = 0;

    /* �������� */
    while(len--)
    {
        I2C_SendData(I2Cx, *data++);
        while(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)!=SUCCESS)
        {
            if(time++>250)
                goto timeout;
        }
        time = 0;
    }
    I2C_GenerateSTOP(I2Cx, ENABLE);

    return SUCCESS;

timeout:
    I2C_GenerateSTOP(I2Cx, ENABLE);
    return ERROR;
}

/******************************** END OF FILE *********************************/
