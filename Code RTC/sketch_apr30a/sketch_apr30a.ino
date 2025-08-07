#include "Wire.h"
#include "RTClib.h"

RTC_PCF8523 rtc;

const char * daysOfTheWeek[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {

  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("test1");
  if (! rtc.begin()) {
    Serial.println("RTC introuvable");
    while (true);
  }
  Serial.println("fin test1");

  Serial.println("ajustement de l'heure en cours...");
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // <<-- mettre ici l'heure exacte
  delay(5000);
  if (rtc.initialized()){
    Serial.println("RTC initialisee");
  }
  else{
    Serial.println("RTC non initialisee");
  }
  Serial.println("fin ajustement de l'heure");
}


void loop () {

  DateTime now = rtc.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

delay(3000);
}