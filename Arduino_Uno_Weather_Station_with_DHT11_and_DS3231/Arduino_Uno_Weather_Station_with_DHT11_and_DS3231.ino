//Made By: Chris Minheere 
//16-07-2018
//Arduino Uno Weather Station with DHT11 and DS3231

#include "DHT.h"
#include <DS3231.h>
#include <LiquidCrystal.h>
#define DHTPIN 9   
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DS3231  rtc(SDA, SCL);

int analogInput = 0;
float vout = 0.0;
float vin = 0.0;
float R1 = 10000.0; // resistance of R1 (10K)
float R2 = 10000.0; // resistance of R2 (10K)
int value = 0;

byte termometru[8] = //icon for termometer
{
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
};

byte picatura[8] = //icon for water droplet
{
    B00100,
    B00100,
    B01010,
    B01010,
    B10001,
    B10001,
    B10001,
    B01110,
};

byte datum[8] = //icon for water droplet
{
    B10101,
    B11111,
    B11011,
    B10011,
    B11011,
    B11011,
    B10001,
    B11111,
};

byte klok[8] = 
{
    B00000,
    B01110,
    B11011,
    B11011,
    B11001,
    B11111,
    B01110,
    B00000,
};

byte batterij_00[8] = 
{
    B00110,
    B01111,
    B01001,
    B01001,
    B01001,
    B01001,
    B01001,
    B01111,
};

byte batterij_20[8] = 
{
    B00110,
    B01111,
    B01001,
    B01001,
    B01001,
    B01001,
    B01111,
    B01111,
};

byte batterij_40[8] = 
{
    B00110,
    B01111,
    B01001,
    B01001,
    B01001,
    B01111,
    B01111,
    B01111,
};

byte batterij_60[8] = 
{
    B00110,
    B01111,
    B01001,
    B01001,
    B01111,
    B01111,
    B01111,
    B01111,
};

byte batterij_80[8] = 
{
    B00110,
    B01111,
    B01001,
    B01111,
    B01111,
    B01111,
    B01111,
    B01111,
};

byte batterij_100[8] = 
{
    B00110,
    B01111,
    B01111,
    B01111,
    B01111,
    B01111,
    B01111,
    B01111,
};

byte stekker[8] = 
{
    B01010,
    B01010,
    B11111,
    B11111,
    B11111,
    B01110,
    B00100,
    B00100,
};


void setup() {
   
  pinMode(analogInput, INPUT);
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  dht.begin();
  lcd.createChar(1,termometru);
  lcd.createChar(2,picatura); 
  lcd.createChar(3,klok); 
  lcd.createChar(4,datum);
  lcd.createChar(5,stekker);

  rtc.begin();
}


   

void loop() {

  
   value = analogRead(analogInput);
   vout = (value * 5.0) / 1024.0; 
   vin = vout / (R2/(R1+R2)); 
   if (vin<0.09) {
      vin=0.0;
  } 

  //Serial.println(vin);
  float meting = vin;
  if(meting > 4.0){
    if(meting >= 9.0){
      lcd.createChar(5, batterij_100);  
    }
    if(meting < 9.0 && meting >= 8.5){
      lcd.createChar(5, batterij_80);  
    }
    if(meting < 8.5 && meting >= 8.0){
      lcd.createChar(5, batterij_60);  
    }
    if(meting < 8.0 && meting >= 7.5){
      lcd.createChar(5, batterij_40);  
    }
    if(meting < 7.5 && meting >= 7.0){
      lcd.createChar(5, batterij_20);  
    }
    if(meting < 7.0){
      lcd.createChar(5, batterij_00);  
    }
  }
  lcd.setCursor(15,0);
  //lcd.write(5);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
    }
  else {
  lcd.setCursor(1, 1);
  lcd.write(1);
  lcd.setCursor(3, 1);
  //correctie op sensorwaarde +1
    Serial.println("<Meting>");
     Serial.print("<Temperatuur__c>");
  Serial.print((int)t+1);
  Serial.print("</Temperatuur__c>");
  lcd.print((int)t+1);
  lcd.setCursor(5, 1);
  lcd.print((char)223); 
  Serial.print(" ");
  Serial.println("");
  lcd.print("C");
  lcd.print("");
  lcd.setCursor(10, 1);
  lcd.write(2);
  lcd.setCursor(12, 1);
  Serial.print("<Luchtvochtigheid__c>");
  Serial.print((int)h);
  Serial.print("</Luchtvochtigheid__c>");
  Serial.println(" ");
  lcd.print((int)h); 
  lcd.print("%");
 
 }
  lcd.setCursor(1,0);
  
  lcd.print(" ");
  lcd.write(4);
  lcd.print(" ");
  Serial.print("<Datum__c>");
  Serial.print(rtc.getDateStr());
   Serial.print("_");
  
  lcd.print(rtc.getDateStr());
  lcd.print("");
   String sTime = rtc.getTimeStr();
  sTime = sTime.substring(0,5);
  Serial.print(sTime);
  Serial.println("</Datum__c>");
  Serial.println("</Meting>");
  
  delay (4000);

  lcd.setCursor(1,0);
  lcd.print("   ");
  lcd.write(3);
  lcd.print(" ");
  sTime = sTime.substring(0,5);
  lcd.print(sTime);
  lcd.print("   ");
  delay (4000);


}


