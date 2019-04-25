#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9           // Configurable, see typical pin layout above
#define SS_PIN          10          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  


#define blueLED 4
#define redLED 2
#define greenLED 3
#define whiteLED 6
#define yellowLED 5

int blinks = 4;
int blinkState = blinks;
int seriesState = 1;
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




void setup() {
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  Serial.println("Aproach card");
  pinMode(redLED, INPUT);
  pinMode(greenLED, INPUT);
  pinMode(blueLED, INPUT);
  pinMode(yellowLED, INPUT);
  pinMode(whiteLED, INPUT);
  timer = millis();
}

void loop() {

  //checkTag();
  
  // rising edge
  /*if(rfid_tag_present && rfid_tag_present_prev){
    if( modeState == 0){
  modeState = 3;
 }   }
      checkButtons();*/
  if (timer + 2000 <= millis() && seriesState == 0){
    timer = millis();
    shutOff();
    modeState ++;
  switch(modeState){
         case 1:
         turnAll();
          break;
        
        case 2:
          turnRed();
          break;
          
        case 3:
        turnGreen();
         break;
          
        case 4:
          turnBlue();
         break;
          
        case 5:
         turnYellow();
          break;
          
        case 6:
         turnWhite();
          break;
          
        case 7:
         shutOff();
         modeState = 0;
         seriesState = 1;
          break;
      }
  }
if (timer + 300 <= millis() && seriesState == 1){
  //encender tira
  timer = millis();
  shutOff();
  blinkState --;
  Serial.println(modeState);
  Serial.print(blinkState);
    switch(modeState){
        
        case 0:
        if (blinkState%2==1){
          turnRed();
        }else if (blinkState%2==0 && blinkState != 0){
          shutOff;
        }else if (blinkState == 0){
          blinkState = blinks;
          modeState ++;
        }
          break;
          
        case 1:
        if (blinkState%2==1){
          turnGreen();
        }else if (blinkState%2==0 && blinkState != 0){
          shutOff;
        }else if (blinkState== 0){
          blinkState = blinks;
          modeState ++;
        }
          break;          
        case 2:
          if (blinkState%2==1){
          turnBlue();
        }else if (blinkState%2==0 && blinkState != 0){
          shutOff;
        }else if (blinkState== 0){
          blinkState = blinks;
          modeState ++;
        }
          break;
          
        case 3:
         if (blinkState%2==1){
          turnYellow();
        }else if (blinkState%2==0 && blinkState != 0){
          shutOff;
        }else if (blinkState == 0){
          blinkState = blinks;
          modeState ++;
        }
          break;
          
          
        case 4:
         if (blinkState%2==1){
          turnWhite();
        }else if (blinkState%2==0 && blinkState != 0){
          shutOff;
        }else if (blinkState== 0){
          blinkState = blinks;
          modeState ++;
        }
          break;
          
          
        case 5:
         shutOff();
         modeState = 0;
         seriesState = 2;
          break;
      }
}
  
  
  // falling edge
  /*if (!rfid_tag_present && rfid_tag_present_prev){
    Serial.println("Tag gone");
    modeState =0;
    shutOff();
  }*/
}
