#include "stm32f10x.h"
#include "i2c.h"
#include "mpu6050.h"
#include "usart.h"

// 0xD0 表示 MPU6050 的地址。I2C从器件（在此当然是指 MPU6050）有 8 位的地址，前 7 位由 WHO AM I 确定，第 8 位由 AD0 的电平决定。
//WHO AM I 默认值是 0x68H（1101000B），AD0 接低电平，所以 MPU6050 的 I2C 地址是 0xD0H（11010000B）。

// 发送开始信号 -> 起始成功?（可能描述的不太准确） -> 发送 MPU6050 地址、状态（写）-> 写地址成功? -> 发送 MPU6050内部某个待写寄存器地址 -> 发送成功? -> 发送要写入的内容 -> 发送成功？ -> 发送结束信号
// 总结：先写 MPU6050 地址，再写 寄存器地址，最后写 内容，且每次都要验证（应该和应答信号有关）。这就像寄快递一样，先写市县地址，再写街道地址，最后写门牌号。

void MPU6050_I2C_ByteWrite(u8 slaveAddr, u8 pBuffer, u8 writeAddr)
{
  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);          //发送开始信号
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send MPU6050 address for write */
  I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter);          // 发送 MPU6050 地址、状态（写）
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the MPU6050's reg address to write to */
  I2C_SendData(I2C1, writeAddr);                   //发送 MPU6050内部某个待写寄存器地址
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send the byte to be written */
  I2C_SendData(I2C1, pBuffer);                     //发送要写入的内容
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STOP condition */
  I2C_GenerateSTOP(I2C1, ENABLE);          //发送结束信号
}

void MPU6050_I2C_BufferRead(u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead)
{
  /* While the bus is busy */
  while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

  /* Send START condition */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send MPU6050 address for write */
  I2C_Send7bitAddress(I2C1, slaveAddr, I2C_Direction_Transmitter);
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2C1, ENABLE);
  /* Send the MPU6050's internal address to write to */
  I2C_SendData(I2C1, readAddr);
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

/* Send STRAT condition a second time */
  I2C_GenerateSTART(I2C1, ENABLE);
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send MPU6050 address for read */
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

      /* Send STOP Condition */
      I2C_GenerateSTOP(I2C1, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      /* Read a byte from the MPU6050 */
      *pBuffer = I2C_ReceiveData(I2C1);

      /* Point to the next location where the byte read will be saved */
      pBuffer++;

      /* Decrement the read bytes counter */
      NumByteToRead--;
    }
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C1, ENABLE);
}

void MPU6050_Initialize()             //初始化过程 ，其实就是写 5个寄存器
{

  MPU6050_I2C_ByteWrite(MPU6050_DA_FRONT,0x00,MPU6050_RA_PWR_MGMT_1);      // reg107, 唤醒，8M内部时钟源
  // myPrintf("test4\r\n");
  MPU6050_I2C_ByteWrite(MPU6050_DA_FRONT,0x07,MPU6050_RA_SMPLRT_DIV);         //采用频率 1000
  MPU6050_I2C_ByteWrite(MPU6050_DA_FRONT,0x06,MPU6050_RA_CONFIG);
  MPU6050_I2C_ByteWrite(MPU6050_DA_FRONT,0x01,MPU6050_RA_ACCEL_CONFIG);     //加速度量程 2g
  MPU6050_I2C_ByteWrite(MPU6050_DA_FRONT,0x18,MPU6050_RA_GYRO_CONFIG);          //角速度量程 2000度/s

  MPU6050_I2C_ByteWrite(MPU6050_DA_REAR,0x00,MPU6050_RA_PWR_MGMT_1);      // reg107, 唤醒，8M内部时钟源
  MPU6050_I2C_ByteWrite(MPU6050_DA_REAR,0x07,MPU6050_RA_SMPLRT_DIV);         //采用频率 1000
  MPU6050_I2C_ByteWrite(MPU6050_DA_REAR,0x06,MPU6050_RA_CONFIG);
  MPU6050_I2C_ByteWrite(MPU6050_DA_REAR,0x01,MPU6050_RA_ACCEL_CONFIG);     //加速度量程 2g
  MPU6050_I2C_ByteWrite(MPU6050_DA_REAR,0x18,MPU6050_RA_GYRO_CONFIG);          //角速度量程 2000度/s
}

