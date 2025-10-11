#pragma once
#include "drivers/gpio_driver.h"

namespace HAL {
    void GPIO_Init(uint8_t pin, gpio_dir_t dir);
    void GPIO_Write(uint8_t pin, gpio_state_t state);
    gpio_state_t GPIO_Read(uint8_t pin);
}