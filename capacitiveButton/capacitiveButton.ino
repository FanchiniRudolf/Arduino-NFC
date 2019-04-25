#define ctsPin 8 // Pin for capactitive touch sensor
int ledPin = 5 ; // pin for the LED
 
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
  pinMode(ctsPin, INPUT);
}
 
void loop() {
  int ctsValue = digitalRead(ctsPin);
  if (ctsValue == HIGH){
    digitalWrite(ledPin, HIGH);
    Serial.println("TOUCHED");
  }
  else{
    digitalWrite(ledPin,LOW);
    Serial.println("not touched");
  } 
  delay(500);
  
}