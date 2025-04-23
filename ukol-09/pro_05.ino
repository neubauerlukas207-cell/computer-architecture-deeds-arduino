/* Program přijímá rozměry kvádru a, b, c ze sériové linky
   a vypočítá jeho objem. Po výpočtu umožní zadat nové rozměry.
*/

unsigned int a, b, c, objem;
byte stav = 0;

void setup() {
	Serial.begin(9600);
	delay(1000);
	Serial.println("Zadejte (rozmer a):");
}

void loop() {
	if (Serial.available()) {
		String vstup = Serial.readStringUntil('\n');
		vstup.trim(); // odstraní prázdné znaky a Enter

		if (vstup.length() == 0) return;

		int hodnota = vstup.toInt();

		if (hodnota == 0 && vstup != "0") {
			Serial.println("Neplatný vstup – zadejte celé číslo:");
			return;
		}

		if (stav == 0) {
			a = hodnota;
			Serial.println("Zadejte (rozmer b):");
			stav = 1;
		} else if (stav == 1) {
			b = hodnota;
			Serial.println("Zadejte (rozmer c):");
			stav = 2;
		} else if (stav == 2) {
			c = hodnota;
			objem = a * b * c;

			Serial.println("********************");
			Serial.print("Kvadr o rozmerech (");
			Serial.print(a); Serial.print(", ");
			Serial.print(b); Serial.print(", ");
			Serial.print(c); Serial.print(") má objem ");
			Serial.println(objem);
			Serial.println("Zadejte (rozmer a):");
			stav = 0;
		}
	}
}
