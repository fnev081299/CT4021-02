unsigned long time;
long elapsed = 0;

// int rpin = 7;

void setup() {
  // put your setup code here, to run once:
  // pinMode(rpin, OUTPUT);

  Serial.print(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  time = millis();
  Serial.print(checkTime());
}

int checkTime(){
  elapsed = millis() - time;
  return elapsed;
}
