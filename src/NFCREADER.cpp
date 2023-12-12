#include "NFCREADER.h"

#define SS_PIN D3
#define RST_PIN D0

MFRC522 rfid(SS_PIN, RST_PIN); // Instance de classe
MFRC522 blou(SS_PIN, RST_PIN); // Instance de classe
MFRC522::MIFARE_Key key; // Instance de la cle(badge)
Classe_NFC_Lecture Carte1 ; 
byte nuidPICC[4]; //tableau pour stockage du num UID
byte Mauvais[4]={0xC3, 0xE6, 0x4C, 0x4F}; 

void printHex(byte *buffer, byte bufferSize) { //methode pour afficher les noombres en hexa d'un tableau donné 
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void printDec(byte *buffer, byte bufferSize) {//methode pour afficher les nombres en decimal d'un tableau donné 
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
Classe_NFC_Lecture::Classe_NFC_Lecture(){}



void Classe_NFC_Lecture::init_nfc ()
{
    SPI.begin(); // Initialisation bus SPI
    rfid.PCD_Init(); // Initialisation MFRC522
    
    Serial.print(F("Reader :"));
    rfid.PCD_DumpVersionToSerial(); // Donne les informations d'initialisation du capteur

    for (byte i = 0; i < 6; i++) 
    {
    key.keyByte[i] = 0xFF; // choix du code des 6 octets à mettre sur la carte: par def | 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF|
    }
     Serial.println();
  
  Serial.print(F("La clé à utiliser est:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);

}



void Classe_NFC_Lecture::lecture_UID_carte ()
{
    
  if ( ! rfid.PICC_IsNewCardPresent()) // Sort de la fonction si aucune carte n'est présente devant le capteur
    {
    return;
    }
    
  if ( ! rfid.PICC_ReadCardSerial())
  {
    return; //On verifie que le num UID soit bien lu
  }
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
      piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
      piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Votre badge n'est pas adapté"));
    return;
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] ||
      rfid.uid.uidByte[1] != nuidPICC[1] ||
      rfid.uid.uidByte[2] != nuidPICC[2] ||
      rfid.uid.uidByte[3] != nuidPICC[3] ) {
    Serial.println(F("Une nouvelle carte est detectée."));

    // On range le nouvel UID lu sur la carte dans notre variable
    for (byte i = 0; i < 4; i++) {
      nuidPICC[i] = rfid.uid.uidByte[i];
    }
   

    Serial.println(F("Sont numéro UID est:"));

    Serial.print(F("En hexa: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("En decimal: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  }
  else Serial.println(F("La carte vient d'être lue."));

  // Arret des méthodes
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

}

byte Classe_NFC_Lecture::GetAccesState (byte *CodeAcces)
{
  byte StateAcces=0; 
  if ((CodeAcces[0]==rfid.uid.uidByte[0])&&(CodeAcces[1]==rfid.uid.uidByte[1])&&
  (CodeAcces[2]==rfid.uid.uidByte[2])&& (CodeAcces[3]==rfid.uid.uidByte[3]))
    return StateAcces=1; 
  else
    return StateAcces=0; 
}

byte Classe_NFC_Lecture::MauvaisBadge(){
   byte StateAcces=0; 
  if ((Mauvais[0]==rfid.uid.uidByte[0])&&(Mauvais[1]==rfid.uid.uidByte[1])&&
  (Mauvais[2]==rfid.uid.uidByte[2])&& (Mauvais[3]==rfid.uid.uidByte[3]))
    return StateAcces=1; 
  else
    return StateAcces=0; 


}
void Classe_NFC_Lecture::stopAcces()
{
  rfid.uid.uidByte[0]=0;
}


void Classe_NFC_Lecture::lecture_donnee_carte (){

  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //Variables locales
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Même oppération de vérification que pour la lecture UID
  if ( ! rfid.PICC_IsNewCardPresent()) {
    return;
  }

  
  if ( ! rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));

  //-------------------------------------------

  rfid.PICC_DumpDetailsToSerial(&(rfid.uid)); // Details de la carte

  

  Serial.print(F("Name: "));

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- Prénom écris sur la carte
  status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(rfid.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(rfid.GetStatusCodeName(status));
    return;
  }

  status = rfid.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(rfid.GetStatusCodeName(status));
    return;
  }

  //PRINT Prénom écrit sur la carte
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }
  Serial.print(" ");

  //---------------------------------------- Nom ecrit sur la carte

  byte buffer2[18];
  block = 1;

  status = rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(rfid.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(rfid.GetStatusCodeName(status));
    return;
  }

  status = rfid.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(rfid.GetStatusCodeName(status));
    return;
  }

  //PRINT Nom
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );
  }


  //----------------------------------------

  Serial.println(F("\n**End Reading**\n"));

  delay(2000); //Lecture de carte delay 2 secondes pour avoir le temps de sortir la carte

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

}
