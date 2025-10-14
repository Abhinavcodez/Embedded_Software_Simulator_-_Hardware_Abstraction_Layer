#include <gtest/gtest.h>
#include "../include/hal/rtos_sim.h"
#include <atomic>
#include <chrono>
#include <iostream>

TEST(RTOS_Sim, BasicTaskExecution) {
    std::atomic<int> counter(0);

    // Add tasks
    RTOS::create_task([&counter]() {
        for (int i = 0; i < 5; ++i) {
            counter++;
            RTOS::delay_ms(10);
        }
    });

    RTOS::create_task([&counter]() {
        for (int i = 0; i < 5; ++i) {
            counter++;
            RTOS::delay_ms(15);
        }
    });

    // Start scheduler (detached threads)
    RTOS::start_scheduler();

    // Wait long enough for tasks to finish deterministically
    RTOS::delay_ms(200);

    EXPECT_EQ(counter.load(), 10);
}

TEST(RTOS_Sim, DelayFunction) {
    auto start = std::chrono::high_resolution_clock::now();
    RTOS::delay_ms(50);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    EXPECT_GE(duration, 50);
}

// Optional: deterministic join test version
TEST(RTOS_Sim, DeterministicJoin) {
    std::atomic<int> counter(0);

    std::vector<std::thread> local_tasks;

    local_tasks.emplace_back([&counter]() {
        for (int i = 0; i < 5; ++i) {
            counter++;
            RTOS::delay_ms(10);
        }
    });

    local_tasks.emplace_back([&counter]() {
        for (int i = 0; i < 5; ++i) {
            counter++;
            RTOS::delay_ms(15);
        }
    });

    // Join threads deterministically
    for (auto& t : local_tasks) {
        if (t.joinable()) t.join();
    }

    EXPECT_EQ(counter.load(), 10);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}