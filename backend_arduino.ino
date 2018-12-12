#include <Arduino.h>
#include <Wire.h>
#include "User_Setup.h"

const uint8_t motor_pin[] = {3, 5, 6, 9};
const uint8_t led_pin = 13;
const uint8_t i2c_addr = 0x30;

void i2c_recv_handler(int) {
    int motor_pwm[] = {0, 0, 0, 0};
    for (auto i = 0; i < 4; i++) {
        while (!Wire.available());
        motor_pwm[i] = Wire.read();
    }
    for (auto i = 0; i < 4; i++)
        analogWrite(motor_pin[i], motor_pwm[i]);
}

void setup() {
    for (auto i = 0; i < 4; i++) {
        pinMode(motor_pin[i], OUTPUT);
        analogWrite(motor_pin[i], 0);
    }

    pinMode(led_pin, OUTPUT);
    digitalWrite(led_pin, HIGH);

    Wire.begin(i2c_addr);
    Wire.onReceive(i2c_recv_handler);
}

void loop() {
    digitalWrite(led_pin, HIGH);
    delay(500);
    digitalWrite(led_pin, LOW);
    delay(500);
}