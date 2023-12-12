
#ifndef _NFCREADER_
#define _NFCREADER_
  
#include <stdint.h>
#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

class Classe_NFC_Lecture {

    protected:
     

    public:
    
    Classe_NFC_Lecture();
    void init_nfc ();
    void lecture_UID_carte ();
    void lecture_donnee_carte ();
    byte GetAccesState(byte *CodeAcces);
    byte MauvaisBadge();
    void stopAcces();
    
    
};
  


#endif