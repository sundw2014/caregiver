#ifndef __PACK_H_
#define __PACK_H_

#include <stdint.h>

typedef int16_t s16;
typedef uint16_t u16;
typedef uint8_t u8;
typedef uint32_t u32;

#define MAGIC_NUMBER0 0x88
#define MAGIC_NUMBER1 0xAF
#define MAGIC_NUMBER2 0x1C
#define MAGIC_NUMBER3 0xCC

#pragma pack(4)
typedef struct _PACK
{
  u8  magic[4];
  s16 frontAccelTemGyroData[4];
  u16 cntVal[2];
  u32 packNo;
  s16 speed[2];
} Pack;

#endif
