#pragma once
#include "drivers/spi_driver.h"

namespace HAL {
    void SPI_Init();
    void SPI_Transfer(const uint8_t *tx, uint8_t *rx, size_t len);
}