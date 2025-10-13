#include "../../include/hal/IUart.h"
#include <iostream>

class VirtualUART : public IUart {
public:
    void send(const char* data, int length) override {
        std::cout << "[UART] Send: ";
        for(int i=0;i<length;++i) std::cout << std::hex << (int)data[i] << " ";
        std::cout << std::endl;
    }

    int receive(char* buffer, int length) override {
        std::cout << "[UART] Receive called" << std::endl;
        return 0;
    }
};

std::unique_ptr<IUart> get_virtual_uart() {
    return std::make_unique<VirtualUART>();
}