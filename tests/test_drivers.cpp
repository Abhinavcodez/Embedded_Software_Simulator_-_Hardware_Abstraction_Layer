#include <gtest/gtest.h>
#include "drivers/uart_driver.h"
#include "drivers/gpio_driver.h"

TEST(VirtualUART, BasicOperations) {
    auto *uart = get_virtual_uart();
    uart->init("uart_test.txt");
    uart->write('A');
    EXPECT_GE(uart->read(), 0);
}

TEST(VirtualGPIO, TogglePin) {
    auto *gpio = get_virtual_gpio();
    gpio->init(5, gpio_dir_t::OUTPUT);
    gpio->write(5, gpio_state_t::LOW);
    EXPECT_EQ(gpio->read(5), gpio_state_t::LOW);
}