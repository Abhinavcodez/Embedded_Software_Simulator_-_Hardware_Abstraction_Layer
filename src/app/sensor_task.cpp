#include "../../include/app/sensor_task.h"
#include <thread>
#include <chrono>
#include <random>
#include <atomic>

void sensor_task(ThreadSafeQueue<SensorSample>& sensor_q, std::atomic<bool>& running) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 100.0f);
    int sensor_id = 1;

    while (running.load()) {
        SensorSample sample;
        sample.id = sensor_id++;
        sample.value = dist(gen);

        sensor_q.push(sample);
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // simulate sensor rate
    }
}