#include "drivers/spi_driver.h"
#include <iostream>

static void spi_init() {
    std::cout << "[SPI] Initialized virtual SPI flash\n";
}

static void spi_transfer(const uint8_t *tx, uint8_t *rx, size_t len) {
    for (size_t i = 0; i < len; ++i)
        rx[i] = tx[i] ^ 0xFF; // simple simulated response
}

static spi_driver_t drv = {spi_init, spi_transfer};
spi_driver_t *get_virtual_spi() { return &drv; }