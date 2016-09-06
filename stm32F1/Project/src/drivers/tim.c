#include "stm32f10x.h"
#include "tim.h"

volatile u16 TIMCaptureValue[7] = {0}; //捕获到的值
//volatile u8 TIMCaptureValueValid[6] = {0}; //捕获是否有效
volatile u8 TIMCaptureState[7] = {TIMCaptureState_RESET};  //捕获状态
volatile u8 TIMCapturePreviousCounter[7] = {0}; //上升沿时的计数器值

/*begin of TIM5*/
static void TIM5_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

static void TIM5_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    u16 CCR1_Val = 0;
    u16 CCR2_Val = 0;
    u16 CCR3_Val = 0;
    u16 CCR4_Val = 0;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = MOTOR_PWM_PERIOD - 1;       //14kHz
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

void TIM5_PWM_Init(void)
{
    TIM5_GPIO_Config();
    TIM5_Mode_Config();
}
/*end of TIM5*/



/*begin of TIM3*/
static void TIM3_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void TIM3_Mode_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;

    u16 CCR1_Val = 1500;
    u16 CCR2_Val = 1500;
    u16 CCR3_Val = 1500;
    u16 CCR4_Val = 1500;

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Period = MOTOR_PWM_PERIOD - 1;       //14kHz
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

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

void TIM3_PWM_Init(void)
{
    TIM3_GPIO_Config();
    TIM3_Mode_Config();
}
/*end of TIM3*/

/*begin of TIM1*/
void TIM1_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM1_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);    /*使能TIM1时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); /*使能GPIOB时钟*/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; /**/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; /*PB0 PB1 输入*/
    GPIO_Init(GPIOA,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_9|GPIO_Pin_10); /*PB0 PB1 下拉*/

    /*初始化定时器3 TIM1*/
    TIM_TimeBaseStructure.TIM_Period = TIMCapture_PERIOD - 1; /*设定计数器自动重装值 */
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1; /*预分频器 1us*/
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; /*设置时钟分割:TDTS = Tck_tim*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /*TIM向上计数模式*/
    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure); /*根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位*/

    /* 初始化TIM1输入捕获参数 */
    TIM1_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; /*上升沿捕获*/
    TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /*映射到TI3上*/
    TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /*配置输入分频,不分频*/
    TIM1_ICInitStructure.TIM_ICFilter = 0; /*IC1F=0000 配置输入滤波器 不滤波*/
    TIM_ICInit(TIM1,&TIM1_ICInitStructure);

    TIM1_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM1_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; /*上升沿捕获*/
    TIM1_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /*映射到TI4上*/
    TIM1_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /*配置输入分频,不分频*/
    TIM1_ICInitStructure.TIM_ICFilter = 0; /*IC1F=0000 配置输入滤波器 不滤波*/
    TIM_ICInit(TIM1,&TIM1_ICInitStructure);

    /*中断分组初始化*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;    /*TIM1中断*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; /*先占优先级0级*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; /*从优先级0级*/
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /*IRQ通道被使能*/
    NVIC_Init(&NVIC_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;    /*TIM1中断*/
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM1,TIM_IT_Update|TIM_IT_CC2|TIM_IT_CC3,ENABLE);/*允许更新中断 ,允许CC3 CC2捕获中断*/
    TIM_Cmd(TIM1,ENABLE); /*使能定时器1*/
}

