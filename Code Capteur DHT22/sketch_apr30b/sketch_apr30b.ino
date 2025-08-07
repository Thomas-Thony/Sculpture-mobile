#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  
  // Initialise la capteur DHT11
  dht.begin();
}
void loop() {
  // Recupere la temperature et l'humidite du capteur et l'affiche
  // sur le moniteur serie
  Serial.println("Temperature = " + String(dht.readTemperature())+" °C");
  Serial.println("Humidite = " + String(dht.readHumidity())+" %");
  delay(500);
}