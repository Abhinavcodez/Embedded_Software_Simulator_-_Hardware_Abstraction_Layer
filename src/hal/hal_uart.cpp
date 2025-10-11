#include "../../include/hal/IUart.h"
#include "../../include/hal/IGpio.h"

class VirtualUart : public IUart {
public:
    void send(const char* data, int length) override {
        // simulate sending
    }
    int receive(char* buffer, int length) override {
        return 0; // simulate receiving
    }
};

IUart* get_virtual_uart() {
    return new VirtualUart();
}

IGpio* get_virtual_gpio() {
    return nullptr;
}