#include <Arduino.h>
#include <Wire.h>
#include "User_Setup.h"

const uint8_t motor_pin[] = {3/*A1*/, 5/*A2*/, 6/*B1*/, 9/*B2*/};
const uint8_t led_pin = 13;
const uint8_t i2c_addr = 0x30;

void rec(int) {
    PRINT_DEBUG_MSG;
    noInterrupts();
    if (Wire.available() >= 4)
        for (auto i = 0; i < 4; i++) {
            auto v = Wire.read();
            if (v < 0)v = 0;
            else if (v > 255)v = 255;
            analogWrite(motor_pin[i], v);
        }
    interrupts();
}

void setup() {
    PRINT_DEBUG_MSG;
    for (auto i = 0; i < 4; i++) {
        pinMode(motor_pin[i], OUTPUT);
        analogWrite(motor_pin[i], 0);
    }

    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, HIGH);

    Wire.onReceive(rec);
    Wire.begin(i2c_addr);
}

void loop() {
    PRINT_DEBUG_MSG;
    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);
    delay(500);
}