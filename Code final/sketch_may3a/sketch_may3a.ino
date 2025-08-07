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
rgb_lcd lcd;


//Déclratation des variables 
const int colorR = 0;
const int colorG = 80;
const int colorB = 150;
const char * daysOfTheWeek[] = {"Dimanche", "Lundi", "Mardi", "Mercredi", "Jeudi", "Vendredi", "Samedi"};
const int trigPin = 8; // Trigger (emission) 
const int echoPin = 9; // Echo (réception) 
long duree;
int distance; 
boolean buttonWasUp = true;
boolean ledEnabled = false;

//Serial => Logs de débogages (Privé)
//lcd => Données à afficher sur l'écran (Publique) 

void setup() {
  //Lancement des modules (RTC, Ecran et capteur DHT22)
  dht.begin();
  //lcd.createChar(1, smile);
  pinMode(7, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);

  //Lancement du module RTC
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
float val_temperature[3] = {14, 15, 30}; 
switch(val_temperature){
  default: {
  bool buttonIsUp = digitalRead(7);
  //Position du curseur sur l'écran
  lcd.setCursor(0, 0);
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

  if(distance <= 40){
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
  delay(1500);

  //Application du capteur DHT22 et de l'écran
  lcd.clear();
  lcd.print("Temps:" + String(dht.readTemperature())+"C");
  delay(1500);
  lcd.clear();
  lcd.println("Humidite: " + String(dht.readHumidity())+"%");
  delay(1500);    
  lcd.clear();
  }
  else {
  lcd.noDisplay();
  }
 }
  case(val_temperature >= 30):{
    lcd.print("Attention Canicule !");
    break;
  }
  case(val_temperature = 15):{
  lcd.print("Température Ambainte");
    break; 
  }
    

  case(val_temperature <= 14):{
    lcd.print("Journée froide !");
    break;
    }
  }
}