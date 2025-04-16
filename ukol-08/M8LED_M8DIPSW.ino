// připravek M8LED na portu BC
// připravek M8DIPSW na portu D, piny 0,1 připojeny na piny 16,17 mikrokontroléru

int pinsOut[] = {10, 9, 8, 14, 13, 12, 11, 15};  // výstupní piny pro LED
int pinsIn[] = {16, 17, 2, 3, 4, 5, 6, 7};       // vstupní piny pro DIP přepínače

int position = 0;  // počáteční pozice LED

void setup() {
	for (int i = 0; i < 8; i++) {
		pinMode(pinsOut[i], OUTPUT);
		pinMode(pinsIn[i], INPUT);
	}
}

void loop() {
	// načtení směru z pinu 7 (osmý DIP)
	bool direction = digitalRead(pinsIn[7]);

	// načtení rychlosti z pinů 0 a 1 (DIP 1 a 2)
	int speedBit1 = digitalRead(pinsIn[1]); // pin 17
	int speedBit0 = digitalRead(pinsIn[0]); // pin 16

	int delayTime = 100; // výchozí hodnota
	if (speedBit1 == 0 && speedBit0 == 0) delayTime = 50;
	else if (speedBit1 == 0 && speedBit0 == 1) delayTime = 100;
	else if (speedBit1 == 1 && speedBit0 == 0) delayTime = 500;
	else if (speedBit1 == 1 && speedBit0 == 1) delayTime = 1000;

	// zhasnutí všech LED
	for (int i = 0; i < 8; i++) {
		digitalWrite(pinsOut[i], LOW);
	}

	// rozsvícení jedné LED
	digitalWrite(pinsOut[position], HIGH);

	// zpoždění podle nastavení přepínačů
	delay(delayTime);

	// posun pozice LED podle směru
	if (direction) {
		position--;
		if (position < 0) position = 7;
	} else {
		position++;
		if (position > 7) position = 0;
	}
}
