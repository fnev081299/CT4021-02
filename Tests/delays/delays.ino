int led = 6; // Pin 13 has an LED connected on most Arduino boards.

int rpin = 7; // Red
int gpin = 6; // Blue
int bpin = 5; // Green

unsigned long DELAY_TIME = 10000; // 10 sec
unsigned long delayStart = 0; // the time the delay started
bool delayRunning = false; // true if still waiting for delay to finish

const int speaker = 3; // Buzzer

void setup() {
  pinMode(led, OUTPUT);   // initialize the digital pin as an output.
  digitalWrite(led, HIGH); // turn led on

  // start delay
  delayStart = millis();
  delayRunning = true;
}

void loop() {
  // check if delay has timed out
  if (delayRunning && ((millis() - delayStart) >= DELAY_TIME)) {
    delayRunning = false; // finished delay -- single shot, once only
    setColor(255, 0, 0);
    tone(speaker, 300, 250);
  }
}


void setColor(int rval, int gval, int bval){
  analogWrite(rpin, rval);
  analogWrite(bpin, bval);
  analogWrite(gpin, gval);
}
