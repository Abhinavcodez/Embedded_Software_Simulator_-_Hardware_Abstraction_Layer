#include <gtest/gtest.h>
#include "../include/hal/hal_manager.h"
#include "../include/hal/IGpio.h"
#include "../include/hal/IUart.h"
#include "../include/hal/virtual_hal_devices.hpp"

TEST(HAL_UART_SendReceive_Test, BasicEcho) {
    auto uart = std::make_unique<VirtualUART>();
    HalManager::instance().register_uart(std::move(uart));

    const char msg[] = "Hello";
    HalManager::instance().uart()->send(msg, sizeof(msg));

    char buffer[64];
    HalManager::instance().uart()->receive(buffer, sizeof(buffer));

    EXPECT_STREQ(buffer, "Echo:Hello");
}

TEST(HAL_GPIO_PinWriteRead_Test, WriteRead) {
    auto gpio = std::make_unique<VirtualGPIO>();
    HalManager::instance().register_gpio(std::move(gpio));

    HalManager::instance().gpio()->write(1, true);
    EXPECT_TRUE(HalManager::instance().gpio()->read(1));
}