/**
* 定时器1输入捕获中断服务程序
*/
void TIM1_CC_IRQHandler(void)
{
    // myPrintf("K\r\n");

    if(TIM_GetITStatus(TIM1,TIM_IT_CC3) != RESET) {
        if(TIMCaptureState[5] & TIMCaptureState_SET) { //处于测量阶段，被下降沿触发
            TIMCaptureValue[5] = TIM_GetCounter(TIM1) + ((!!(TIMCaptureState[5] & TIMCaptureState_OVERFLOW))?TIMCapture_PERIOD:0) - TIMCapturePreviousCounter[5];
            TIMCaptureState[5] = TIMCaptureState_RESET;
            TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Rising); //设置为上升沿捕获
        } else {
            TIMCapturePreviousCounter[5] = TIM_GetCounter(TIM1);
            TIMCaptureState[5] |= TIMCaptureState_SET;
            TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Falling); //设置为下降沿捕获
        }
        TIM_ClearITPendingBit(TIM1,TIM_IT_CC3);
    }

    if(TIM_GetITStatus(TIM1,TIM_IT_CC2) != RESET) {
        if(TIMCaptureState[6] & TIMCaptureState_SET) { //处于测量阶段，被下降沿触发
            TIMCaptureValue[6] = TIM_GetCounter(TIM1) + ((!!(TIMCaptureState[6] & TIMCaptureState_OVERFLOW))?TIMCapture_PERIOD:0) - TIMCapturePreviousCounter[6];
            TIMCaptureState[6] = TIMCaptureState_RESET;
            TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Rising); //设置为上升沿捕获
        } else {
            TIMCapturePreviousCounter[6] = TIM_GetCounter(TIM1);
            TIMCaptureState[6] |= TIMCaptureState_SET;
            TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Falling); //设置为下降沿捕获
        }
        TIM_ClearITPendingBit(TIM1,TIM_IT_CC2);
    }
}
void TIM1_UP_IRQHandler()
{
    if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET) {
        if(TIMCaptureState[5] & TIMCaptureState_SET) {
            TIMCaptureState[5] |= TIMCaptureState_OVERFLOW;
        }
        if(TIMCaptureState[6] & TIMCaptureState_SET) {
            TIMCaptureState[6] |= TIMCaptureState_OVERFLOW;
        }
        TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
    }
}
/*end of TIM1*/



/*begin of TIM4*/
void TIM4_Init()
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_ICInitTypeDef TIM4_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);    /*使能TIM4时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); /*使能GPIOB时钟*/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; /**/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; /*PB0 PB1 输入*/
    GPIO_Init(GPIOB,&GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9); /*PB0 PB1 下拉*/

    /*初始化定时器3 TIM4*/
    TIM_TimeBaseStructure.TIM_Period = TIMCapture_PERIOD - 1; /*设定计数器自动重装值 */
    TIM_TimeBaseStructure.TIM_Prescaler = 72-1; /*预分频器 1us*/
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; /*设置时钟分割:TDTS = Tck_tim*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /*TIM向上计数模式*/
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure); /*根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位*/

    /* 初始化TIM4输入捕获参数 */
    TIM4_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; /*上升沿捕获*/
    TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /*映射到TI3上*/
    TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /*配置输入分频,不分频*/
    TIM4_ICInitStructure.TIM_ICFilter = 0; /*IC1F=0000 配置输入滤波器 不滤波*/
    TIM_ICInit(TIM4,&TIM4_ICInitStructure);

    /* 初始化TIM4输入捕获参数 */
    TIM4_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; /*上升沿捕获*/
    TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /*映射到TI3上*/
    TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /*配置输入分频,不分频*/
    TIM4_ICInitStructure.TIM_ICFilter = 0; /*IC1F=0000 配置输入滤波器 不滤波*/
    TIM_ICInit(TIM4,&TIM4_ICInitStructure);

    TIM4_ICInitStructure.TIM_Channel = TIM_Channel_3;
    TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; /*上升沿捕获*/
    TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /*映射到TI4上*/
    TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /*配置输入分频,不分频*/
    TIM4_ICInitStructure.TIM_ICFilter = 0; /*IC1F=0000 配置输入滤波器 不滤波*/
    TIM_ICInit(TIM4,&TIM4_ICInitStructure);

    /* 初始化TIM4输入捕获参数 */
    TIM4_ICInitStructure.TIM_Channel = TIM_Channel_4;
    TIM4_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; /*上升沿捕获*/
    TIM4_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /*映射到TI3上*/
    TIM4_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /*配置输入分频,不分频*/
    TIM4_ICInitStructure.TIM_ICFilter = 0; /*IC1F=0000 配置输入滤波器 不滤波*/
    TIM_ICInit(TIM4,&TIM4_ICInitStructure);

    /*中断分组初始化*/
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;    /*TIM4中断*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; /*先占优先级0级*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; /*从优先级0级*/
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /*IRQ通道被使能*/
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM4,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);/*允许更新中断 ,允许CC3 CC2捕获中断*/
    TIM_Cmd(TIM4,ENABLE); /*使能定时器1*/
}

