int rpin = 7;
int gpin = 6;
int bpin = 5;

void setup() {
  pinMode(rpin, OUTPUT);
  pinMode(gpin, OUTPUT);
  pinMode(bpin, OUTPUT);
}

void loop() {
  setColor(255, 0, 0);
  delay(1000);
  setColor(0, 255, 0);
  delay(1000);
  setColor(0, 0, 255);
  delay(1000);

}

void setColor(int rval, int gval, int bval){
  analogWrite(rpin, rval);
  analogWrite(bpin, bval);
  analogWrite(gpin, gval);
}
