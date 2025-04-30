#include "Native_LiquidCrystal.h"
/* Definice komunikacnich pinu. Zde je potreba dat pozor na datove piny, protoze UnoArduSim
ma pouze jedno okenko pro nejnizsi dat. pin (DB4) a potom bere, ze dalsi tri nasledujici piny jsou DB5, DB6 a DB7.
   Take je mozne vynechat pin R/W - coz delam, protože muj realny displej ho ma natvrdo na GND.
*/
#include "Native_LiquidCrystal.h"

#define RS_PIN 7
#define EN_PIN 6
#define D4_PIN 2
#define D5_PIN 3
#define D6_PIN 4
#define D7_PIN 5

Native_LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

int A, B, C;

void setup() {
	Serial.begin(9600);
	lcd.begin(20, 4);

	while (true) {
		Serial.println("Zadejte (parametr A): ");
		A = readIntFromSerial();

		Serial.println("Zadejte (parametr B): ");
		B = readIntFromSerial();

		Serial.println("Zadejte (parametr C): ");
		C = readIntFromSerial();

		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("Rovnice:");
		lcd.setCursor(0, 1);
		lcd.print(A);
		lcd.print("*x^2");
		if (B >= 0) lcd.print("+");
		lcd.print(B);
		lcd.print("*x");
		if (C >= 0) lcd.print("+");
		lcd.print(C);
		lcd.print("=0");

		Serial.println("********************");
		Serial.println("Kvadraticka rovnice:");
		Serial.print(A);
		Serial.print("*x^2");
		if (B >= 0) Serial.print("+");
		Serial.print(B);
		Serial.print("*x");
		if (C >= 0) Serial.print("+");
		Serial.print(C);
		Serial.println("=0");

		int D = B * B - 4 * A * C;

		if (D < 0) {
			lcd.setCursor(0, 2);
			lcd.print("Nema reseni");
			Serial.println("Nema realne reseni");
		} else {
			int x1 = (-B + sqrt(D)) / (2 * A);
			int x2 = (-B - sqrt(D)) / (2 * A);
			lcd.setCursor(0, 2);
			lcd.print("x1="); lcd.print(x1);
			lcd.setCursor(0, 3);
			lcd.print("x2="); lcd.print(x2);
			Serial.println("Reseni:");
			Serial.print("x1="); Serial.print(x1);
			Serial.print(" x2="); Serial.println(x2);
		}

		Serial.println("********************\\n");
	}
}

int readIntFromSerial() {
	while (!Serial.available()) {	}
	return Serial.parseInt();
}

void loop() {
	// nevyužito
}
