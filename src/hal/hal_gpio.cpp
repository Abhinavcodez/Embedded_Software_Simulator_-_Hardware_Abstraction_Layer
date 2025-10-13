#include "hal/hal_gpio.h"
#include <iostream>

class VirtualGPIO : public IGpio {
public:
    void write(int pin, bool value) override {
        std::cout << "[GPIO] Pin " << pin << " = " << value << std::endl;
    }

    bool read(int pin) override {
        std::cout << "[GPIO] Read pin " << pin << std::endl;
        return false;
    }
};

std::unique_ptr<IGpio> get_virtual_gpio() {
    return std::make_unique<VirtualGPIO>();
}