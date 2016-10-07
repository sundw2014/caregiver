#ifndef _RGBSENSOR_H
#define _RGBSENSOR_H
#include "stm32f10x.h"

enum rgbSensorColor{
  red = 1, green, blue, white
};

const volatile u16 *rgbSensorValues; //only rgbSensorValues[0] is available

void rgbSensor_Init(void);
void rgbSensor_setColor(enum rgbSensorColor);

#endif
