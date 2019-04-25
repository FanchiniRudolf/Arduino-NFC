#define pwrLED 8

void setup() {
  // put your setup code here, to run once:
pinMode(pwrLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(pwrLED,HIGH);
}
