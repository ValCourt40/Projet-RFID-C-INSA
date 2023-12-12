#include "Servo_Porte.h"


Servo servo();

Servo_Porte::Servo_Porte() : Servo() {
}


void Servo_Porte::init(int servoPin){
  attach(servoPin); // Initialisation de l'électroaimant par le pin
}

void Servo_Porte::activate() {
  write(180); // Activer l'electroaimant
}

void Servo_Porte::deactivate() {
  write(0); // Désactiver l'electroaimant
}