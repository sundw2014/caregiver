#include <stdlib.h>
#include "stm32f10x.h"
#include "usart.h"
#include "utilities.h"

void main()
{

	//myPrintf("test1\r\n");
	// for(int i=0;i<1;i++)
	// 	delayMicroseconds(1864135);
	// myPrintf("test2\r\n");
	//
	// while(1);
	// while(1)
	// 	myPrintf("fuck!!!\r\n");

	//TIM3_Init();
	// TIM4_Init();

	//I2C1_Init();
	// JY901_Init(1,0);
	// myPrintf("test3\r\n");
	//MPU6050_Initialize();

	//SPI1_Init();
	//SPI_A9800_PowerUp();
	Init();
	myPrintf("Init OK\r\n");

	while(1)
	{
		myPrintf("ch1=%d, ch2=%d, ch3=%d, ch4=%d. ch5=%d, ch6=%d\r\n", receiverValues[1], receiverValues[2], receiverValues[3],
			receiverValues[4], receiverValues[5], receiverValues[6]);
	}
}
