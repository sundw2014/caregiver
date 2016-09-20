#ifndef __MY_USART1_H_
#define __MY_USART1_H_

// #define USE_USART1 //串口1和接收机的5、6通道使用了相同的IO口（PA9/PA10），两个功能只能使用一个，如果使用串口1则保留这个define否则注释掉

#include <stdarg.h>
#include <stdlib.h>
// #include <stdio.h>
#include "stm32f10x.h"

// int fputc(int ch, FILE *f);
#ifdef USE_USART1
  void USART1_Init(void);
#endif

void USART3_Init(void); //bluetooth usart
void myPrintf(USART_TypeDef* USARTx, uint8_t *Data,...);//lite printf function, support format:%d,%c,%s,\r,\n
void USART_SendBytes(u8 *p, int length, USART_TypeDef* USARTx);

#endif
