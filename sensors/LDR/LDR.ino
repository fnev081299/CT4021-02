const int ledPin = 6;

const int ldrPin = A0;

void setup() {

Serial.begin(9600);

pinMode(ledPin, OUTPUT);

pinMode(ldrPin, INPUT);

}

void loop() {

int ldrStatus = analogRead(ldrPin);

if (ldrStatus <= 20) {

digitalWrite(ledPin, HIGH);

Serial.print("Its too Dark, Turn on the LED : ");

Serial.println(ldrStatus);

} else {

digitalWrite(ledPin, LOW);

Serial.print("Its Light, Turn off the LED : ");

Serial.println(ldrStatus);

}

}
