#pragma once
#include "../drivers/i2c_driver.h"

namespace HAL {
    void I2C_Init();
    bool I2C_Read(uint8_t addr, uint8_t *data, size_t len);
    bool I2C_Write(uint8_t addr, const uint8_t *data, size_t len);
}