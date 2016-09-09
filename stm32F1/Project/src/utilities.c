#include "utilities.h"

void Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           //中断优先级分组为2 note:2 bits for pre-emption priority, 2 bits for subpriority

    DelayInit();   //SysTick init
    // DelayS(1);

    USART1_Init(); //user serial port
    USART3_Init(); //bluetooth

    RECEIVER_Init(); //Receiver channel 5,6
    MOTOR_Init();
    SERVO_Init();

    setMotorSpeed(motor1,0);
    setMotorSpeed(motor2,0);
    setMotorSpeed(motor3,0);
    setMotorSpeed(motor4,0);

    setServoAngle(servo1,0);
    setServoAngle(servo2,0);
    setServoAngle(servo3,0);
    setServoAngle(servo4,0);
}
