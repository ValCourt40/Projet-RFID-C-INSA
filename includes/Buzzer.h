#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
  private:
    int pin;

  public:
    Buzzer(int buzzerPin);
    void buzz(int frequency, int duration);
    void stop();
    void validationSound();
    void refusalSound();
};

#endif
