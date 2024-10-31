#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

const int pirPin = 2;
const int ledVerde = 3;
const int ledRojo = 4;

int estadoPIR = 0;
int contador = 0;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRojo, OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Incidencia: 000");

  digitalWrite(ledVerde, LOW);
  digitalWrite(ledRojo, LOW);
}

void loop() {
  estadoPIR = digitalRead(pirPin);

  if (estadoPIR == LOW) {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledRojo, LOW);
    delay(200);
    digitalWrite(ledVerde, LOW);
    delay(200);
  } else { 
    digitalWrite(ledRojo, HIGH);
    digitalWrite(ledVerde, LOW);

    contador++;

    lcd.setCursor(0, 0);
    lcd.print("Incidencia:     ");
    lcd.setCursor(12, 0);
    lcd.print(contador);

    delay(5000);
  }
}