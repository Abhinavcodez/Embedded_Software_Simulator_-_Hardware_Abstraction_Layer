#pragma once
#include <string>
#include <vector>

namespace HAL {

void UART_Init(const std::string& port);
void UART_Send(const unsigned char* data, unsigned long length);
std::vector<unsigned char> UART_Receive(unsigned long length);

} // namespace HAL