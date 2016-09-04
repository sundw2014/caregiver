#ifndef __MY_USART1_H_
#define __MY_USART1_H_

#include <stdarg.h>
#include <stdio.h>
#include "stm32f10x.h"
#include <stdlib.h>

int fputc(int ch, FILE *f);
void USART1_NVIC_Config(void);
void USART1_Init();
void myPrintf(uint8_t *Data,...);
void USART1_SendBytes(u8 *p, int length);

#endif
