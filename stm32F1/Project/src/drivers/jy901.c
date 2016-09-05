#include "stm32f10x.h"
#include "i2c.h"
#include "jy901.h"
#include "usart.h"

static s16 JY901_MAX_MAG_FRONT[3] = {-0x7FFF, -0x7FFF, -0x7FFF};
static s16 JY901_MIN_MAG_FRONT[3] = {0x7FFF, 0x7FFF, 0x7FFF};

static s16 JY901_MAX_MAG_REAR[3] = {-0x7FFF, -0x7FFF, -0x7FFF};
static s16 JY901_MIN_MAG_REAR[3] = {0x7FFF, 0x7FFF, 0x7FFF};

u8 JY901Initinig=0;

void JY901_I2C_ByteWrite(u8 slaveAddr, u8* pBuffer, u8 writeAddr, u16 NumByteToWrite)
{
  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);          //发送开始信号
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send JY901 address for write */
  I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter);          // 发送 JY901 地址、状态（写）
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the JY901's reg address to write to */
  I2C_SendData(I2C1, writeAddr);                   //发送 JY901内部某个待写寄存器地址
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send the bytes to be written */
  while(NumByteToWrite)
  {
    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
    {
      /* Read a byte from the JY901 */
      I2C_SendData(I2C1, *pBuffer);

      /* Point to the next location where the byte read will be saved */
      pBuffer++;

      /* Decrement the read bytes counter */
      NumByteToWrite--;
    }
  }
  /* Send STOP condition */
  I2C_GenerateSTOP(I2C1, ENABLE);          //发送结束信号
}

void JY901_I2C_BufferRead(u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead)
{
  /* While the bus is busy */
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send JY901 address for write */
  I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter);
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2C1, ENABLE);
  /* Send the JY901's internal address to write to */
  I2C_SendData(I2C1, readAddr);
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STRAT condition a second time */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send JY901 address for read */
  I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Receiver);
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  /* While there is data to be read */
  while(NumByteToRead)
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(I2C1, DISABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      /* Read a byte from the JY901 */
      *pBuffer = I2C_ReceiveData(I2C1);

      /* Point to the next location where the byte read will be saved */
      pBuffer++;

      /* Decrement the read bytes counter */
      NumByteToRead--;
    }
  }
  /* Send STOP Condition */
  I2C_GenerateSTOP(I2C1, ENABLE);

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C1, ENABLE);
}

void JY901_GetData(s16 *jy901FrontData, s16 *jy901RearData)
{

     if(jy901FrontData != NULL)
     {
       JY901_I2C_BufferRead(JY901_DA_FRONT, (u8 *)jy901FrontData, JY901_RA_GYRO_XOUT, 3 * sizeof(s16));
     }
     if(jy901RearData != NULL)
     {
       JY901_I2C_BufferRead(JY901_DA_REAR, (u8 *)jy901RearData, JY901_RA_GYRO_XOUT, 3 * sizeof(s16));
     }
}

void JY901_Init(u8 front, u8 rear)
{
  while(1)
  {
    if(JY901Initinig)
    {
        s16 jy901TempDataFront[3], jy901TempDataRear[3];
        if(front)
          JY901_I2C_BufferRead(JY901_DA_FRONT, (u8 *)jy901TempDataFront, JY901_RA_MAG_XOUT, 3 * sizeof(s16));
        if(rear)
          JY901_I2C_BufferRead(JY901_DA_REAR, (u8 *)jy901TempDataRear, JY901_RA_MAG_XOUT, 3 * sizeof(s16));

        if(front)
        {
          for(u8 i=0;i<3;i++)
          {
            if(JY901_MAX_MAG_FRONT[i] < jy901TempDataFront[i])
              JY901_MAX_MAG_FRONT[i] = jy901TempDataFront[i];
            if(JY901_MIN_MAG_FRONT[i] > jy901TempDataFront[i])
              JY901_MIN_MAG_FRONT[i] = jy901TempDataFront[i];
          }
        }
       if(rear)
       {
         for(u8 i=0;i<3;i++)
         {
           if(JY901_MAX_MAG_REAR[i] < jy901TempDataRear[i])
             JY901_MAX_MAG_REAR[i] = jy901TempDataRear[i];
           if(JY901_MIN_MAG_REAR[i] > jy901TempDataRear[i])
             JY901_MIN_MAG_REAR[i] = jy901TempDataRear[i];
         }
      }
    }
    else
    {
       break;
    }
  }
}
