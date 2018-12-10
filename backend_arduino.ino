#include <Arduino.h>
#include "spi_slave.h"

#define DEBUG
const uint8_t motor[]{3, 5, 6, 9};

uint8_t motor_pwm[] = {0, 0, 0, 0};

void update_pwm_value(buffer buf) {
    if (buf.size < 4)return;
#ifdef DEBUG
    for (auto i = 0; i < buf.size; i++)
        Serial.print(static_cast<char>(buf.data));
    Serial.println();
#endif
    for (auto i = 0; i < 4; i++)
        motor_pwm[i] = buf.data[i];
}

void setup() {
    SPI_slave.set_ss(3);
    SPI_slave.on_data(update_pwm_value);
    SPI_slave.begin();
    for (auto i = 0; i < 4; i++)
        pinMode(motor[i], OUTPUT);
}

void loop() {
    for (auto i = 0; i < 4; i++)
        analogWrite(motor[i], motor_pwm[i]);
}