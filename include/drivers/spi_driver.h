#pragma once
#include <cstdint>
#include <vector>
#include <cstddef>
#include <cstdint>

struct spi_driver_t {
    void (*init)(void);
    void (*transfer)(const uint8_t *tx, uint8_t *rx, size_t len);
};

spi_driver_t *get_virtual_spi();