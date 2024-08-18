// Pressure_Sensor.cpp
#include "Pressure_Sensor.h"

PressureSensor::PressureSensor(byte sensPin, LiquidCrystal_I2C &lcdRef)
    : sensorPin(sensPin), lcd(lcdRef) {}

void PressureSensor::begin() {
    pinMode(sensorPin, INPUT);
    calculateBits();
}

void PressureSensor::calculateBits() {
    minBits = static_cast<int>((minVolt * 1024) / 5.0);
    maxBits = static_cast<int>((maxVolt * 1024) / 5.0);
}

void PressureSensor::update() {
    int sensorValue = analogRead(sensorPin);
    pressure = map(sensorValue, minBits, maxBits, minPressure, maxPressure) / 10.0;
    volt = map(sensorValue, minBits, maxBits, minV, maxV) / 10.0;

    Serial.println(sensorValue);
    Serial.println(volt);
}

void PressureSensor::display() {
    lcd.setCursor(0, 0);
    lcd.print("Pressure: ");
    lcd.print(pressure, 1);
    lcd.print(" Bar");

    lcd.setCursor(0, 1);
    lcd.print("Volts: ");
    lcd.print(volt, 1);
    lcd.print(" V");

    lcd.setCursor(0, 2);
    if (volt < 1.0) {
        lcd.print("Alarm:Sensor Malfunc");
    } else if (volt > 4.7) {
        lcd.print("Alarm: Over Pressure");
    }
}
