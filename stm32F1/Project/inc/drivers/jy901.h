#ifndef __JY901_H_
#define __JY901_H_

#include "stm32f10x.h"

#define JY901_DA_FRONT          0xA0
#define JY901_DA_REAR           0xA2

#define JY901_RA_ACCEL_XOUT     0x34
#define JY901_RA_ACCEL_YOUT     0x35
#define JY901_RA_ACCEL_ZOUT     0x36
#define JY901_RA_GYRO_XOUT      0x37
#define JY901_RA_GYRO_YOUT      0x38
#define JY901_RA_GYRO_ZOUT      0x39
#define JY901_RA_MAG_XOUT       0x3A
#define JY901_RA_MAG_YOUT       0x3B
#define JY901_RA_MAG_ZOUT       0x3C

#define JY901_RA_ANGEL_ZOUT     0x3F

extern u8 JY901Initinig;

void JY901_I2C_ByteWrite(u8 slaveAddr, u8* pBuffer, u8 writeAddr, u16 NumByteToWrite);
void JY901_I2C_ByteRead(u8 slaveAddr, u8* pBuffer, u8 readAddr, u16 NumByteToRead);
void JY901_GetData(s16 *jy901FrontData, s16 *jy901RearData);
void JY901_Init(u8 front, u8 rear);

#endif
