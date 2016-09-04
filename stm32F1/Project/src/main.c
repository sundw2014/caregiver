#include <stdlib.h>
#include "stm32f10x.h"
#include "usart1.h"
#include "tim.h"
#include "utilities.h"

void main()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           //中断优先级分组为2 note:2 bits for pre-emption priority, 2 bits for subpriority
	DelayInit();
	DelayS(1);
	USART1_Init();

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
	//myPrintf("sizeof(Pack)=%d\r\n",sizeof(Pack));
	// s16 *frontAccelTemGyroData = (s16 *) malloc (7 * sizeof(s16));
  // s16 *rearAccelTemGyroData = (s16 *) malloc (7 * sizeof(s16));
	GPIO_SetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);

	GPIO_SetBits(GPIOC,GPIO_Pin_2);
	GPIO_ResetBits(GPIOC,GPIO_Pin_3);

	GPIO_SetBits(GPIOC,GPIO_Pin_5);
	GPIO_ResetBits(GPIOC,GPIO_Pin_4);

	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
	//TIM1_Init();
	while(1)
	{
			// if(TIM3_CC3_CAPTURE_VAL_AVA)
			// {
			// 	TIM3_CC3_CAPTURE_VAL_AVA = 0;
			//   myPrintf("%d\r\n",TIM3_CC3_CAPTURE_VAL);
			// }
		//MPU6050_GetRawAccelGyroAverage(frontAccelTemGyroData,NULL);
		//myPrintf("MPU6050_FRONT: acceleration = [%d , %d ,%d] temperature=%d Gyro = [%d , %d ,%d]\r\n" ,\
		 frontAccelTemGyroData[0], frontAccelTemGyroData[1], frontAccelTemGyroData[2], frontAccelTemGyroData[3],\
		  frontAccelTemGyroData[4], frontAccelTemGyroData[5], frontAccelTemGyroData[6]);
    // myPrintf("MPU6050_REAR: acceleration = [%d , %d ,%d] temperature=%d Gyro = [%d , %d ,%d]\r\n" ,\
		 rearAccelTemGyroData[0], rearAccelTemGyroData[1], rearAccelTemGyroData[2], rearAccelTemGyroData[3],\
			rearAccelTemGyroData[4], rearAccelTemGyroData[5], rearAccelTemGyroData[6]);
	}
}
