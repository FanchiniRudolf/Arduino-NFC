#define buttonPin 5

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int status = digitalRead(buttonPin);
  if(status == HIGH){
    pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);
    digitalWrite(2,HIGH);
    digitalWrite(4,LOW);
  }
  else{
    pinMode(2, INPUT);
    pinMode(4,INPUT);
  }
  delay(1500);
}
