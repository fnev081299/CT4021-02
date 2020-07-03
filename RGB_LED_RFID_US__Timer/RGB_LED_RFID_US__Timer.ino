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

bool ldrStatus;
bool d;

unsigned long time;
unsigned long timeElapsed;
bool bstatus =  false;

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

void setup() {
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);

  pinMode(rpin, OUTPUT);
  pinMode(gpin, OUTPUT);
  pinMode(bpin, OUTPUT);
  
  pinMode(ldrPin, INPUT);
}

void loop() {
  ldrStatus = LDRstatus();
  d = usDetect();
  
  if (ldrStatus = true and d == true) // check for light and mostion
  { 
    if (bstatus == false){
        bstatus= true;
        starttime();
    }
    if (checkTime() <= 20) // time less than 20 second
    {
      setColor(255,0,0);
      // scanRFID();
    }
    if (checkTime() >= 21) // time over 20 seconds
    {
        //buzzer();
        setColor(255,255,0);
        // scanRFID();
    }
    if (checkTime()>= 600) // time over 10 minutes
    {
        //alarm();
        setColor(255, 150, 300);
    } else {
        setColor(255, 0, 255);
        bstatus= false; 
    }
  }
  
} 

void scanRFID() {
        setColor(0, 255, 0); //ready to read
        
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) 
        {
          return;
        }
        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) 
        {
          return;
        }
        Serial.print("UID tag :");
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
        Serial.print("Message : ");
        content.toUpperCase();
        if (content.substring(1) == "04 3C CA 83")
        {
          setColor(0, 0, 255);
          tone(speaker, 500, 500);
          Serial.println("Authorized Access");
          Serial.println();
          delay(2000);
        } 
      else   {
          setColor(255, 0, 0);
          tone(speaker, 300, 250);
          Serial.println(" Access Denied");
          delay(2000);
      }
}

bool LDRstatus(){
  bool bldr = false;
  int ldrStatus = analogRead(ldrPin);
  if (ldrStatus >= 35){
    bldr = true;
    }
    return bldr;
}

bool usDetect(){
  float duration, distance;
  bool bdist = false;
  
  digitalWrite(trigpin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  
 duration = pulseIn(echopin, HIGH);
 distance = (duration/2) * 0.0344;
 
 if(distance <=40){
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
