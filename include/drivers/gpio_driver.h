#pragma once
#include <cstdint>
#include <unordered_map>

enum class gpio_state_t { LOW = 0, HIGH };
enum class gpio_dir_t { INPUT, OUTPUT };

struct gpio_driver_t {
    void (*init)(uint8_t pin, gpio_dir_t dir);
    void (*write)(uint8_t pin, gpio_state_t state);
    gpio_state_t (*read)(uint8_t pin);
};

gpio_driver_t *get_virtual_gpio();