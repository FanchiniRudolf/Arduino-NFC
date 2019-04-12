#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();


void setup() {
  // put your setup code here, to run once:
 #ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("7 Segment Backpack Test");
#endif
  matrix.begin(0x70);


}

void loop() {
  // put your main code here, to run repeatedly:
  
  matrix.print(500, DEC);
  matrix.writeDisplay();
}
