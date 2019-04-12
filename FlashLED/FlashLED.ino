#define buttonPin 2
#define pwrLED 3
#define redLED 4
#define greenLED 5
#define blueLED 6
#define interval 1000

int color = 0;
unsigned long timer = 0;
int ledState = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int status = digitalRead(buttonPin);
  if(status == HIGH){
    color ++;
    if (color == 6) {color = 0;}
  }
  switch(color){
    case 0:
    case 1:
      //blanco
      Serial.println("blanco");
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
      if (millis()-timer > interval){
        timer = millis();
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
