/**
  ******************************************************************************
  * @file    /User/src/iic.c 
  * @author  Jarvis-JKW
  * @version V0.0.2
  * @date    11-Aug-2022
  * @brief   IIC communication program body
  ******************************************************************************
  * @attention
  * This project uses Chinese GB2312 as encoding.
  * 适用于: 7位地址设备，8位内部寻址空间设备
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "iic.h"


IIC_TypeDef IIC2 = {GPIOB, GPIOB, GPIO_Pin_10, GPIO_Pin_11};
/**
  * @brief  IIC 端口I/O 配置.
  * @param  IICx: IIC_Typedef structure
  * @param  mode: IIC_SDA_Mode_Out | IIC_SDA_Mode_IN
  * @retval None
  */
static void IIC_SDA_Set(IIC_TypeDef* IICx, IIC_SDA_Mode mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = IICx->SDA_Pin;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = mode;

    GPIO_Init(IICx->SDA_Port, &GPIO_InitStructure);
}


/**
  * @brief  等待确认信息
  * @param  IICx: IIC_Typedef structure
  * @retval SUCCESS: 接收成功 | ERROR: 接收超时
  */
static uint8_t IIC_Wait_ACK(IIC_TypeDef* IICx)
{
	uint8_t time = 0;

    IIC_SDA_Set(IICx, IIC_SDA_Mode_IN);

    GPIO_SetBits(IICx->SDA_Port, IICx->SDA_Pin);
    delay_us(1);
    GPIO_SetBits(IICx->SCL_Port, IICx->SCL_Pin);
    delay_us(1);

	while(GPIO_ReadInputDataBit(IICx->SDA_Port, IICx->SDA_Pin))
	{
		if(time++>250)
		{
			IIC_GenerateSTOP(IICx);
			return ERROR;
		}
	}
    GPIO_ResetBits(IICx->SCL_Port, IICx->SCL_Pin);
	return SUCCESS;  
}


/**
  * @brief  IIC应答ACK或NACK
  * @param  IICx: IIC_Typedef structure
  *         ACK_State: ACK | NACK
  * @retval None
  */
static void IIC_Response(IIC_TypeDef* IICx, BitAction ACK_State)
{
    GPIO_ResetBits(IICx->SCL_Port, IICx->SCL_Pin);

    IIC_SDA_Set(IICx, IIC_SDA_Mode_Out);

    //高电平为NACK，低电平为ACK
    GPIO_WriteBit(IICx->SDA_Port, IICx->SDA_Pin, ACK_State);
    delay_us(1);//

    GPIO_SetBits(IICx->SCL_Port, IICx->SCL_Pin);
    delay_us(1);//

    GPIO_ResetBits(IICx->SCL_Port, IICx->SCL_Pin);
}


/**
  * @brief  Generates IICx communication START condition.
  * @param  IICx: IIC_Typedef structure
  * @retval None
  * @note   当SCL为高电平时，SDA下降沿触发起始信号
  */
void IIC_GenerateSTART(IIC_TypeDef* IICx)
{
    IIC_SDA_Set(IICx, IIC_SDA_Mode_Out);

    GPIO_SetBits(IICx->SDA_Port, IICx->SDA_Pin);  //拉高SDA
    GPIO_SetBits(IICx->SCL_Port, IICx->SCL_Pin);  //拉高SCL
    delay_us(1);//

    GPIO_ResetBits(IICx->SDA_Port, IICx->SDA_Pin);//产生下降沿
    delay_us(1);//

    GPIO_ResetBits(IICx->SCL_Port, IICx->SCL_Pin);//拉低CLK，保证状态稳定
}


/**
  * @brief  Generates IICx communication STOP condition.
  * @param  IICx: IIC_Typedef structure
  * @retval None
  * @note   当SCL为高电平时，SDA上升沿触发停止信号
  */
void IIC_GenerateSTOP(IIC_TypeDef* IICx)
{
    IIC_SDA_Set(IICx, IIC_SDA_Mode_Out);

    GPIO_ResetBits(IICx->SCL_Port, IICx->SCL_Pin);  //拉低SCL
    GPIO_ResetBits(IICx->SDA_Port, IICx->SDA_Pin);  //拉低SDA
    delay_us(1);//

    GPIO_SetBits(IICx->SCL_Port, IICx->SCL_Pin);    //拉高SCL
    GPIO_SetBits(IICx->SDA_Port, IICx->SDA_Pin);    //产生上升沿
    delay_us(1);//

    GPIO_ResetBits(IICx->SCL_Port, IICx->SCL_Pin);  //拉低CLK，保证状态稳定
}


/**
  * @brief  Sends a data byte through the IICx.
  * @param  IICx: IIC_Typedef structure
  * @param  data: Byte to be transmitted..
  * @retval None
  */
void IIC_SendData(IIC_TypeDef* IICx, uint8_t data)
{                        
    uint8_t i;

    IIC_SDA_Set(IICx, IIC_SDA_Mode_Out);
    GPIO_ResetBits(IICx->SCL_Port, IICx->SCL_Pin);

    for(i = 0; i < 8; i++)
    {
        GPIO_WriteBit(IICx->SDA_Port, IICx->SDA_Pin,
            (BitAction) (data>>(7-i) & 0x01));  //从最高位依次发送数据
//      delay_us(2);
        // 时钟脉冲
        GPIO_SetBits(IICx->SCL_Port, IICx->SCL_Pin);
        delay_us(1);//
        GPIO_ResetBits(IICx->SCL_Port, IICx->SCL_Pin);
        delay_us(1);//
    }
}


