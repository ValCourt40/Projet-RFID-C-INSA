
#ifndef ELECTRO_H
#define ELECTRO_H

#include <Arduino.h>

class Electromagnet {
  private:
    int pin;

  public:
    Electromagnet(int electromagnetPin);
    void activate();
    void deactivate();
};

#endif
