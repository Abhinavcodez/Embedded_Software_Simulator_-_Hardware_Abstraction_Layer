#pragma once
#include <string>
#include <vector>
#include <iostream>

namespace HAL {

// Mock UART functions
inline void UART_Init(const std::string& port) {
    std::cout << "[Mock HAL] UART_Init called for port: " << port << std::endl;
}

inline void UART_Send(const unsigned char* data, unsigned long length) {
    std::cout << "[Mock HAL] UART_Send called with length: " << length << std::endl;
    for (unsigned long i = 0; i < length; ++i)
        std::cout << (int)data[i] << " ";
    std::cout << std::endl;
}

}