
#ifndef SERVO_PORTE_H
#define SERVO_PORTE_H
#include <Arduino.h>
#include <Servo.h>

class Servo_Porte : public Servo {
  public:
    Servo_Porte();
    void init(int servoPin);
    void activate();
    void deactivate();
};

#endif
