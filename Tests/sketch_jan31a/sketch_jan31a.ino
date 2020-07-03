int btnPin = 2;
int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode (btnPin, INPUT);
  pinMode (ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(btnPin) == HIGH){
    Serial.println("Button Pressed");
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  
  delay(100);
}
