#ifndef APPLICATION_H
#define APPLICATION_H
#include <Arduino.h>
#include "NFCWRITER.h"
#include "LED_PORTE.h"
#include "Buzzer.h"
#include "Servo_Porte.h"

class Application : public LED, public Buzzer, public Carte_NFC_Ecriture, public Servo_Porte{
  public :
  Application (int buzzerPin, byte clk_pin, byte data_pin);
  void init();
  void run();
};



#endif