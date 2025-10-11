#pragma once
#include "virtual_uart.h"
#include "virtual_gpio.h"
#include <memory>

std::unique_ptr<IUart> get_virtual_uart();
std::unique_ptr<IGpio> get_virtual_gpio();