#include "hal/hal_spi.h"

static spi_driver_t *drv = nullptr;

void HAL::SPI_Init() {
    drv = get_virtual_spi();
    drv->init();
}

void HAL::SPI_Transfer(const uint8_t *tx, uint8_t *rx, size_t len) {
    drv->transfer(tx, rx, len);
}