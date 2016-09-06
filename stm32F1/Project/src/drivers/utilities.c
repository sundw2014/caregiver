#include "stm32f10x.h"
#include "utilities.h"
#include "tim.h"
#include "delay.h"

static void Motor_GPIO_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void setMotorSpeed(enum Motor m, int speed)
{
  switch(m)
  {
    case motor1:{
      if(speed > 0){
        GPIO_SetBits(GPIOB,GPIO_Pin_13);
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);
        TIM_SetCompare1(TIM5, speed);
      }
      else{
        GPIO_ResetBits(GPIOB,GPIO_Pin_13);
        GPIO_SetBits(GPIOB,GPIO_Pin_12);
        TIM_SetCompare1(TIM5, -speed);
      }
      break;
    }

    case motor2:{
      if(speed > 0){
        GPIO_SetBits(GPIOC,GPIO_Pin_2);
        GPIO_ResetBits(GPIOC,GPIO_Pin_3);
        TIM_SetCompare2(TIM5, speed);
      }
      else{
        GPIO_ResetBits(GPIOC,GPIO_Pin_2);
        GPIO_SetBits(GPIOC,GPIO_Pin_3);
        TIM_SetCompare2(TIM5, -speed);
      }
      break;
    }

    case motor3:{
      if(speed > 0){
        GPIO_SetBits(GPIOC,GPIO_Pin_5);
        GPIO_ResetBits(GPIOC,GPIO_Pin_4);
        TIM_SetCompare3(TIM5, speed);
      }
      else{
        GPIO_ResetBits(GPIOC,GPIO_Pin_5);
        GPIO_SetBits(GPIOC,GPIO_Pin_4);
        TIM_SetCompare3(TIM5, -speed);
      }
      break;
    }

    case motor4:{
      if(speed > 0){
        GPIO_SetBits(GPIOA,GPIO_Pin_4);
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);
        TIM_SetCompare4(TIM5, speed);
      }
      else{
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
        TIM_SetCompare4(TIM5, -speed);
      }
      break;
    }

    default:{
      break;
    }
  }
}

void setServoAngle(enum Servo s, float angle)
{
  if(angle < -90.0){
    angle = -90.0;
  }
  if(angle > 90.0){
    angle = 90.0;
  }

  int width = (int)(angle/90.0*500.0 + 1500);

  switch(s)
  {
    case servo1:{
      TIM_SetCompare1(TIM3,width);
      break;
    }
    case servo2:{
      TIM_SetCompare2(TIM3,width);
      break;
    }
    case servo3:{
      TIM_SetCompare3(TIM3,width);
      break;
    }
    case servo4:{
      TIM_SetCompare4(TIM3,width);
      break;
    }
  }
}

void Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           //中断优先级分组为2 note:2 bits for pre-emption priority, 2 bits for subpriority

    DelayInit();   //SysTick init
    // DelayS(1);

    USART1_Init(); //user serial port
    USART3_Init(); //bluetooth

    Motor_GPIO_Init(); //Motor GPIO

    TIM1_Init(); //Receiver channel 5,6
    TIM5_PWM_Init(); //Motor PWM
    TIM3_PWM_Init(); //Servo PWM
    TIM4_Init(); //Receiver channel 1,2,3,4
}
