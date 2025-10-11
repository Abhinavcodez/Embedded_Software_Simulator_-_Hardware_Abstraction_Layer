#include "drivers/gpio_driver.h"
#include <iostream>

static std::unordered_map<uint8_t, gpio_state_t> gpio_bank;

static void gpio_init(uint8_t pin, gpio_dir_t) {
    gpio_bank[pin] = gpio_state_t::LOW;
    std::cout << "[GPIO] Pin " << (int)pin << " initialized\n";
}

static void gpio_write(uint8_t pin, gpio_state_t state) {
    gpio_bank[pin] = state;
    std::cout << "[GPIO] Pin " << (int)pin << " set to " << (state == gpio_state_t::HIGH ? "HIGH" : "LOW") << "\n";
}

static gpio_state_t gpio_read(uint8_t pin) {
    return gpio_bank.count(pin) ? gpio_bank[pin] : gpio_state_t::LOW;
}

static gpio_driver_t virtual_gpio = {gpio_init, gpio_write, gpio_read};

gpio_driver_t *get_virtual_gpio() { return &virtual_gpio; }