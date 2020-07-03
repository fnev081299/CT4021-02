int switchPin = 8;
boolean switchState=false;
int bState=0;

void setup() {
  pinMode(switchPin, INPUT);
}

void loop() {
  bState=digitalRead(switchState);

  if(bState==HIGH){
    if(bState==false)
      bState=true;
    else
      bState=false;
  }

  if(bState==true){
    Serial.print("hi");
  }else{
    Serial.print("low");
  }
    delay(1000);
}
