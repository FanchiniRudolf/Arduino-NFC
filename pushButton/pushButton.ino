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
  pinMode(manualButton, INPUT_PULLUP);
  pinMode(autoButton, INPUT_PULLUP);
  pinMode(redLED, INPUT);
  pinMode(greenLED, INPUT);
  pinMode(blueLED, INPUT);
  pinMode(yellowLED, INPUT);
  pinMode(whiteLED, INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
      int status = digitalRead(autoButton);
      if (status == 0){
        pinMode(whiteLED, OUTPUT);
        digitalWrite(whiteLED, HIGH);
      }else{
        pinMode(whiteLED, INPUT);
      }
      
      
  
}
