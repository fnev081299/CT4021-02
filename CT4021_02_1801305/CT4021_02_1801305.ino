// libraries needed 
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
#define trigpin 2
#define echopin 4

int rpin = 7; // Red
int gpin = 6; // Blue
int bpin = 5; // Green

const int speaker = 3; // Buzzer
const int ldrPin = A0; // LDR

// to work out the time taken
unsigned long time;
unsigned long timeElapsed;

bool bstatus =  false; // to help start the timer only when there is light and a person infront of the object
bool ldrS; // if there is light

// light and US sensor
bool d;
bool l;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Creating an instance for the reader

void setup() {
  Serial.begin(9600);   // start serial communication
  SPI.begin();      // start SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("***Place card on reader***");
  Serial.println();
  
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(rpin, OUTPUT);
  pinMode(gpin, OUTPUT);
  pinMode(bpin, OUTPUT);
  
  pinMode(ldrPin, INPUT);
}

void loop() {
  // changes the values if needed by getting the returned values
  d = usDetect();
  l = ldrStatus();
  
  if (l == true and d == true) // check for light and mostion
    { 
    
    if (bstatus == false){
      bstatus = true;
      starttime();
      }
    if (checkTime() <= 10) // time less than 10 second
      {
       setColor(0,255, 0);
       scanRFID();
       Serial.println(checkTime());
        }
    if (checkTime() >= 11) // time over 10 seconds
      {
        tone(speaker, 300, 250);
        scanRFID();
        setColor(255,225,0);
        delay(500);
       }
    if (checkTime() >= 20) // time over 20 seconds
      {
        tone(speaker, 300, 250);
        setColor(255,0,0);
        delay(50);
       }
  } else {
      bstatus= false;  
      setColor(0, 0, 0);
      } 
} 

void scanRFID() {
        
        // Look for cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) 
        {
          return;
        }
        // Select the card
        if ( ! mfrc522.PICC_ReadCardSerial()) 
        {
          return;
        }
        Serial.print("Tag UID:");
        String content= "";
        byte letter;
        for (byte i = 0; i < mfrc522.uid.size; i++) 
        {
           Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
           Serial.print(mfrc522.uid.uidByte[i], HEX);
           content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
           content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        Serial.println();
        Serial.print("Tag Access : ");
        content.toUpperCase();
        if (content.substring(1) == "04 3C CA 83") // UID of card being used
        {
          setColor(0, 0, 255); // green
          tone(speaker, 500, 500); // high pitch for access
          Serial.println("Authorized");
          delay(10000);
        } 
      else   {
          setColor(255, 0, 0); // red
          tone(speaker, 300, 250); // low pitch for denied
          Serial.println("Denied");
          delay(2000);
      }
}

bool ldrStatus(){
  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus >= 20){
    ldrS = true;
  } else if (ldrStatus < 20) {
    ldrS = false;
  }
  return ldrS;
}

bool usDetect(){
  float duration, distance;
  bool bdist = false;
  
  //set trig pin to be clear:
  digitalWrite(trigpin, LOW);  
  delayMicroseconds(2);
  
  // generate ultrasonic wave:
  digitalWrite(trigpin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  //waits for pin to go high:
 duration = pulseIn(echopin, HIGH);
 // distance in centimeters:
 distance = (duration/2) * 0.0344; 

 // checks if the object is 50cm or closer to the device: 
 if(distance <=50){
  bdist = true;
  delay(500);
 } else {
  bdist = false;
  delay(500);  
 }
 return bdist;
}

void starttime(){
  time = millis() / 1000;
  }

int checkTime(){
  timeElapsed = 0;
  timeElapsed = (millis() /1000) - time;
  return timeElapsed;
}

void setColor(int rval, int gval, int bval){
  analogWrite(rpin, rval);
  analogWrite(bpin, bval);
  analogWrite(gpin, gval);
}
