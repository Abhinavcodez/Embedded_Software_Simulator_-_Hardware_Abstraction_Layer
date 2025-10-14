#ifndef VIRTUAL_HAL_DEVICES_HPP
#define VIRTUAL_HAL_DEVICES_HPP

#include <iostream>
#include <cstring>
#include "IUart.h"
#include "IGpio.h"

// ----------- Virtual UART -------------
class VirtualUART : public IUart {
public:
    void send(const char* data, int length) override {
        std::string msg(data, length);
        std::cout << "[VirtualUART] TX: " << msg << std::endl;
        last_message = msg;
    }

    int receive(char* buffer, int length) override {
        std::string echo = "Echo:" + last_message;
        std::strncpy(buffer, echo.c_str(), length);
        buffer[length - 1] = '\0';
        std::cout << "[VirtualUART] RX: " << buffer << std::endl;
        return echo.size();
    }

private:
    std::string last_message;
};

// ----------- Virtual GPIO -------------
class VirtualGPIO : public IGpio {
public:
    void write(int pin, bool value) override {
        states[pin] = value;
        std::cout << "[VirtualGPIO] Pin " << pin << " = "
                  << (value ? "HIGH" : "LOW") << std::endl;
    }

    bool read(int pin) override {
        return states[pin];
    }

private:
    bool states[64] = {false}; // simulate 64 GPIO pins
};

#endif // VIRTUAL_HAL_DEVICES_HPP