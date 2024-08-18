// Pressure_Sensor.h
#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class PressureSensor {
private:
    const byte sensorPin;
    const int minPressure = 0;
    const int maxPressure = 160;
    const float minVolt = 0.5;
    const float maxVolt = 4.5;
    const int minV = 5;
    const int maxV = 45;
    int minBits, maxBits;
    float pressure, volt;
    LiquidCrystal_I2C &lcd;

    void calculateBits();

public:
    PressureSensor(byte sensPin, LiquidCrystal_I2C &lcdRef);
    void begin();
    void update();
    void display();
};

#endif
