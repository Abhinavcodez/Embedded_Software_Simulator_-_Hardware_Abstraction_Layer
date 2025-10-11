#include "virtual_gpio.h"
#include <iostream>

std::unordered_map<Pin, GpioState> VirtualGPIO::pins;

void VirtualGPIO::init() {
    pins.clear();
    std::cout << "[GPIO] Initialized virtual GPIOs.\n";
}

void VirtualGPIO::write(Pin pin, GpioState state) {
    pins[pin] = state;
    std::cout << "[GPIO] Pin " << (int)pin << " -> " << (state == GpioState::HIGH ? "HIGH" : "LOW") << "\n";
}

GpioState VirtualGPIO::read(Pin pin) {
    return pins[pin];
}

void VirtualGPIO::toggle(Pin pin) {
    pins[pin] = (pins[pin] == GpioState::HIGH) ? GpioState::LOW : GpioState::HIGH;
    std::cout << "[GPIO] Pin " << (int)pin << " toggled.\n";
}