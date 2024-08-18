#include <LiquidCrystal_I2C.h>
#include "Pressure_Sensor.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);
PressureSensor PT(A0, lcd);
const byte pot = A1;
const byte pumpRelay = 3;
unsigned long startMillis, currentMillis;
const unsigned long period = 1500;
char data;

void setup() {
    startMillis = millis();
    Serial.begin(9600);
    PT.begin();
    pinMode(pot, INPUT);
    pinMode(pumpRelay, OUTPUT);
    digitalWrite(pumpRelay, HIGH);

    lcd.init();
    lcd.clear();
    lcd.backlight();
    lcd.setCursor(5, 1);
    lcd.print("Loading....");
    delay(2000);
    lcd.clear();
}

void loop() {
    PT.update();
    currentMillis = millis();
    
    if (currentMillis - startMillis >= period) {
        PT.display();
        startMillis = currentMillis;
    }

    if (Serial.available()) {
        data = Serial.read();
    }

    if (data == '1' || data == '2') {
        digitalWrite(pumpRelay, LOW);
        lcd.setCursor(0, 3);
        lcd.print("Pump On");
    } else {
        digitalWrite(pumpRelay, HIGH);
        lcd.setCursor(0, 3);
        lcd.print("Pump Off");
    }
}
