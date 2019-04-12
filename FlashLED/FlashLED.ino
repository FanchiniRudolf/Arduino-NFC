void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  pinMode(2,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(2,HIGH);
  digitalWrite(4,LOW);
  delay(1500);
  pinMode(2, INPUT);
  pinMode(4,INPUT);
  delay(1500);
}
