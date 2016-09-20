#ifndef _COMMON_H
#define _COMMON_H

#include "stm32f10x.h"
#include "motor.h"
#include "servo.h"
#include "receiver.h"
#include "usart.h"
#include "delay.h"

//defines
#define USE_BT

#ifdef USE_BT
  #define USE_USART1
#endif

#ifdef USE_RECEIVER

#endif

#endif
