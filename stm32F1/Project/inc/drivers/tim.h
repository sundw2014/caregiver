#ifndef __TIM_H_
#define __TIM_H_

//clock of timer is 72MHz
void TIM1_Init(void);
void TIM5_PWM_Init(void);
void TIM3_PWM_Init(void);
void TIM4_Init(void);

#define TIMCaptureState_RESET    0x00
#define TIMCaptureState_SET     0x01
#define TIMCaptureState_OVERFLOW 0x02

#define TIMCapture_PERIOD                  50000   //us
#define IsTIMCaptureValueValid(VAL)              ((VAL<2000) && (VAL>1000))

#define MOTOR_PWM_PERIOD 5000

volatile extern u16 TIMCaptureValue[7]; //捕获到的值,1,2,3,4,5,6有效

#endif
