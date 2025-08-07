#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int delaytime = 200;

String msgs1[]= {"A promotion is","You will soon","Laughter is the","Live long and", "Laugh hard and", "Eat well and", "A creative ","Someone", "A merry heart","Seize the day.", "Carpe diem.", "Prince Charming"};
String msgs2[] = {"coming soon.","be happy.","best medicine.","prosper.", "laugh often.", "make merry.", "mind is yours.","loves you.","is good.","", "", "is coming to u."};

byte bigHeart[8] = {
    0b00000,
    0b01010,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b00100,
    0b00000
};

byte smallHeart[8] = {
    0b00000,
    0b00000,
    0b01010,
    0b01110,
    0b00100,
    0b00000,
    0b00000,
    0b00000
};

void setup()
{
  lcd.begin(16, 2);
  #if 1
  lcd.createChar(0, bigHeart);
  lcd.createChar(1, smallHeart);
  #endif
  randomSeed(analogRead(A0));
}

void loop()
{
  if(digitalRead(4) == 1)
  {
    delay(10);
    if(digitalRead(4) == 1)
    {
      lcd.setRGB(100, 100, 0);
     int randomNum = random(0, 12);
     lcd.clear();
     lcd.setCursor(1, 0);
     lcd.print(msgs1[randomNum]);
     lcd.setCursor(1, 1);
     lcd.print(msgs2[randomNum]);
     delay(3000);
    }
  }
  else
  {
    openning();
  }    
}

void openning()
{
  lcd.setRGB(25, 10, 25);
  lcd.setCursor(1, 0);
  lcd.print("Lucky Dumpling");
  lcd.setCursor(1, 1);
  lcd.print("press to check");
  bouncing(15,1);
}

void bouncing(int x, int y)
{
    lcd.setCursor(x, y);
    lcd.write((unsigned char)0);
    delay(delaytime);
    lcd.setCursor(x, y);
    lcd.write((unsigned char)1);
    delay(delaytime);
}
