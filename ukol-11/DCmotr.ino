const int pwmPin = 3;
const int dirPin = 4;

int currentSpeed = 0;
int targetSpeed = 0;
unsigned long lastUpdate = 0;

void setup() {
	pinMode(pwmPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	Serial.begin(9600);
	Serial.println("Zadej hodnotu rychlosti (-100 az 100):");
}

void loop() {
	// Čtení čísla ze sériové linky (při zadání ?)
	if (Serial.available()) {
		int val = Serial.parseInt();
		if (val > 100) val = 100;
		if (val < -100) val = -100;
		targetSpeed = val;
		Serial.print("Nova cilova rychlost: ");
		Serial.println(targetSpeed);
	}

	// Pozvolné přibližování k cílové rychlosti
	if (millis() - lastUpdate >= 20) {
		lastUpdate = millis();

		if (currentSpeed != targetSpeed) {
			if (currentSpeed < targetSpeed) currentSpeed++;
			else if (currentSpeed > targetSpeed) currentSpeed--;

			int pwm = map(abs(currentSpeed), 0, 100, 0, 255);

			if (currentSpeed >= 0) {
				digitalWrite(dirPin, HIGH);
			} else {
				digitalWrite(dirPin, LOW);
			}

			analogWrite(pwmPin, pwm);
		}
	}
}
