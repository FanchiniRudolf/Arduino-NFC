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

long autoTime = 0;


int modeState = 0;
int status = 1;
unsigned long timer = 0;
long selector = 0;

bool rfid_tag_present_prev = false;
bool rfid_tag_present = false;
int _rfid_error_counter = 0;
bool _tag_found = false;


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
  mfrc522.PCD_WriteRegister(mfrc522.TxModeReg, 0x00);
  mfrc522.PCD_WriteRegister(mfrc522.RxModeReg, 0x00);
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

void manualMode(){
  shutOff();

  
  if (timer+5000<= millis()){
  selector =random(1, 6);
  timer = millis();
  }
  switch (selector){
    case 1:
      turnRed();
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed");
      }
      
       break;
       
      case 2:
      turnGreen();
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed");
      }
      break;
      
      case 3:
      turnBlue();
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed"); 
      }
      break;
      
      case 4:
      turnWhite();
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed");
      }
       break;
       
      case 5:
      turnYellow();
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed");
      }
       break;
       
       
  }
}

void autoMode(){
  shutOff();

  if (timer+autoTime<= millis()){
  selector =random(1, 6);
  timer = millis();
  }
  switch (selector){
    case 1:
      turnRed();
      autoTime = 1000;
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed");
      }
       break;
       
      case 2:
      turnGreen();
      autoTime = 3000;
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed");
      }
      break;
      
      case 3:
      turnBlue();
      autoTime = 3000;
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed"); 
      }
      break;
      
      case 4:
      turnWhite();
      autoTime = 3000;
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed");
      }
       break;
       
      case 5:
      turnYellow();
      autoTime = 1000;
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        Serial.println("boton pressed");
      }
       break;
       
       
  }
}



void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
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

  checkTag();
  
  // rising edge
  if(rfid_tag_present && rfid_tag_present_prev){
    if( modeState == 0){
  modeState = 3;
 }   }

  if (modeState == 3 || modeState == 1 || modeState == 2){ 
      status = digitalRead(autoButton);
      if (status == 0){
        modeState = 1;
        timer = 0;
      }
      status = digitalRead(manualButton);
      if (status == 0){
        modeState = 2;
        timer = millis();
        selector =random(1, 6);
        
      }
  switch(modeState){
        case 0:
          shutOff();
          break;
          
        case 1:
        autoMode();
          break;
          
        case 2:
          manualMode();
          break;
          
        case 3:
         turnAll();
          break;
      }
       
  }
  
  // falling edge
  if (!rfid_tag_present && rfid_tag_present_prev){
    Serial.println("Tag gone");
    modeState =0;
    shutOff();
  }
}