/**
* 定时器1输入捕获中断服务程序
*/
void TIM4_IRQHandler(void)
{
    // myPrintf("K\r\n");
    if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET) {
        if(TIMCaptureState[1] & TIMCaptureState_SET) {
            TIMCaptureState[1] |= TIMCaptureState_OVERFLOW;
        }
        if(TIMCaptureState[2] & TIMCaptureState_SET) {
            TIMCaptureState[2] |= TIMCaptureState_OVERFLOW;
        }
        if(TIMCaptureState[3] & TIMCaptureState_SET) {
            TIMCaptureState[3] |= TIMCaptureState_OVERFLOW;
        }
        if(TIMCaptureState[4] & TIMCaptureState_SET) {
            TIMCaptureState[4] |= TIMCaptureState_OVERFLOW;
        }
        TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
    }

    if(TIM_GetITStatus(TIM1,TIM_IT_CC1) != RESET) {
        if(TIMCaptureState[1] & TIMCaptureState_SET) { //处于测量阶段，被下降沿触发
            TIMCaptureValue[1] = TIM_GetCounter(TIM1) + ((!!(TIMCaptureState[1] & TIMCaptureState_OVERFLOW))?TIMCapture_PERIOD:0) - TIMCapturePreviousCounter[1];
            TIMCaptureState[1] = TIMCaptureState_RESET;
            TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Rising); //设置为上升沿捕获
        } else {
            TIMCapturePreviousCounter[1] = TIM_GetCounter(TIM1);
            TIMCaptureState[1] |= TIMCaptureState_SET;
            TIM_OC1PolarityConfig(TIM1,TIM_ICPolarity_Falling); //设置为下降沿捕获
        }
        TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
    }

    if(TIM_GetITStatus(TIM1,TIM_IT_CC2) != RESET) {
        if(TIMCaptureState[2] & TIMCaptureState_SET) { //处于测量阶段，被下降沿触发
            TIMCaptureValue[2] = TIM_GetCounter(TIM1) + ((!!(TIMCaptureState[2] & TIMCaptureState_OVERFLOW))?TIMCapture_PERIOD:0) - TIMCapturePreviousCounter[2];
            TIMCaptureState[2] = TIMCaptureState_RESET;
            TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Rising); //设置为上升沿捕获
        } else {
            TIMCapturePreviousCounter[2] = TIM_GetCounter(TIM1);
            TIMCaptureState[2] |= TIMCaptureState_SET;
            TIM_OC2PolarityConfig(TIM1,TIM_ICPolarity_Falling); //设置为下降沿捕获
        }
        TIM_ClearITPendingBit(TIM1,TIM_IT_CC2);
    }

    if(TIM_GetITStatus(TIM1,TIM_IT_CC3) != RESET) {
        if(TIMCaptureState[3] & TIMCaptureState_SET) { //处于测量阶段，被下降沿触发
            TIMCaptureValue[3] = TIM_GetCounter(TIM1) + ((!!(TIMCaptureState[3] & TIMCaptureState_OVERFLOW))?TIMCapture_PERIOD:0) - TIMCapturePreviousCounter[3];
            TIMCaptureState[3] = TIMCaptureState_RESET;
            TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Rising); //设置为上升沿捕获
        } else {
            TIMCapturePreviousCounter[3] = TIM_GetCounter(TIM1);
            TIMCaptureState[3] |= TIMCaptureState_SET;
            TIM_OC3PolarityConfig(TIM1,TIM_ICPolarity_Falling); //设置为下降沿捕获
        }
        TIM_ClearITPendingBit(TIM1,TIM_IT_CC3);
    }

    if(TIM_GetITStatus(TIM1,TIM_IT_CC4) != RESET) {
        if(TIMCaptureState[4] & TIMCaptureState_SET) { //处于测量阶段，被下降沿触发
            TIMCaptureValue[4] = TIM_GetCounter(TIM1) + ((!!(TIMCaptureState[4] & TIMCaptureState_OVERFLOW))?TIMCapture_PERIOD:0) - TIMCapturePreviousCounter[4];
            TIMCaptureState[4] = TIMCaptureState_RESET;
            TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Rising); //设置为上升沿捕获
        } else {
            TIMCapturePreviousCounter[4] = TIM_GetCounter(TIM1);
            TIMCaptureState[4] |= TIMCaptureState_SET;
            TIM_OC4PolarityConfig(TIM1,TIM_ICPolarity_Falling); //设置为下降沿捕获
        }
        TIM_ClearITPendingBit(TIM1,TIM_IT_CC4);
    }

}
/*end of TIM4*/
