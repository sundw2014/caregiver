#include "usart.h"
#include "utilities.h"

static void USART1_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART1_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* config USART1 clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

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
    USART_InitStructure.USART_BaudRate = 115200;
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

void USART1_IRQHandler (void)
{
    if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)!=RESET) {
//		BluetoothReceiveInterruput(USART_GetData(USART3));
        USART_ClearFlag(USART1,USART_IT_RXNE);
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}



static void USART3_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART3_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3 , ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);

    /* USART3 GPIO config */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* USART1 mode config */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
    USART_Cmd(USART3, ENABLE);

    USART_ClearFlag(USART3,USART_IT_RXNE);
    USART_ClearITPendingBit(USART3,USART_IT_RXNE);
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);

    USART_Cmd(USART3, ENABLE);
}

void USART3_IRQHandler (void)
{
    if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE)!=RESET) {
        BluetoothReceiveInterruput(USART_ReceiveData(USART3));
        USART_ClearFlag(USART3,USART_IT_RXNE);
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);
    }
}

char* itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10) {
        *ptr = 0;
        return string;
    }

    if (!value) {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0) {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }
    for (unsigned int i = 1000000000; i>0 ; i /= 10) {
        d = value / i;

        if (d || flag) {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

void myPrintf(uint8_t *Data,...)
{
    const char *s;
    int d;
    char buf[50];

    va_list ap;
    va_start(ap, Data);

    while ( *Data != 0) {   // 判断是否到达字符串结束符
        if ( *Data == 0x5c ) { //'\'
            switch ( *++Data ) {
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
        } else if ( *Data == '%') {
            //
            switch ( *++Data ) {
            case 's':										  //字符串
                s = va_arg(ap, const char *);
                for ( ; *s; s++) {
                    USART_SendData(USART1,*s);
                    while( USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET );
                }
                Data++;
                break;

            case 'd':										//十进制
                d = va_arg(ap, int);
                itoa(d, buf, 10);
                for (s = buf; *s; s++) {
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

void USART_SendBytes(u8 *p, int length, USART_TypeDef* USARTx)
{
    for(int i=0; i<length; i++) {
        USART_SendData(USARTx, *p++);
        while( USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET );
    }
}
