#ifndef _RECEIVER_H
#define _RECEIVER_H

#include "stm32f10x.h"

#define TIMCaptureState_RESET    0x00
#define TIMCaptureState_SET     0x01
#define TIMCaptureState_OVERFLOW 0x02

#define TIMCapture_PERIOD                  50000   //us
#define IsTIMCaptureValueValid(VAL)              ((VAL<2000) && (VAL>1000))

void RECEIVER_Init(void);
u16 getReceiveChannelsValue(int ch);

extern const volatile u16 *receiverValues; //receiver channel values array, and the index range is 1~6

#endif
