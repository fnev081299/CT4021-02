float temp;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  temp = analogRead(A1);
  temp = (temp - .5) * 100;
  
  Serial.print("TEMP: ");
  Serial.print(temp);
  Serial.print("*C");
  Serial.println();
  delay(1000);
}
