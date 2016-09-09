#include "motor.h"

/*begin of TIM5*/
static void MOTOR_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    //PWM pins
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);



    //direction pins
        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_12 | GPIO_Pin_13;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
}

static void MOTOR_TIM_Config(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    u16 CCR1_Val = 0;
    u16 CCR2_Val = 0;
    u16 CCR3_Val = 0;
    u16 CCR4_Val = 0;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = MOTOR_TIM_PERIOD - 1;       //14kHz
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM5, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

    TIM_OC2Init(TIM5, &TIM_OCInitStructure);

    TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

    TIM_OC3Init(TIM5, &TIM_OCInitStructure);

    TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel4 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

    TIM_OC4Init(TIM5, &TIM_OCInitStructure);

    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM5, ENABLE);

    /* TIM5 enable counter */
    TIM_Cmd(TIM5, ENABLE);
}

void MOTOR_Init(void)
{
    MOTOR_GPIO_Config();
    MOTOR_TIM_Config();
}
/*end of TIM5*/

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
