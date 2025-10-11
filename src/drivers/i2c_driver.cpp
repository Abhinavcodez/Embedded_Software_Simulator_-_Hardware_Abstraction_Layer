#include "drivers/i2c_driver.h"
#include <iostream>
#include <map>

static std::map<uint8_t, std::vector<uint8_t>> virtual_i2c_devices;

static void i2c_init() {
    std::cout << "[I2C] Initialized virtual I2C bus\n";
    virtual_i2c_devices[0x50] = std::vector<uint8_t>(256, 0xAA); // virtual EEPROM
}

static bool i2c_read(uint8_t addr, uint8_t *data, size_t len) {
    if (virtual_i2c_devices.count(addr) == 0) return false;
    auto &mem = virtual_i2c_devices[addr];
    for (size_t i = 0; i < len && i < mem.size(); ++i) data[i] = mem[i];
    return true;
}

static bool i2c_write(uint8_t addr, const uint8_t *data, size_t len) {
    if (virtual_i2c_devices.count(addr) == 0) return false;
    auto &mem = virtual_i2c_devices[addr];
    for (size_t i = 0; i < len && i < mem.size(); ++i) mem[i] = data[i];
    return true;
}

static i2c_driver_t drv = {i2c_init, i2c_read, i2c_write};
i2c_driver_t *get_virtual_i2c() { return &drv; }