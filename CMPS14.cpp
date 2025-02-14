#include "CMPS14.h"

// Constructor: Set the I2C address and initialize offset
CMPS14::CMPS14(int i2cAddress) {
    address = i2cAddress;
    headingOffset = 0;  // Default offset
}

// Initialize I2C communication
void CMPS14::begin() {
    Wire.begin();
}

// Read compass heading (Clockwise)
int CMPS14::getHeading() {
    Wire.beginTransmission(address);
    Wire.write(0x02);  // Point to heading register
    Wire.endTransmission();

    Wire.requestFrom(address, 2);  // Request 2 bytes

    if (Wire.available() >= 2) {
        uint8_t high_byte = Wire.read();
        uint8_t low_byte = Wire.read();
        int angle16 = ((high_byte << 8) | low_byte) / 10.0;  // Convert to degrees

        return calculateHeading(angle16);
    }
    return -1;  // Error
}

// Get counterclockwise heading
int CMPS14::getHeadingCCW() {
    int heading = getHeading();
    return (heading == 0) ? 360 : (360 - heading);
}

// Reset heading to zero at the current position
void CMPS14::resetHeading() {
    headingOffset = getHeading();
}

// Convert raw angle to proper 0-360° range with offset
int CMPS14::calculateHeading(int rawAngle) {
    int heading = rawAngle - 90 - headingOffset;
    if (heading >= 360) heading -= 360;
    else if (heading < 0) heading += 360;
    return heading;
}

// Print compass data
void CMPS14::printHeading() {
    Serial.print("CW: ");
    Serial.print(getHeading());
    Serial.print("° | CCW: ");
    Serial.print(getHeadingCCW());
    Serial.println("°");
}
