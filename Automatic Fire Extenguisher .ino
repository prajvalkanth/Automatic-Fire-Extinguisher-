#include <max6675.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#define Realy 7
int thermoDO = 6;
int thermoCS = 5;
int thermoCLK = 4;
double C;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
int vccPin = 3;
int gndPin = 2;

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// make a cute degree symbol
uint8_t degree[8]  = {140,146,146,140,128,128,128,128};

void setup() {
  Serial.begin(9600);
  // use Arduino pins 
  pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
  pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
  pinMode(Realy,OUTPUT);
  lcd.begin(16, 2);
  lcd.createChar(0, degree);

  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WELCOME");
  
  
  // go to line #1
  lcd.setCursor(0,1);
  lcd.print(thermocouple.readCelsius());
#if ARDUINO >= 100
  lcd.write((byte)0);
#else
  lcd.print(0, BYTE);
#endif
  lcd.print("C ");
  lcd.print(thermocouple.readFahrenheit());
#if ARDUINO >= 100
  lcd.write((byte)0);
#else
  lcd.print(0, BYTE);
#endif
  lcd.print('F');
  
  delay(1000);
  C = thermocouple.readCelsius();
  if (C>=50){
  digitalWrite(Realy,0);
}
else{
  digitalWrite(Realy,1);
}
}


