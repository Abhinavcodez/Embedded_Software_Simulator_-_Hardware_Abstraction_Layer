#include <gtest/gtest.h>
#include "hal/hal_uart.h"
#include "hal/hal_gpio.h"

TEST(HAL_UART, SendReceive) {
    HAL::UART_Init("test_uart.txt");
    uint8_t msg[] = {'H', 'i'};
    HAL::UART_Send(msg, 2);
    SUCCEED();
}

TEST(HAL_GPIO, PinWriteRead) {
    auto gpio_drv = get_virtual_gpio();
    gpio_drv->init(1, gpio_dir_t::OUTPUT);
    gpio_drv->write(1, gpio_state_t::HIGH);
    EXPECT_EQ(gpio_drv->read(1), gpio_state_t::HIGH);
}