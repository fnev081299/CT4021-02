int inpin = 2;
const int speaker = 3;
int sState = 0;
int prevsState = 0;

void setup()
{
  pinMode(inpin, INPUT);
}

void loop()
{
  sState = digitalRead(inpin);
  if (sState != prevsState) {
    if(sState == LOW){
      tone(speaker, 494, 500);
    } else {
      Serial.print("lol");
      }
  }
  Serial.print(sState);
  prevsState = sState;
}
