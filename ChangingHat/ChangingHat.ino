#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  

#define buttonPin 2
#define pwrLED 3
#define redLED 4
#define greenLED 5
#define blueLED 6
#define intervalLED 1000
#define intervalNFC 1500

int color = 0;
unsigned long timerLED = 0;
unsigned long timerNFC = 0;
int ledState = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println("Aproach card");
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (millis()-timerNFC > intervalNFC){
    timerNFC = 0;
  if ( mfrc522.PICC_IsNewCardPresent()) {
    
    if ( mfrc522.PICC_ReadCardSerial()) {
     
      int status = digitalRead(buttonPin);
      if(status == HIGH){
        color ++;
        if (color == 6) {color = 0;}
      }
      switch(color){
        case 0:
        case 1:
          //blanco
          Serial.println("blanco");
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
  }else{
    ledState = 0;
    pinMode(pwrLED, INPUT);
    pinMode(greenLED, INPUT);
    pinMode(blueLED, INPUT);
    pinMode(redLED, INPUT);
}
  }
}
