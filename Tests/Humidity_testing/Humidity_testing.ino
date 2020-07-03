#include <DHT.h>

#define  DHTPIN 4
#define DHTTYPE DHT11

DHT dht (DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Test");

  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if(isnan(t) || isnan(h)){
    Serial.println("Failed to read");
  }
  else{
    Serial.print("humidity");
    Serial.println(h);
    Serial.println(" %\t");
    Serial.println(t);
    Serial.println(" *c");
    }

}
