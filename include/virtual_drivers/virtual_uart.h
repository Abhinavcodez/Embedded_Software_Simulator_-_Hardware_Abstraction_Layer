#pragma once
#include <functional>
#include <string>

using uart_callback_t = std::function<void(const std::string&)>;

class VirtualUART {
public:
    static void init();
    static void send(const std::string& data);
    static void setCallback(uart_callback_t cb);
private:
    static uart_callback_t callback;
};