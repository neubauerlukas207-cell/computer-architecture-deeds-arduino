#include "Native_LiquidCrystal.h"

/* Definice komunikacnich pinu. Zde je potreba dat pozor na datove piny, protoze UnoArduSim
ma pouze jedno okenko pro nejnizsi dat. pin (DB4) a potom bere, ze dalsi tri nasledujici piny jsou DB5, DB6 a DB7.
   Take je mozne vynechat pin R/W - coz delam, protože muj realny displej ho ma natvrdo na GND.
*/
#define RS_PIN   7
#define EN_PIN   6
#define D4_PIN   2
#define D5_PIN   3
#define D6_PIN   4
#define D7_PIN   5

/* Instance lcd displeje, podle toho jakou si vyberu knihovnu */
Native_LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

// Funkce pro testování prvočíselnosti
bool isPrime(int num) {
  if (num <= 1) return false;  // 1 není prvočíslo
  if (num == 2) return true;   // 2 je prvočíslo
  if (num % 2 == 0) return false; // žádné sudé číslo (kromě 2) není prvočíslo
  for (int i = 3; i * i <= num; i += 2) {
    if (num % i == 0) return false; // pokud je dělitel, není prvočíslo
  }
  return true;
}

void setup() {
  /* Inicializace displeje */
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Zadejte cislo:");
  
  /* Inicializace sériového monitoru */
  Serial.begin(9600);
  Serial.println("Zadejte cislo mezi 2 a 10000:");
}

void loop() {
  if (Serial.available()) {
    // Načítání čísla
    int num = Serial.parseInt();
    
    // Ověření, zda číslo je v požadovaném rozsahu
    if (num < 2 || num > 10000) {
      Serial.println("Cislo neni v rozsahu 2-10000.");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Cislo mimo rozsah");
      return;
    }

    // Měření času
    unsigned long startTime = millis();
    
    // Testování prvočíselnosti
    bool prime = isPrime(num);

    unsigned long endTime = millis();
    unsigned long duration = endTime - startTime;

    // Zobrazení výsledku na sériovém monitoru
    Serial.print("Cislo: ");
    Serial.println(num);
    if (prime) {
      Serial.println("Je to prvocislo.");
    } else {
      Serial.println("Neni to prvocislo.");
    }
    Serial.print("Cas pro vypocet: ");
    Serial.print(duration);
    Serial.println(" ms");

    // Zobrazení výsledku na LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cislo: ");
    lcd.print(num);
    
    lcd.setCursor(0, 1);
    if (prime) {
      lcd.print("Je to prvocislo.");
    } else {
      lcd.print("Neni to prvocislo.");
    }
    
    lcd.setCursor(0, 2);
    lcd.print("Cas: ");
    lcd.print(duration);
    lcd.print(" ms");

    delay(3000); // Pauza před zadáním nového čísla
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Zadejte cislo:");
    Serial.println("Zadejte cislo mezi 2 a 10000:");
  }
}
