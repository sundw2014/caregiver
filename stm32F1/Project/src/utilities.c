#include "utilities.h"

unsigned char BTBuf[7]= {100,100,100,100,100,100,100};

void Init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);           //中断优先级分组为2 note:2 bits for pre-emption priority, 2 bits for subpriority

    DelayInit();   //SysTick init
    // DelayS(1);
    #ifdef USE_USART1
      USART1_Init(); //user serial port
    #endif
    USART3_Init(); //bluetooth

    RECEIVER_Init();
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

void BluetoothReceiveInterruput(const unsigned char s)
{
    // myPrintf(USART1, "%c", s);
    static char state = 0;
    static int cnt = 0;
    switch (state)
    {
    case 0:
        state = (s == 0xAA)?1:0;
        break;
    case 1:
        state = (s == 0xBB)?2:0;
        break;
    case 2:
        state = (s == 0xCC)?3:0;
        break;
    case 3:
        BTBuf[cnt] = s;
        cnt ++;
        if(cnt == 7)
        {
            cnt = 0;
            state = 0;
        }
        break;
    default:
        break;
    }
}
