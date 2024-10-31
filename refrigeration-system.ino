#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int sensorTempPin = A0;
const int sensorHumedadPin = A1;
const int ledRojo = 4;
const int buzzer = 6;

float temperatura = 0;
int humedad = 0;

void setup() {
  pinMode(ledRojo, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("TEMP  HUMED");
}

void loop() {
  temperatura = (analogRead(sensorTempPin) - 20.0) * (100.0 / (358.0 - 20.0));
  humedad = (analogRead(sensorHumedadPin) / 875.0) * 100.0;

  lcd.setCursor(0, 1);
  lcd.print(temperatura);
  lcd.print("C  ");
  lcd.print(humedad);
  lcd.print("%  ");

  if (temperatura < 0 || temperatura > 10 || humedad < 80 || humedad > 90) {
    digitalWrite(ledRojo, HIGH);
    tone(buzzer, 1000);
  } else {
    digitalWrite(ledRojo, LOW);
    noTone(buzzer);
  }

  delay(2000);
}