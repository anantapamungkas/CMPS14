#ifndef CMPS14_H
#define CMPS14_H

#include <Arduino.h>
#include <Wire.h>  // Include Wire library for I2C

class CMPS14 {
private:
    int address;        // I2C Address of CMPS14
    int headingOffset;  // Offset for heading reset

public:
    CMPS14(int i2cAddress = 0x60);  // Constructor with default address

    void begin();              // Initialize compass
    int getHeading();          // Get current heading (CW)
    int getHeadingCCW();       // Get counterclockwise heading (CCW)
    void resetHeading();       // Reset heading offset
    void printHeading();       // Print heading data

private:
    int calculateHeading(int rawAngle);  // Convert raw angle to 0-360°
};

#endif
