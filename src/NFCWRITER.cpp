#include "NFCWRITER.h"

#define SS_PIN D3
#define RST_PIN D0
MFRC522 rfids(SS_PIN, RST_PIN); // Instance de classe
MFRC522::MIFARE_Key keys; // Instance de la cle(badge)

Carte_NFC_Ecriture::Carte_NFC_Ecriture(){}

void Carte_NFC_Ecriture::ecriture_carte(){
  for (byte i = 0; i < 6; i++) keys.keyByte[i] = 0xFF;

  // Boucle infini tant que pas de carte présente
  if ( ! rfids.PICC_IsNewCardPresent()) {
    return;
  }

 
  if ( ! rfids.PICC_ReadCardSerial()) {
    return;
  }

  Serial.print(F("UID de la carte:"));    //Affiche UID
  for (byte i = 0; i < rfids.uid.size; i++) {
    Serial.print(rfids.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfids.uid.uidByte[i], HEX);
  }
  Serial.print(F("Type de PICC : "));   
  MFRC522::PICC_Type piccType = rfids.PICC_GetType(rfids.uid.sak);
  Serial.println(rfids.PICC_GetTypeName(piccType));

  byte buffer[34];
  byte block;
  MFRC522::StatusCode status;
  byte len;

  Serial.setTimeout(20000L) ;     // Attendre 20 secondes l'entrée du nom
  // NOM
  Serial.println(F("Taper le nom en terminant par #"));
  len = Serial.readBytesUntil('#', (char *) buffer, 30) ; // Lire le nom de famille
  for (byte i = len; i < 30; i++) buffer[i] = ' ';     // Completer le reste avec des espaces

  block = 1;
  //Serial.println(F("Authenticating using key A..."));
  status = rfids.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keys, &(rfids.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentification échouée: "));
    Serial.println(rfids.GetStatusCodeName(status));
    return;
  }
  else Serial.println(F("Authentification réussie: "));

  // Write block
  status = rfids.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Ecriture échouée: "));
    Serial.println(rfids.GetStatusCodeName(status));
    return;
  }
  else Serial.println(F("Ecriture réussie: "));

  block = 2;
  //Serial.println(F("Authenticating using key A..."));
  status = rfids.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keys, &(rfids.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentification échouée: "));
    Serial.println(rfids.GetStatusCodeName(status));
    return;
  }

  // Write block
  status = rfids.MIFARE_Write(block, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Ecriture échouée: "));
    Serial.println(rfids.GetStatusCodeName(status));
    return;
  }
  else Serial.println(F("Ecriture réussie: "));

  //Prénom
  Serial.println(F("Taper le prénom en terminant par #"));
  len = Serial.readBytesUntil('#', (char *) buffer, 20) ; // Lire prénom
  for (byte i = len; i < 20; i++) buffer[i] = ' ';     // Remplir avec espaces

  block = 4;
  //Serial.println(F("Authenticating using key A..."));
  status = rfids.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keys, &(rfids.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentification échouée: "));
    Serial.println(rfids.GetStatusCodeName(status));
    return;
  }

  // Bloc écriture
  status = rfids.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Ecriture échouée: "));
    Serial.println(rfids.GetStatusCodeName(status));
    return;
  }
  else Serial.println(F("Ecriture réussie: "));

  block = 5;
  //Serial.println(F("Authenticating using key A..."));
  status = rfids.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &keys, &(rfids.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentification non réussie: "));
    Serial.println(rfids.GetStatusCodeName(status));
    return;
  }

  // Ecriture Block
  status = rfids.MIFARE_Write(block, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Ecriture échouée: "));
    Serial.println(rfids.GetStatusCodeName(status));
    return;
  }
  else Serial.println(F("Ecriture réussi: "));


  Serial.println(" ");
  rfids.PICC_HaltA(); // Arret des méthode
  rfids.PCD_StopCrypto1();  
}

