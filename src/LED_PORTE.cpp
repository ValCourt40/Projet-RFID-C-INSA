#include "LED_PORTE.h"

LED::LED(byte clk_pin, byte data_pin) : LEDchainable(clk_pin, data_pin, 1)
{
    // Le constructeur de la classe de base est appelé automatiquement et on n'a ici qu'une simple LED
}

LED::~LED()
{
    // Le destructeur
}

void LED::rouge()// méthode pour allumer la LED en rouge
{
    setColorRGB(0, 255, 0, 0);  // Rouge complet, pas de vert, pas de bleu
}

void LED::vert()// méthode pour allumer la LED en vert
{
    setColorRGB(0, 0, 255, 0);  // Pas de rouge, vert complet, pas de bleu
}

void LED::clignoteOrangeVert(int nbre_clignotements, int freq_clignotements)
{
    for (int i = 0; i < nbre_clignotements; ++i)
    {
        // Allumer la LED en orange
        setColorRGB(0, 255, 69, 0);  // Rouge complet, vert moyen, pas de bleu
        delay(freq_clignotements);

        // Éteindre la LED
        setColorRGB(0, 0, 0, 0);
        delay(freq_clignotements);

        // Allumer la LED en vert
        setColorRGB(0, 0, 255, 0);  // Pas de rouge, vert complet, pas de bleu
        delay(freq_clignotements);

        // Éteindre la LED
        setColorRGB(0, 0, 0, 0);
        delay(freq_clignotements);
    }
}

void LED::clignoteBleuVert(int nbre_clignotements, int freq_clignotements)
{
    for (int i = 0; i < nbre_clignotements; ++i)
    {
        // Allumer la LED en orange
        setColorRGB(0, 0, 0, 255);  // Pas de rouge , pas de vert, bleu complet
        delay(freq_clignotements);

        // Éteindre la LED
        setColorRGB(0, 0, 0, 0);
        delay(freq_clignotements);

        // Allumer la LED en vert
        setColorRGB(0, 0, 255, 0);  // Pas de rouge, vert complet, pas de bleu
        delay(freq_clignotements);

        // Éteindre la LED
        setColorRGB(0, 0, 0, 0);
        delay(freq_clignotements);
    }
}

void LED::clignoteRouge(int nbre_clignotements, int freq_clignotements)
{
    for (int i = 0; i < nbre_clignotements; ++i)
    {
        // Allumer la LED en orange
        setColorRGB(0, 255, 0, 0);  // Pas de rouge , pas de vert, bleu complet
        delay(freq_clignotements);

        // Éteindre la LED
        setColorRGB(0, 0, 0, 0);
        delay(freq_clignotements);

        // Allumer la LED en vert
        setColorRGB(0, 255, 0, 0);  // Pas de rouge, vert complet, pas de bleu
        delay(freq_clignotements);

        // Éteindre la LED
        setColorRGB(0, 0, 0, 0);
        delay(freq_clignotements);
    }
}