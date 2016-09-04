#include "usart1.h"

void USART1_NVIC_Config(void);
void _ttywrch(int ch);

void USART1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);

	/* USART1 GPIO config */
	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1, ENABLE);

	USART_ClearFlag(USART1,USART_IT_RXNE);
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

	USART_Cmd(USART1, ENABLE);
}

void USART1_NVIC_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


 void USART1_IRQHandler (void)
 {
	static unsigned char totalByteCNT=0,stopByteCNT=0 ,ackByteCNT=0;	//接受到的总字节数，接受到的停止字节个数

 	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)!=RESET)
 	{
		USART_ClearFlag(USART1,USART_IT_RXNE);
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
 }

int fputc(int ch, FILE *f)
{

	USART_SendData(USART1, (unsigned char) ch);
	while (!(USART1->SR & USART_FLAG_TXE));
//	while( USART_GetFlagStatus(USART1,USART_FLAG_TC)!= SET);
	return (ch);
}


char *itoa(int value, char *string, int radix)
{
	int     i, d;
	int     flag = 0;
	char    *ptr = string;

	/* This implementation only works for decimal numbers. */
	if (radix != 10)
	{
	    *ptr = 0;
	    return string;
	}

	if (!value)
	{
	    *ptr++ = 0x30;
	    *ptr = 0;
	    return string;
	}

	/* if this is a negative value insert the minus sign. */
	if (value < 0)
	{
	    *ptr++ = '-';

	    /* Make the value positive. */
	    value *= -1;
	}
	for (unsigned int i = 1000000000; i>0 ; i /= 10)
	{
	    d = value / i;

	    if (d || flag)
	    {
	        *ptr++ = (char)(d + 0x30);
	        value -= (d * i);
	        flag = 1;
	    }
	}

	/* Null terminate the string. */
	*ptr = 0;

	return string;

} /* NCL_Itoa */


/* Retargeting functions for gcc-arm-embedded */

int _write (int fd, char *ptr, int len)
{
  /* Write "len" of char from "ptr" to file id "fd"
   * Return number of char written.
   * Need implementing with UART here. */
  int i;
  for (i = 0; i < len; ++i)
  {
    _ttywrch(ptr[i]);
  }
  return len;
}

int _read (int fd, char *ptr, int len)
{
  /* Read "len" of char to "ptr" from file id "fd"
   * Return number of char read.
   * Need implementing with UART here. */
  return len;
}

void _ttywrch(int ch) {
  /* Write one char "ch" to the default console
   * Need implementing with UART here. */
  fputc(ch, NULL);
}

void myPrintf(uint8_t *Data,...)
{
	const char *s;
	int d;
	char buf[50];

	va_list ap;
	va_start(ap, Data);

	while ( *Data != 0)     // 判断是否到达字符串结束符
	{
		if ( *Data == 0x5c )  //'\'
	{
	switch ( *++Data )
	{
		case 'r':							          //回车符
			USART_SendData(USART1, 0x0d);
			Data ++;
		break;

		case 'n':							          //换行符
			USART_SendData(USART1, 0x0a);
			Data ++;
		break;

		default:
			Data ++;
		break;
	}
	}
	else if ( *Data == '%')
	{									  //
	switch ( *++Data )
	{
		case 's':										  //字符串
			s = va_arg(ap, const char *);
	for ( ; *s; s++)
	{
		USART_SendData(USART1,*s);
		while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
	}
		Data++;
		break;

	case 'd':										//十进制
	d = va_arg(ap, int);
	itoa(d, buf, 10);
	for (s = buf; *s; s++)
	{
		USART_SendData(USART1,*s);
		while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
	}
	Data++;
	break;
		 default:
				Data++;
		    break;
	}
	} /* end of else if */
	else USART_SendData(USART1, *Data++);
	while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
	}
}

void USART1_SendBytes(u8 *p, int length)
{
	for(int i=0;i<length;i++)
	{
		USART_SendData(USART1, *p++);
		while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
	}
}
