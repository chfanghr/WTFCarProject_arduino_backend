#include <Wire.h>
#include <Arduino.h>

const uint8_t motor_pin[] = {3/*A1*/, 5/*A2*/, 6/*B1*/, 9/*B2*/};
uint8_t motor_pwm[] = {0, 0, 0, 0};
bool is_pwm_changed = false;
const uint8_t i2c_addr = 9;

void setup() {
    for (auto i = 0; i < 4; i++)pinMode(motor_pin[i], OUTPUT);
    Wire.begin(i2c_addr);
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
}

void receiveEvent(int) {
    while (Wire.available() < 4);
    for (auto i = 0; i < 4; i++)motor_pwm[i] = static_cast<uint8_t>(Wire.read());
    is_pwm_changed = true;
}

void requestEvent() {
    Wire.write(motor_pwm, 4);
}

void loop() {
    if (is_pwm_changed) {
        for (auto i = 0; i < 4; i++)analogWrite(motor_pin[i], motor_pwm[i]);
        is_pwm_changed = false;
    }
}