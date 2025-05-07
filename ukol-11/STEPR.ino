#include <Stepper.h>

const int stepsPerRevolution = 100;

Stepper myStepper(stepsPerRevolution, 2, 3, 4, 5);

void setup() {
	Serial.begin(9600);
	myStepper.setSpeed(30);
	Serial.println("Zadejte počet kroků a stiskněte:");
}

void loop() {
	if (Serial.available()) {
		String input = Serial.readStringUntil('\n');
		int steps = input.toInt();
		myStepper.step(steps);
		Serial.print("Otoceno o ");
		Serial.print(steps);
		Serial.println(" kroku.");
	}
}
