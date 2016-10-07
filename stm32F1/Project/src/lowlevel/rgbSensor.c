#include "rgbSensor.h"

#define TIMCaptureState_RESET    0x00
#define TIMCaptureState_SET     0x01
#define TIMCaptureState_OVERFLOW 0x02

#define TIMCapture_PERIOD                  50000   //us
#define TIMCapture_PRESCALER               72
#define IsTIMCaptureValueValid(VAL)              ((VAL<2000) && (VAL>1000))

static volatile u16 rgbSensorCaptureValue[1] = {0}; //捕获到的值
const volatile u16 *rgbSensorValues = rgbSensorCaptureValue;
static volatile u8 rgbSensorCaptureState[1] = {TIMCaptureState_RESET};  //捕获状态
static volatile u16 rgbSensorCapturePreviousCounter[1] = {0}; //上升沿时的计数器值

void rgbSensor_Init(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); /*使能GPIOB时钟*/

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; /*PB1输入*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; /**/
  GPIO_Init(GPIOB,&GPIO_InitStructure);
  GPIO_ResetBits(GPIOB,GPIO_Pin_1); /*PB1下拉*/

  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStructure);

  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);    /*使能TIM3时钟*/

  /*初始化定时器3 TIM3*/
  TIM_TimeBaseStructure.TIM_Period = TIMCapture_PERIOD - 1; /*设定计数器自动重装值 */
  TIM_TimeBaseStructure.TIM_Prescaler = TIMCapture_PRESCALER - 1; /*预分频器 1us*/
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; /*设置时钟分割:TDTS = Tck_tim*/
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; /*TIM向上计数模式*/
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure); /*根据TIM_TimeBaseInitStruct中指定的参数初始化TIM3的时间基数单位*/

  /* 初始化TIM3输入捕获参数 */
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; /*上升沿捕获*/
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; /*映射到TI4上*/
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; /*配置输入分频,不分频*/
  TIM_ICInitStructure.TIM_ICFilter = 0; /*IC1F=0000 配置输入滤波器 不滤波*/
  TIM_ICInit(TIM3,&TIM_ICInitStructure);

  /*中断分组初始化*/
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;    /*TIM1中断*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; /*先占优先级0级*/
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; /*从优先级0级*/
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; /*IRQ通道被使能*/
  NVIC_Init(&NVIC_InitStructure);

  TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC4,ENABLE);/*允许更新中断 ,允许CC3捕获中断*/
  TIM_Cmd(TIM3,ENABLE); /*使能定时器3*/
  rgbSensor_setColor(white);
}

void rgbSensor_setColor(enum rgbSensorColor color){
  switch(color)
  {
    case red:
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
    break;

    case green:
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
    break;

    case blue:
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
    break;

    case white:
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
      GPIO_SetBits(GPIOB,GPIO_Pin_3);
    break;

    default:
    break;
  }
}

/**
* 定时器3输入捕获中断服务程序
*/
void TIM3_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM3,TIM_IT_CC4) != RESET) {
      if(rgbSensorCaptureState[0] & TIMCaptureState_SET) { //处于测量阶段，被下降沿触发
          rgbSensorCaptureValue[0] = TIM_GetCounter(TIM3) + ((!!(rgbSensorCaptureState[0] & TIMCaptureState_OVERFLOW))?TIMCapture_PERIOD:0) - rgbSensorCapturePreviousCounter[5];
          rgbSensorCaptureState[0] = TIMCaptureState_RESET;
          TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Rising); //设置为上升沿捕获
      } else {
          rgbSensorCapturePreviousCounter[0] = TIM_GetCounter(TIM3);
          rgbSensorCaptureState[0] |= TIMCaptureState_SET;
          TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Falling); //设置为下降沿捕获
      }
      TIM_ClearITPendingBit(TIM3,TIM_IT_CC4);
  }

  if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET) {
      if(rgbSensorCaptureState[0] & TIMCaptureState_SET) {
          rgbSensorCaptureState[0] |= TIMCaptureState_OVERFLOW;
      }
      TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
  }
}
