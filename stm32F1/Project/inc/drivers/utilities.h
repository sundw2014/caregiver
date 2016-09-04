void Init();
__attribute__((weak)) void BluetoothReceiveInterruput(unsigned char c);

enum Motor{
  motor1 = 1, motor2, motor3, motor4
};
enum Servo{
  servo1 = 1, servo2, servo3, servo4
};

void setMotorSpeed(enum Motor m, int speed);//speed must be a integer in -5000 ~ 5000
void setServoAngle(enum Servo s, float angle);//angle must be a float in -90.0 ~ 90.0
