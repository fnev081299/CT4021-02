#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#define beep_pin 3

LiquidCrystal lcd(1, 2, 4, 5, 6, 7);

void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication

  pinMode(beep_pin, OUTPUT);
  digitalWrite(beep_pin, LOW);

  lcd.begin(16, 2);
  lcd.setCursor(3, 1);
  lcd.print("Welcome!!");
  lcd.setCursor(0, 0);
  lcd.print("Circuit is Ready");
  delay(1500);
  lcd.clear();
  
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Place on reader...");
  Serial.println();

}
void loop() 
{
  digitalWrite(beep_pin, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Place Card On Reader");
  lcd.setCursor(0, 1);
  lcd.print("Reading...");
  delay(3000);
  
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
  //Show UID on serial monitor
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
  Serial.print("Tag Access : ");
  content.toUpperCase();
  if (content.substring(1) == "04 3C CA 83") //change here the UID of the card/cards that you want to give access
  {
    digitalWrite(beep_pin, HIGH);
    delay(200);
    digitalWrite(beep_pin, LOW);
    delay(200);
    lcd.setCursor(0, 0);
    lcd.print("ID: ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Autherised");
    Serial.println("Authorized");
    delay(3000);
  }
 
 else   {
    digitalWrite(beep_pin, HIGH);
    delay(200);
    lcd.setCursor(0, 0);
    lcd.print("ID: ");
    lcd.print(content.substring(1));
    lcd.setCursor(0, 1);
    lcd.print("Denied");
    Serial.println(" Denied");
    delay(3000);
  }
} 
