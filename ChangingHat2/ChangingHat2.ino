#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          8          // Configurable, see typical pin layout above

#define SS_PIN2          10          // Configurable, see typical pin layout above


MFRC522 mfrc522(SS_PIN, RST_PIN);  
MFRC522 mfrc522_2(SS_PIN2, RST_PIN);  

#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();


#define buttonPin 2
#define pwrLED 3
#define redLED 4
#define greenLED 5
#define blueLED 6
#define intervalLED 1000
#define intervalNFC 1500

int color = 0;
unsigned long timerScore = 0;
unsigned long timerLED = 0;
int ledState = 0;
int nfcStart = 0;
int nfcNumber = 0;
int score = 0;


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
  mfrc522_2.PCD_WriteRegister(mfrc522_2.TxModeReg, 0x00);
  mfrc522_2.PCD_WriteRegister(mfrc522_2.RxModeReg, 0x00);
  // Reset ModWidthReg
  mfrc522_2.PCD_WriteRegister(mfrc522_2.ModWidthReg, 0x26);

  MFRC522::StatusCode result = mfrc522_2.PICC_RequestA(bufferATQA, &bufferSize);

  if(result == mfrc522_2.STATUS_OK){
    if ( ! mfrc522_2.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue   
      Serial.println("no pudo leer");
      return false;
    }
    _rfid_error_counter2 = 0;
    _tag_found2 = true;        
  }
  
  rfid_tag_present2 = _tag_found2;
  
}

void shutOff(){
  pinMode(pwrLED, INPUT);
  pinMode(greenLED, INPUT);
  pinMode(blueLED, INPUT);
  pinMode(redLED, INPUT);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  mfrc522_2.PCD_Init();  
  Serial.println("Aproach card");
  pinMode(buttonPin, INPUT);
  matrix.begin(0x70);
}

void loop() {
  
  checkTag();
  checkTag2();
  if(rfid_tag_present && !rfid_tag_present_prev){
    Serial.println("0 leyo");
    nfcNumber =2;
    if (nfcStart == 0){
      nfcStart = 1;
    }
    if (nfcNumber == 2){
      timerScore = millis();
    }
  }
    if(rfid_tag_present2 && !rfid_tag_present_prev2){
    Serial.println("1 leyo");
    nfcNumber =2;
    if (nfcStart == 0){
      nfcStart = 1;
    }
    if (nfcNumber == 2){
      timerScore = millis();
    }
    }

  if (nfcNumber == 0){
    matrix.print(0, DEC);
     matrix.writeDisplay();
     shutOff();
  }

  else if (nfcNumber == 1){
    matrix.print(score, DEC);
     matrix.writeDisplay();
     int status = digitalRead(buttonPin);
      if(status == HIGH){
        color ++;
        if (color == 6) {color = 0;}
      }
      switch(color){
        case 0:
        case 1:
          //blanco
          pinMode(pwrLED, OUTPUT);
          pinMode(greenLED, OUTPUT);
          pinMode(blueLED, OUTPUT);
          pinMode(redLED, INPUT);
          digitalWrite(pwrLED,HIGH);
          digitalWrite(greenLED, LOW);
          digitalWrite(blueLED, LOW);
          break;
          
        case 2:
        case 3:
          //ambar
          Serial.println("ambar");
          pinMode(pwrLED, OUTPUT);
          pinMode(greenLED, INPUT);
          pinMode(blueLED, OUTPUT);
          pinMode(redLED, OUTPUT);
          digitalWrite(pwrLED,HIGH);
          digitalWrite(redLED, LOW);
          digitalWrite(blueLED, LOW);
          break;
          
        case 4:
        case 5:
          //blanco parpadeo
          Serial.println("blanco parpadeo");
          if (millis()-timerLED > intervalLED){
            timerLED = millis();
            if (ledState == 0){
              ledState = 1;
              pinMode(pwrLED, OUTPUT);
              pinMode(greenLED, OUTPUT);
              pinMode(blueLED, OUTPUT);
              pinMode(redLED, INPUT);
              digitalWrite(pwrLED,HIGH);
              digitalWrite(greenLED, LOW);
              digitalWrite(blueLED, LOW);
            }
            else{
              ledState = 0;
              pinMode(pwrLED, INPUT);
              pinMode(greenLED, INPUT);
              pinMode(blueLED, INPUT);
              pinMode(redLED, INPUT);
            }
          }
          break;
      }
  }
  
  else if (nfcNumber == 2){
    Serial.println(millis());
    if (timerScore +2500 <= millis()){
      timerScore = millis();
      score ++;
       matrix.print(score, DEC);
    }
   
     matrix.writeDisplay();
      int status = digitalRead(buttonPin);
      if(status == HIGH){
        color ++;
        if (color == 6) {color = 0;}
      }
      switch(color){
        case 0:
        case 1:
          //blanco
          pinMode(pwrLED, OUTPUT);
          pinMode(greenLED, OUTPUT);
          pinMode(blueLED, OUTPUT);
          pinMode(redLED, INPUT);
          digitalWrite(pwrLED,HIGH);
          digitalWrite(greenLED, LOW);
          digitalWrite(blueLED, LOW);
          break;
          
        case 2:
        case 3:
          //ambar
          Serial.println("ambar");
          pinMode(pwrLED, OUTPUT);
          pinMode(greenLED, INPUT);
          pinMode(blueLED, OUTPUT);
          pinMode(redLED, OUTPUT);
          digitalWrite(pwrLED,HIGH);
          digitalWrite(redLED, LOW);
          digitalWrite(blueLED, LOW);
          break;
          
        case 4:
        case 5:
          //blanco parpadeo
          Serial.println("blanco parpadeo");
          if (millis()-timerLED > intervalLED){
            timerLED = millis();
            if (ledState == 0){
              ledState = 1;
              pinMode(pwrLED, OUTPUT);
              pinMode(greenLED, OUTPUT);
              pinMode(blueLED, OUTPUT);
              pinMode(redLED, INPUT);
              digitalWrite(pwrLED,HIGH);
              digitalWrite(greenLED, LOW);
              digitalWrite(blueLED, LOW);
            }
            else{
              ledState = 0;
              pinMode(pwrLED, INPUT);
              pinMode(greenLED, INPUT);
              pinMode(blueLED, INPUT);
              pinMode(redLED, INPUT);
            }
          }
          break;
      }
  }
  
  
   if(!rfid_tag_present && rfid_tag_present_prev) {
     Serial.println("down 0");
     nfcNumber =0;
     if (nfcStart == 1){
      nfcStart = 0;
    }
  
   }
   if(!rfid_tag_present2 && rfid_tag_present_prev2) {
    Serial.println("down 1");
    nfcNumber =0;
    if (nfcStart == 2){
      nfcStart = 0;
    }
   }
}
