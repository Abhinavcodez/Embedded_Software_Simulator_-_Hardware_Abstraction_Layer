#pragma once
#include <cstddef>
#include <cstdint>
#include "drivers/uart_driver.h"
#include "IUart.h"

namespace HAL {
    void UART_Init(const std::string &dev);
    void UART_Send(const uint8_t *data, size_t len);
    uint8_t UART_Read();
}