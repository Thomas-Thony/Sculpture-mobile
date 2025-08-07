#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>

//Importation des librairies

#include "rgb_lcd.h"
#include "Wire.h"
#include <RTClib.h>
#include "DHT.h"
#include "Ultrasonic.h"

#define DHTPIN 2
#define DHTTYPE DHT22
#define BACKLIGHT_PIN 13
DHT dht(DHTPIN, DHTTYPE);
RTC_PCF8523 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Déclratation des variables 
const int colorR = 0;
const int colorG = 80;
const int colorB = 150;
const char * daysOfTheWeek[] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const int trigPin = 8; // Trigger (emission) 
const int echoPin = 9; // Echo (réception) 
long duree; // durée de l'echo 
int distance; // distance 


void setup() {
  //Lancement des modules (RTC, Ecran et capteur DHT22)
  dht.begin();
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("Test 1");
  if (! rtc.begin()){
  Serial.println("RTC introuvable");
  while (true);
  delay(500);
  }
  Serial.println("Fin Test 1");
  delay(500);
  Serial.println("Ajustement de l'heure en cours...");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // <<-- mettre ici l'heure exacte
  delay(5000);
  if (rtc.initialized()){
    Serial.println("RTC initialisee");
    delay(1000);
  }
  else{
    Serial.println("RTC non initialisee");
    delay(1000);
  }
    Serial.println("Fin ajustement de l'heure");
    delay(1000);
    lcd.clear();
}


void loop() {

   //Capteur Ultra-son
   digitalWrite(trigPin, LOW); 
   delayMicroseconds(5); 
   digitalWrite(trigPin, HIGH); 
   delayMicroseconds(10); 
   digitalWrite(trigPin, LOW); 

   // Écoute de l'écho 
   duree = pulseIn(echoPin, HIGH); 

   // Calcul de la distance 
   distance = duree*0.034/2; 

   // Affichage de la distance dans le Moniteur Série 
   Serial.print("Distance : "); 
   Serial.print(distance); 
   Serial.println("cm"); 
   delay(1000);
 
  if(distance <= 30){
  //Position du curseur sur l'écran
  lcd.setCursor(0, 0);
  lcd.display();
  
  //Application du module RTC
  DateTime now = rtc.now();
  delay(100);  
  lcd.print(now.day(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print('/');
  lcd.print(now.year(), DEC);
  lcd.print(' ');
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  delay(3000);

  //Application du capteur DHT22
  lcd.clear();
  lcd.print("Temps:" + String(dht.readTemperature())+"C");
  delay(3000);
  lcd.clear();
  lcd.println("Humidite: " + String(dht.readHumidity())+"%");
  delay(3000);
  lcd.clear();
  }
  else{
    lcd.noDisplay();
    lcd.noBacklight();
  }
}