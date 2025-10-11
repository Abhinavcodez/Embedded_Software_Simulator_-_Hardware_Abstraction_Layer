#include "hal/hal_i2c.h"

static i2c_driver_t *drv = nullptr;

void HAL::I2C_Init() {
    drv = get_virtual_i2c();
    drv->init();
}

bool HAL::I2C_Read(uint8_t addr, uint8_t *data, size_t len) {
    return drv->read(addr, data, len);
}

bool HAL::I2C_Write(uint8_t addr, const uint8_t *data, size_t len) {
    return drv->write(addr, data, len);
}