#ifndef __LED_h__
#define __LED_h__
#include "ChainableLED.h"

class LED : public ChainableLED
{
public:
    LED(byte clk_pin, byte data_pin);
    ~LED();

    void rouge();
    void vert();
    void clignoteOrangeVert(int nbre_clignotements, int freq_clignotements);
    void clignoteBleuVert(int nbre_clignotements, int freq_clignotements);
};

#endif
