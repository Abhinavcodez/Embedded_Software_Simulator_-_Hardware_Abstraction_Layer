// tests/test_integration.cpp
#include <gtest/gtest.h>
#include <thread>
#include <chrono>

#include "../include/app/sensor_task.h"           // For SensorSample
#include "../include/utils/thread_safe_queue.h"   // For ThreadSafeQueue

// ------------------------
// Fake sensor producer
// ------------------------
void fake_sensor_producer(ThreadSafeQueue<SensorSample>& queue, int count) {
    for (int i = 0; i < count; ++i) {
        SensorSample sample;
        sample.id = i;
        sample.value = i * 10;
        queue.push(sample);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// ------------------------
// System Integration Test
// ------------------------
TEST(SystemIntegration_SensorTaskRun_NoRTOS_Test, QueuePushPop) {
    ThreadSafeQueue<SensorSample> sensor_q;

    // Start producer thread
    std::thread producer(fake_sensor_producer, std::ref(sensor_q), 5);

    // Consume from queue
    for (int i = 0; i < 5; ++i) {
        SensorSample sample = sensor_q.pop();  // use return value
        EXPECT_EQ(sample.id, i);
        EXPECT_EQ(sample.value, i * 10);
    }

    producer.join();
}