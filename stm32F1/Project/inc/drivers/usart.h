#ifndef __MY_USART1_H_
#define __MY_USART1_H_

#include <stdarg.h>
// #include <stdio.h>
#include "stm32f10x.h"
#include <stdlib.h>

// int fputc(int ch, FILE *f);
void USART1_Init(void);
void USART3_Init(void);
void myPrintf(uint8_t *Data,...);
void USART_SendBytes(u8 *p, int length, USART_TypeDef* USARTx);

#endif
