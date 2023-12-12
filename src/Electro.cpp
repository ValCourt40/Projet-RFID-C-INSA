#include "Electro.h"
#include <Arduino.h>


Electromagnet::Electromagnet(int electromagnetPin) : pin(electromagnetPin) {
  pinMode(pin, OUTPUT); // Initialisation de l'électroaimant par le pin
}

void Electromagnet::activate() {
  digitalWrite(pin, HIGH); // Activer l'electroaimant
}

void Electromagnet::deactivate() {
  digitalWrite(pin, LOW); // Désactiver l'electroaimant
}


