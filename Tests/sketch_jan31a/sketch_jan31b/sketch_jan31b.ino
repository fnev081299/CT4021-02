int sensorPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9400);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue); // log value
}
