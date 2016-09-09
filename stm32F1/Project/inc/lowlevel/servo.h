#ifndef _SERVO_H
#define _SERVO_H

#include "stm32f10x.h"

enum Servo{
  servo1 = 1, servo2, servo3, servo4
};

#define SERVO_TIM_PERIOD 5000

void SERVO_Init(void);
void setServoAngle(enum Servo s, float angle);//angle must be a float in -90.0 ~ 90.0

#endif
