const int pinLaser = 2; // výstupní pin laserového modulu
const int pinPrijimac = 3; // vstupní pin přijímače
const int LED = 4; // výstupní pin LED diody
unsigned long casDetekce = 0; // proměnná pro detekci času
bool ledStav = false; // nastavuje aby mohla být LED detekována při dalším spuštění

#include <LiquidCrystal_I2C.h>  // knihovna pro LCD displej
LiquidCrystal_I2C lcd(0x27,16,2);  


void setup() {
  pinMode(pinLaser, OUTPUT); // nastavení laser pinu do výstupního módu
  pinMode(pinPrijimac, INPUT); // nastavení LED pinu do vstupního módu
  pinMode(LED, OUTPUT); // nastavení LED pinu do výstupního módu
  digitalWrite(pinLaser, HIGH); // Neustálé světlo laseru
  Serial.begin(9600); // sériová komunikace mezi arduinem a počítačem

  lcd.init(); // nastavení LCD displeje
  lcd.clear();
  lcd.backlight();
}

void loop() {
  int value = digitalRead(pinPrijimac); // Přijímač dává 1 nebo 0
  Serial.println(value); 
  delay(1000); // 1000ms
  if (digitalRead(LED) == LOW && !ledStav){ // kontroluje jestli je LED poprvé zapnuta
    casDetekce = millis(); // začíná časovač
    ledStav = true;  
  }
  if (value == LOW){ // kontroluje jestli přijímač detukuje laser
    unsigned long finalcas = millis() - casDetekce; // vypočítá čas 
    Serial.println("Finální čas: " + String(finalcas) + " ms"); // 
    float x = 13000.0 / (finalcas); //vypočítání rychlosti s nastavenou délkou
    lcd.clear(); // nastavení displeje
    lcd.setCursor(0,0); 
    lcd.print("Cas: " + String(finalcas) + " ms"); 
    lcd.setCursor(0,1);  
    lcd.print("Rychl: " + String(x) + " cm/s"); 
    ledStav = false; 
      }
    }
