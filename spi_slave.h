#pragma once

#include <Arduino.h>

struct buffer {
    uint8_t size;
    uint8_t *data;
};


typedef void(*cb)(buffer);

static cb cb_func;

constexpr uint8_t default_ss = 2;

class {
private:
    uint8_t ss_pin = static_cast<uint8_t>(digitalPinToInterrupt(default_ss));
public:
    void set_ss(uint8_t _ss_pin = static_cast<uint8_t >(digitalPinToInterrupt(default_ss))) {
        ss_pin = static_cast<uint8_t>(digitalPinToInterrupt(_ss_pin));
    }

    void begin() {
        attachInterrupt(static_cast<uint8_t>(digitalPinToInterrupt(ss_pin)), interrupt_handler, LOW);
    }

    void end() {
        detachInterrupt(static_cast<uint8_t>(digitalPinToInterrupt(ss_pin)));
    }

    void on_data(cb func) {
        cb_func = func;
    }

private:
    static uint8_t spi_slave_receive() {
        while (!(SPSR & (1 << SPIF)));
        return SPDR;
    }

    static void interrupt_handler() {
        buffer buf;
        uint8_t size = spi_slave_receive();
        buf.size = size;
        buf.data = new uint8_t[size];
        for (auto i = 0; i < size; i++)
            buf.data[i] = spi_slave_receive();
        if (cb_func)cb_func(buf);
        delete[]buf.data;
    }
} SPI_slave;