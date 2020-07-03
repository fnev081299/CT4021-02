int inPin = 2;   // the number of the input pin
int reading;     // the current reading from the input pin
int GreenLedPin = 6;  // the number of the Green LED output pin
int RedLedPin = 5;    // the number of the Red LED output pin
const int SpeakerPin = 3; // the number of the Speaker/Buzzer pin

void setup(){
  pinMode (inPin, INPUT);
  pinMode (GreenLedPin, OUTPUT);
  pinMode (RedLedPin, OUTPUT);
  Serial.begin(9600);
}

void loop () {
  reading = digitalRead(inPin);
  if (reading == 1) {
    digitalWrite(RedLedPin, HIGH);   // if tilted, turn the red LED ON
    digitalWrite(GreenLedPin, LOW);
    tone(SpeakerPin, 494, 500);      // if tilted, turn the Speaker ON
   delay(500);
   
  } else {
    digitalWrite(RedLedPin, LOW);
    digitalWrite(GreenLedPin, HIGH);    // if not tilted, turn the green LED ON
  }
  Serial.println(reading); // not really needed

  delay(200);   // pause 200 milliseconds between readings
}
