#include <SPI.h>
#define pwrLED 8

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();
  pinMode(pwrLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("jalo");
  digitalWrite(pwrLED, HIGH);
  delay(500);
  digitalWrite(pwrLED, LOW);
  delay(500);
  
}
