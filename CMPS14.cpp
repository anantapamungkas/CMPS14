#include "CMPS14.h"

// Constructor: Set the I2C address and initialize the initial angle
CMPS14::CMPS14(int i2cAddress) {
    address = i2cAddress;
    initialAngle = 0;  // Default: No offset
}

// Initialize I2C communication
void CMPS14::begin() {
    Wire.begin();
}

// Internal function to read raw angle from CMPS14
int CMPS14::readRawAngle() {
    Wire.beginTransmission(address);
    Wire.write(0x02);  // Point to heading register
    Wire.endTransmission();

    Wire.requestFrom(address, 2);  // Request 2 bytes

    if (Wire.available() >= 2) {
        uint8_t high_byte = Wire.read();
        uint8_t low_byte = Wire.read();
        return ((high_byte << 8) | low_byte) / 10.0;  // Convert to degrees
    }
    return -1;  // Error
}

// Get compass heading (Clockwise), adjusted for reset
int CMPS14::getHeading() {
    int rawAngle = readRawAngle();
    if (rawAngle == -1) return -1; // Error checking

    int heading = (rawAngle - initialAngle + 360) % 360; // Adjusted for reset
    return (heading == 0) ? 360 : heading;
}

// Get counterclockwise heading
int CMPS14::getHeadingCCW() {
    int heading = getHeading();
    return (heading == 360) ? 0 : (360 - heading);
}

// Reset the heading to the current position
void CMPS14::resetHeading() {
    int rawAngle = readRawAngle();
    if (rawAngle != -1) {
        initialAngle = rawAngle + 90;
    }
}

// Print compass heading data
void CMPS14::printHeading() {
    Serial.print("CW: ");
    Serial.print(getHeading());
    Serial.print("° | CCW: ");
    Serial.print(getHeadingCCW());
    Serial.println("°");
}
