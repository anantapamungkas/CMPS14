#include <CMPS14.h>

CMPS14 compass;

void setup() {
    Serial.begin(9600);
    compass.begin();
}

void loop() {
    compass.printHeading();

    // Example: Shift heading by +45°
    int newHeading = compass.shiftHeading(45);
    Serial.print("Heading + 45°: ");
    Serial.println(newHeading);

    delay(500);
}
