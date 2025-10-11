#include "../../include/hal/hal.h"
#include <iostream>
#include <vector>

namespace HAL {

// Minimal dummy implementations for testing

void UART_Init(const std::string& port) {
    std::cout << "[HAL] UART initialized on port: " << port << std::endl;
}

void UART_Send(const unsigned char* data, unsigned long length) {
    std::cout << "[HAL] UART Send: ";
    for (unsigned long i = 0; i < length; ++i) {
        std::cout << std::hex << (int)data[i] << " ";
    }
    std::cout << std::dec << std::endl;
}

std::vector<unsigned char> UART_Receive(unsigned long length) {
    std::vector<unsigned char> dummy(length, 0xAA); // dummy data
    std::cout << "[HAL] UART Receive called, returning dummy data\n";
    return dummy;
}

} // namespace HAL