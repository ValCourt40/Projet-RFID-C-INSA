#ifndef __LED_h__
#define __LED_h__
#include "LED_Chainable.h"

class LED : public LEDchainable
{
public:
    LED(byte clk_pin, byte data_pin);
    ~LED();

    void rouge();
    void vert();
    void clignoteOrangeVert(int nbre_clignotements, int freq_clignotements);
    void clignoteBleuVert(int nbre_clignotements, int freq_clignotements);
    void clignoteRouge(int nbre_clignotements, int freq_clignotements);
};

#endif
