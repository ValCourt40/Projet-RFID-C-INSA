#include <Arduino.h>
#include "Application.h"

Classe_NFC_Lecture nfc;
LED leds(D1,D2);
Servo_Porte servo;
Buzzer buzze(D8);

byte CodeVerif=0; 
byte CodeMauvais=0; 
byte Code_Acces[4]={0xC3, 0x5A, 0x96, 0x4F}; 
int presence;

Application::Application(int buzzerPin, byte clk_pin, byte data_pin):LED( clk_pin, data_pin),Buzzer(buzzerPin){

  Carte_NFC_Ecriture();
  Servo_Porte();
}


void Application::init(){
  Serial.begin(9600);
  nfc.init_nfc();
  leds.init();
  servo.init(D9);
  buzze.stop();
  
}

void Application::run(){

  nfc.lecture_donnee_carte();
  delay(100);
  CodeVerif = nfc.GetAccesState(Code_Acces);
  CodeMauvais = nfc.MauvaisBadge();
  Serial.print(CodeVerif);

  if (CodeVerif==1 )
  {
    
    leds.clignoteBleuVert(6,100);
    buzze.validationSound();
    servo.activate();
    delay(5000);
    servo.deactivate();
    nfc.stopAcces();
  }
  else if(CodeVerif==0 && CodeMauvais == 1) {
    leds.clignoteRouge(6, 100);
    buzze.refusalSound();
    delay(1000);
    nfc.stopAcces();
  }
  else{leds.rouge();}


}