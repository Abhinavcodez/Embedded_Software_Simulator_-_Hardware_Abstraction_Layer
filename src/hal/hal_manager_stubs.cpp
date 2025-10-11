#include "../../include/hal/hal_manager.h"
#include "../../include/hal/virtual_uart.h"
#include "../../include/hal/virtual_gpio.h"
#include <memory>

std::unique_ptr<IUart> get_virtual_uart() {
    return std::make_unique<VirtualUART>();
}

std::unique_ptr<IGpio> get_virtual_gpio() {
    return std::make_unique<VirtualGPIO>();
}