#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  

#define autoButton 2
#define manualButton 8
#define blueLED 5
#define redLED 3
#define greenLED 4
#define whiteLED 7
#define yellowLED 6

#define manualTime = 6000
#define redyellowTime 1000
#define othercolorsTime 3000

int modeState = 0;

void turnGreen(){
  pinMode(greenLED, OUTPUT);
  digitalWrite(greenLED, HIGH);
}

void turnBlue(){
  pinMode(blueLED, OUTPUT);
  digitalWrite(blueLED, HIGH);
}
void turnRed(){
  pinMode(redLED, OUTPUT);
  digitalWrite(redLED, HIGH);
}
void turnYellow(){
  pinMode(yellowLED, OUTPUT);
  digitalWrite(yellowLED, HIGH);
}
void turnWhite(){
  pinMode(whiteLED, OUTPUT);
  digitalWrite(whiteLED, HIGH);
}

void turnAll(){
  pinMode(redLED, OUTPUT);
        digitalWrite(redLED, HIGH);
         pinMode(greenLED, OUTPUT);
        digitalWrite(greenLED, HIGH);
         pinMode(blueLED, OUTPUT);
        digitalWrite(blueLED, HIGH);
         pinMode(yellowLED, OUTPUT);
        digitalWrite(yellowLED, HIGH);
         pinMode(whiteLED, OUTPUT);
        digitalWrite(whiteLED, HIGH);
}

void shutOff(){
  pinMode(redLED, INPUT);
          pinMode(greenLED, INPUT);
          pinMode(blueLED, INPUT);
          pinMode(yellowLED, INPUT);
          pinMode(whiteLED, INPUT);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println("Aproach card");
  pinMode(manualButton, INPUT_PULLUP);
  pinMode(autoButton, INPUT_PULLUP);
  pinMode(redLED, INPUT);
  pinMode(greenLED, INPUT);
  pinMode(blueLED, INPUT);
  pinMode(yellowLED, INPUT);
  pinMode(whiteLED, INPUT);
  
}

void loop() {
  
      switch(modeState){
        case 0:
          shutOff();
          break;
          
        case 1:
        turnRed();
          break;
          
        case 2:
          turnGreen();
          break;
          
        case 3:
         turnAll();
          break;
      }

      
  // put your main code here, to run repeatedly:
    if ( !mfrc522.PICC_IsNewCardPresent()) {
    modeState=0;
    return;
  }
  if ( !mfrc522.PICC_ReadCardSerial()) {
    modeState=0;
    return;
  }

 if( modeState == 0){
  modeState = 3;
 }
      int status = digitalRead(autoButton);
      if (status == 0){
        modeState = 1;
      }
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
      }

      switch(modeState){
        case 0:
          shutOff();
          break;
          
        case 1:
        turnRed();
          break;
          
        case 2:
          turnGreen();
          break;
          
        case 3:
         turnAll();
          break;
      }
  Serial.println("Helo");
   delay (1000);
  Serial.println("bye");
}
