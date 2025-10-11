#include "virtual_uart.h"
#include <iostream>

uart_callback_t VirtualUART::callback = nullptr;

void VirtualUART::init() {
    std::cout << "[UART] Initialized virtual UART.\n";
}

void VirtualUART::send(const std::string& data) {
    std::cout << "[UART TX] " << data << "\n";
    if (callback) callback("[UART RX ECHO] " + data);
}

void VirtualUART::setCallback(uart_callback_t cb) {
    callback = cb;
}