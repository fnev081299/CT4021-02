int rpin = 7; // Red
int gpin = 6; // Blue
int bpin = 5; // Green

unsigned long time;

void setup() {
  // put your setup code here, to run once:
  pinMode(rpin, OUTPUT);
  pinMode(gpin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(rpin, HIGH);
  Serial.print("time: ");
  time = millis();
  Serial.println(time);
  delay(500);
  if(time >= 15000) {
    Serial.print("Timer has ended");
    digitalWrite(rpin, LOW);
  } else;
  digitalWrite(rpin, LOW);
  delay(500); 
}
