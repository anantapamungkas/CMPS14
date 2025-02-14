#include <CMPS14.h>

// Create CMPS14 object
CMPS14 compass;

void setup() {
    Serial.begin(9600);
    compass.begin();
}

void loop() {
    compass.printHeading();  // Print heading data

    // Reset heading when user presses 'r' in Serial Monitor
    if (Serial.available()) {
        char command = Serial.read();
        if (command == 'r') {
            compass.resetHeading();
            Serial.println("Compass reset!");
        }
    }

    delay(500);
}
