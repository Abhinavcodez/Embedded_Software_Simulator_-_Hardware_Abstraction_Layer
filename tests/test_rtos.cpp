#include <gtest/gtest.h>
#include "rtos/freertos_sim.h"
#include "rtos/queues.h"
#include "rtos/semaphore.h"
#include <atomic>

TEST(RTOS, TaskExecution) {
    std::atomic<int> counter{0};
    RTOS::create_task([&] {
        counter++;
    }, "TaskA");
    RTOS::start_scheduler();
    EXPECT_EQ(counter.load(), 1);
}

TEST(RTOS, QueueSendReceive) {
    RTOS::Queue<int> q(5);
    q.send(42);
    int val = 0;
    ASSERT_TRUE(q.receive(val, 100));
    EXPECT_EQ(val, 42);
}

TEST(RTOS, SemaphoreControl) {
    RTOS::Semaphore sem(false);
    std::atomic<bool> done{false};

    std::thread t([&]() {
        sem.take();
        done = true;
    });

    RTOS::delay_ms(100);
    sem.give();
    t.join();

    EXPECT_TRUE(done);
}