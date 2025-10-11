#include <gtest/gtest.h>
#include "../include/hal/IUart.h"
#include "rtos/freertos_sim.h"
#include "../include/app/sensor_task.h"

TEST(SystemIntegration, SensorTaskRun) {
    std::atomic<int> count = 0;
    RTOS::create_task([&]() {
        count++;
        RTOS::delay_ms(10);
    }, "TestTask");

    RTOS::start_scheduler();
    EXPECT_EQ(count.load(), 1);
}