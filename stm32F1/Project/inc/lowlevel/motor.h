#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f10x.h"

enum Motor{
  motor1 = 1, motor2, motor3, motor4
};

#define MOTOR_TIM_PERIOD 5000

void MOTOR_Init(void);
void setMotorSpeed(enum Motor m, int speed);//speed must be a integer in -5000 ~ 5000

#endif
