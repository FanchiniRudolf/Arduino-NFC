#include <SPI.h>
#include <MFRC522.h>
 
 
#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above
#define SS_PIN2          7          // Configurable, see typical pin layout above


MFRC522 mfrc522(SS_PIN, RST_PIN);  
MFRC522 mfrc522_2(SS_PIN2, RST_PIN);  

bool rfid_tag_present_prev = false;
bool rfid_tag_present = false;
int _rfid_error_counter = 0;
bool _tag_found = false;

bool rfid_tag_present_prev2 = false;
bool rfid_tag_present2 = false;
int _rfid_error_counter2 = 0;
bool _tag_found2 = false;

boolean checkTag(){
  
 rfid_tag_present_prev = rfid_tag_present;

  _rfid_error_counter += 1;
  if(_rfid_error_counter > 2){
    _tag_found = false;
  }

  // Detect Tag without looking for collisions
  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);

  // Reset baud rates
  mfrc522.PCD_WriteRegister(mfrc522.TxModeReg, 0x01);
  mfrc522.PCD_WriteRegister(mfrc522.RxModeReg, 0x01);
  // Reset ModWidthReg
  mfrc522.PCD_WriteRegister(mfrc522.ModWidthReg, 0x26);

  MFRC522::StatusCode result = mfrc522.PICC_RequestA(bufferATQA, &bufferSize);

  if(result == mfrc522.STATUS_OK){
    if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue   
      
      return false;
    }
    _rfid_error_counter = 0;
    _tag_found = true;        
  }
  
  rfid_tag_present = _tag_found;
  
}
boolean checkTag2(){
  
 rfid_tag_present_prev2 = rfid_tag_present2;

  _rfid_error_counter2 += 1;
  if(_rfid_error_counter2 > 2){
    _tag_found2 = false;
  }

  // Detect Tag without looking for collisions
  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);

  // Reset baud rates
  mfrc522_2.PCD_WriteRegister(mfrc522_2.TxModeReg, 0x01);
  mfrc522_2.PCD_WriteRegister(mfrc522_2.RxModeReg, 0x01);
  // Reset ModWidthReg
  mfrc522_2.PCD_WriteRegister(mfrc522_2.ModWidthReg, 0x26);

  MFRC522::StatusCode result = mfrc522_2.PICC_RequestA(bufferATQA, &bufferSize);

  if(result == mfrc522_2.STATUS_OK){
    if ( ! mfrc522_2.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue   
      
      return false;
    }
    _rfid_error_counter2 = 0;
    _tag_found2 = true;        
  }
  
  rfid_tag_present2 = _tag_found;
  
}

void setup() {
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init(SS_PIN, RST_PIN);                                              // Init MFRC522 card
  mfrc522_2.PCD_Init(SS_PIN2, RST_PIN);  
  mfrc522.PCD_DumpVersionToSerial();
  mfrc522_2.PCD_DumpVersionToSerial();
  Serial.println("Aproach card"); 

}

void loop() {
  // put your main code here, to run repeatedly:
  checkTag();

  // rising edge
  if (rfid_tag_present && !rfid_tag_present_prev){
    Serial.println("Tag found");
  }
  
  // falling edge
  if (!rfid_tag_present2 && rfid_tag_present_prev2){
    Serial.println("Tag gone");
  }
}
