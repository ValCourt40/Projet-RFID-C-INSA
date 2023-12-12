#include "NFCREADER.h"
#include "NFCWRITER.h"
#include "LED_PORTE.h"
#include "Buzzer.h"
#include "Servo_Porte.h"


Classe_NFC_Lecture nfc;
LED leds(D1,D2);
Servo_Porte servo;


byte CodeVerif=0; 
byte CodeMauvais=0; 
byte Code_Acces[4]={0xC3, 0x5A, 0x96, 0x4F}; 
int presence;

void setup() {
Serial.begin(9600);
nfc.init_nfc();
leds.init();
servo.init(D9);

}


void loop() {

nfc.lecture_donnee_carte();
delay(100);
CodeVerif = nfc.GetAccesState(Code_Acces);
CodeMauvais = nfc.MauvaisBadge();
Serial.print(CodeVerif);

if (CodeVerif==1 )
{
  
  leds.clignoteBleuVert(6,100);
  delay(1000);
  servo.activate();
  delay(5000);
  servo.deactivate();
  nfc.stopAcces();
}
else if(CodeVerif==0 && CodeMauvais == 1) {
  leds.clignoteRouge(6, 100);
  delay(1000);
  nfc.stopAcces();
}
else{leds.rouge();}

}
