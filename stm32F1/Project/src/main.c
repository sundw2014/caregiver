#include "common.h"
#include "utilities.h"

void main()
{
    Init();

    while(1)
    {
        //myPrintf(USART1, "ch1=%d, ch2=%d, ch3=%d, ch4=%d. ch5=%d, ch6=%d\r\n", receiverValues[1], receiverValues[2], receiverValues[3],\
        receiverValues[4], receiverValues[5], receiverValues[6]);
        //myPrintf(USART1,"%d,%d,%d,%d,%d,%d,%d\r\n",BTBuf[0],BTBuf[1],BTBuf[2],BTBuf[3],BTBuf[4],BTBuf[5],BTBuf[6]);
        int speed = (BTBuf[1]-100)/100.0*5000.0;
        int speed1=0,speed2=0;
        int turn = BTBuf[0] - 100;
        if(turn>30||turn<-30) {
        speed1=(BTBuf[0]-100)/100.0*5000.0;
            speed2=-speed1;
        }
        else {
            speed1=speed2=speed;
        }
        setMotorSpeed(motor1,speed1);
        setMotorSpeed(motor2,speed2);
        int angle=(BTBuf[3]-100)/100.0*90.0;
        setServoAngle(servo1,angle);
        //DelayMs(500);
    }
}
