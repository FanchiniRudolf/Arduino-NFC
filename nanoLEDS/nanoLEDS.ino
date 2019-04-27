#include <SPI.h>


#define pwrLED 3
#define redLED 4
#define greenLED 5
#define blueLED 6

#define intervalLED 1000


void shutOff(){
  pinMode(pwrLED, INPUT);
  pinMode(greenLED, INPUT);
  pinMode(blueLED, INPUT);
  pinMode(redLED, INPUT);
}

unsigned long timerScore = 0;
unsigned long timerLED = 0;
int ledState = 0;
int color = -1;




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();
  timerScore = millis();
  
}
 
void loop() {
  // put your main code here, to run repeatedly:
    
  if (timerScore  + 3000 <= millis()){
        timerScore = millis();
        color ++;
        Serial.println(color);
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
