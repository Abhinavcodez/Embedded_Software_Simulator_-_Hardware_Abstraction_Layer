#include "hal/hal_gpio.h"

static gpio_driver_t *drv = nullptr;

void HAL::GPIO_Init(uint8_t pin, gpio_dir_t dir) {
    drv = get_virtual_gpio();
    drv->init(pin, dir);
}

void HAL::GPIO_Write(uint8_t pin, gpio_state_t state) { drv->write(pin, state); }
gpio_state_t HAL::GPIO_Read(uint8_t pin) { return drv->read(pin); }