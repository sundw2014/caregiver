#include "servo.h"

/*begin of TIM3*/
static void SERVO_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void SERVO_TIM_Config(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    u16 CCR1_Val = 1500;
    u16 CCR2_Val = 1500;
    u16 CCR3_Val = 1500;
    u16 CCR4_Val = 1500;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = SERVO_TIM_PERIOD - 1;
    TIM_TimeBaseStructure.TIM_Prescaler = SERVO_TIM_PRESCALER - 1;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    // /*中断分组初始化*/
    // NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    /*TIM1中断*/
    // NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; /*先占优先级0级*/
    // NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; /*从优先级0级*/
    // NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /*IRQ通道被使能*/
    // NVIC_Init(&NVIC_InitStructure);
    //
    // TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);/*允许更新中断*/
    // TIM_Cmd(TIM3,ENABLE); /*使能定时器1*/

    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR3_Val;

    TIM_OC3Init(TIM3, &TIM_OCInitStructure);

    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

    /* PWM1 Mode configuration: Channel4 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR4_Val;

    TIM_OC4Init(TIM3, &TIM_OCInitStructure);

    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM3, ENABLE);

    /* TIM3 enable counter */
    TIM_Cmd(TIM3, ENABLE);
}

// void TIM3_IRQHandler()
// {
//   if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET) {
//       static int servo_cnt=0;
//       static int servo_previous_campare[4];
//       TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
//       if(servo_cnt==0)
//       {
//
//       }
//       else(servo_cnt==)
//       servo_cnt++;
//   }
// }
void SERVO_Init(void)
{
    SERVO_GPIO_Config();
    SERVO_TIM_Config();
}
/*end of TIM3*/

void setServoAngle(enum Servo s, float angle)
{
    if(angle < -90.0) {
        angle = -90.0;
    }
    if(angle > 90.0) {
        angle = 90.0;
    }

    int width = (int)(angle/90.0*500.0 + 1500.0);

    switch(s)
    {
    case servo1: {
        TIM_SetCompare1(TIM3,width);
        break;
    }
    case servo2: {
        TIM_SetCompare2(TIM3,width);
        break;
    }
    case servo3: {
        TIM_SetCompare3(TIM3,width);
        break;
    }
    case servo4: {
        TIM_SetCompare4(TIM3,width);
        break;
    }
    }
}
