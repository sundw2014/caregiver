#ifndef __DELAY_H_
#define __DELAY_H_

#include "stm32f10x.h"

void DelayInit(void);
void delayMicroseconds(u32);
void DelayUs(unsigned int us);
void DelayMs(unsigned int ms);
void DelayS(unsigned int s);

#endif