void MPU6050_GetRawAccelGyro(s16 *mpu6050FrontAccelTemGyro, s16 *mpu6050RearAccelTemGyro )        //读加速度值 和 角速度值
{
		 u8 tmpBuffer[14],i;
		 if(mpu6050FrontAccelTemGyro != NULL)
		 {
			 MPU6050_I2C_BufferRead(MPU6050_DA_FRONT, tmpBuffer, MPU6050_RA_ACCEL_XOUT_H, 14);
		 	 /* Get acceleration, temperature, gyro data*/
		 	 for(i=0; i<7; i++)
		   mpu6050FrontAccelTemGyro[i]=((s16)((u16)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]);
		 }

		 if(mpu6050RearAccelTemGyro != NULL)
		 {
			 MPU6050_I2C_BufferRead(MPU6050_DA_REAR, tmpBuffer, MPU6050_RA_ACCEL_XOUT_H, 14);
		   /* Get acceleration, temperature, gyro data*/
			 for(i=0; i<7; i++)
		 	 mpu6050RearAccelTemGyro[i]=((s16)((u16)tmpBuffer[2*i] << 8) + tmpBuffer[2*i+1]);
		 }
}

void MPU6050_GetRawAccelGyroAverage(s16 *mpu6050FrontAccelTemGyroAverage, s16 *mpu6050RearAccelTemGyroAverage )        //读加速度值 和 角速度值
{
     s16 *tempFront = NULL, *tempRear = NULL;
     s16 tempFrontAvr[7], tempRearAvr[7];
     if(mpu6050FrontAccelTemGyroAverage != NULL)
      tempFront = (s16 *) malloc (4 * 7 * sizeof(s16));
     if(mpu6050RearAccelTemGyroAverage != NULL)
      tempRear = (s16 *) malloc (4 * 7 * sizeof(s16));

     s16 *tF = tempFront, *tR = tempRear;
     for(u8 i=0;i<4;i++)
     {
       MPU6050_GetRawAccelGyro(tF,tR);

       //myPrintf("MPU6050_FRONT______%d: acceleration = [%d , %d ,%d] temperature=%d Gyro = [%d , %d ,%d]\r\n", i,\
 		    tF[0], tF[1], tF[2], tF[3],\
 		     tF[4], tF[5], tF[6]);

       if(tempFront != NULL) tF += 7;
       if(tempRear != NULL)  tR += 7;
     }
     for(u8 i=0;i<7;i++)
     {
       tempFrontAvr[i] = (tempFront[i] + tempFront[i+7] + tempFront[i+14] + tempFront[i+21]) >> 2;

       tempRearAvr[i] = (tempRear[i] += tempRear[i+7] + tempRear[i+14] + tempRear[i+21]) >> 2;
     }

     //myPrintf("MPU6050_FRONT: acceleration = [%d , %d ,%d] temperature=%d Gyro = [%d , %d ,%d]\r\n" ,\
 		 tempFrontAvr[0], tempFrontAvr[1], tempFrontAvr[2], tempFrontAvr[3],\
 		  tempFrontAvr[4], tempFrontAvr[5], tempFrontAvr[6]);

     if(mpu6050FrontAccelTemGyroAverage != NULL)
     {
        memcpy(mpu6050FrontAccelTemGyroAverage, tempFrontAvr, 7 * sizeof(s16));
        free(tempFront);
      }
     if(mpu6050RearAccelTemGyroAverage != NULL)
     {
        memcpy(mpu6050RearAccelTemGyroAverage, tempRearAvr, 7 * sizeof(s16));
        free(tempRear);
     }
}
