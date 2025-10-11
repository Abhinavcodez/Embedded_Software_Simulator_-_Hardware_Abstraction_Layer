#pragma once
#include "../utils/thread_safe_queue.h"
#include <atomic>   // <-- Add this
#include <cstddef>

// Simple sensor sample struct
struct SensorSample {
    int id;
    float value;
};

// Sensor task function
void sensor_task(ThreadSafeQueue<SensorSample>& sensor_q, std::atomic<bool>& running);