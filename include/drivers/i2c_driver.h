#pragma once
#include <cstdint>
#include <vector>
#include <cstddef>
#include <cstdint>


struct i2c_driver_t {
    void (*init)(void);
    bool (*read)(uint8_t addr, uint8_t *data, size_t len);
    bool (*write)(uint8_t addr, const uint8_t *data, size_t len);
};

i2c_driver_t *get_virtual_i2c();