/**
  * @brief  Returns the most recent received data by the IICx, followed by an ACK/NACK. 
  * @param  IICx: IIC_Typedef structure
  *         ACK_State: ACK | NACK
  * @retval 0~255
  */
uint8_t IIC_ReceiveData(IIC_TypeDef* IICx, BitAction ACK_State)
{
	uint8_t i, data=0;

    IIC_SDA_Set(IICx, IIC_SDA_Mode_IN);
//    delay_us(30);
    for(i = 0; i < 8; i++)
	{
        //时钟脉冲
        GPIO_ResetBits(IICx->SCL_Port, IICx->SCL_Pin);
        delay_us(1);//
        GPIO_SetBits(IICx->SCL_Port, IICx->SCL_Pin);

        data <<= 1;
        if(GPIO_ReadInputDataBit(IICx->SDA_Port, IICx->SDA_Pin))
            data++;
		delay_us(1);//
    }

    IIC_Response(IICx, ACK_State);
    return data;
}


/**
  * @brief  Read a byte via IICx
  * @param  IICx: IIC_Typedef structure 
  * @param  slaveAddr: 8 bit device address
  * @param  regAddr: word address
  * @retval uint8_t data
  */
uint8_t IIC_Read(IIC_TypeDef* IICx ,uint8_t slaveAddr, uint8_t regAddr)
{
    uint8_t temp = 0;

    IIC_GenerateSTART(IICx);

    /* 发送从设备地址+写命令 */
    IIC_SendData(IICx, slaveAddr&0xFE);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    /* 写寄存器地址 */
    IIC_SendData(IICx, regAddr);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    IIC_GenerateSTART(IICx);
    /* 发送从设备地址+读命令 */
    IIC_SendData(IICx, slaveAddr|0x01);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    /* 接收数据 */
    temp = IIC_ReceiveData(IICx, NACK);

    IIC_GenerateSTOP(IICx);
    return temp;

timeout:
    IIC_GenerateSTOP(IICx);
    printf("IIC Read timeout!\r\n");
    return ERROR;
}


/**
  * @brief  write a byte via IICx
  * @param  IICx: IIC_Typedef structure 
  *         slaveAddr: 8 bit device address
  *         regAddr: word address
  *         data: 数据
  * @retval 0:成功 | 1: 失败
  */
uint8_t IIC_Write(IIC_TypeDef* IICx ,uint8_t slaveAddr, uint8_t regAddr, uint8_t data)
{
    IIC_GenerateSTART(IICx);

    /* 发送从设备地址+写命令*/
    IIC_SendData(IICx, slaveAddr&0xFE);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    /* 写寄存器地址 */
    IIC_SendData(IICx, regAddr);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    /* 发送数据 */
    IIC_SendData(IICx, data);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    IIC_GenerateSTOP(IICx);
    return SUCCESS;

timeout:
    IIC_GenerateSTOP(IICx);
    printf("IIC Write timeout!\r\n");
    return ERROR;
}

/**
  * @brief  Random Read len bytes via IICx
  * @param  IICx: IIC_Typedef structure
  * @param  slaveAddr: 8 bit device address
  * @param  regAddr: word address
  * @param  data: array that stores data to be read
  * @param  len: number of bytes
  * @retval 0: success | 1: fail
  */
uint8_t IIC_ReadBytes(IIC_TypeDef* IICx, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint8_t len)
{
    IIC_GenerateSTART(IICx);

    IIC_SendData(IICx, slaveAddr&0xFE);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    IIC_SendData(IICx, regAddr);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    IIC_GenerateSTART(IICx);
    IIC_SendData(IICx, slaveAddr|0x01);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;
            
    while(--len)
    {
        *data++ = IIC_ReceiveData(IICx, ACK);
    }
    *data = IIC_ReceiveData(IICx, NACK);

    IIC_GenerateSTOP(IICx);
    return SUCCESS;
    
timeout:
    IIC_GenerateSTOP(IICx);
    printf("IIC Read Sequential Data Timeout!\r\n");
    return ERROR;
}


/**
  * @brief  write len bytes via IICx
  * @param  IICx: IIC_Typedef structure
  *         slaveAddr: 从设备地址
  *         regAddr: 数据在从设备中存放的地址
  *         data: 数据在主设备中存放的地址
  *         len: 字节长度
  * @retval 0: 正常 | others: 异常
  */
uint8_t IIC_WriteBytes(IIC_TypeDef* IICx, uint8_t slaveAddr, uint8_t regAddr, uint8_t *data, uint8_t len)
{
    IIC_GenerateSTART(IICx);

    /* 发送从设备地址+写命令*/
    IIC_SendData(IICx, slaveAddr&0xFE);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    /* 写寄存器地址 */
    IIC_SendData(IICx, regAddr);
    if(IIC_Wait_ACK(IICx)!=SUCCESS)
        goto timeout;

    /* 发送数据 */
    while(len--)
    {
        IIC_SendData(IICx, *data++);
        if(IIC_Wait_ACK(IICx)!=SUCCESS)
            goto timeout;
    }

    IIC_GenerateSTOP(IICx);
    delay_ms(10);
    return SUCCESS;

timeout:
    IIC_GenerateSTOP(IICx);
    printf("IIC Page Write Timeout!\r\n");
    return ERROR;
}
/******************************** END OF FILE *********************************/
