int buzzer = 9;
int sensorPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9400);
  pinMode(sensorPin, INPUT);
  pinMode(buzzer, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(sensorPin);

  tone(buzzer, sensorValue);
  delay(50);
  Serial.println(sensorValue);
}
