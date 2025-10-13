#include <iostream>
#include <thread>
#include <atomic>
#include <functional>
#include "../../include/hal/rtos_sim.h"
#include "../../include/app/sensor_task.h"
#include "../../include/utils/thread_safe_queue.h"

void RtosSim::run(ThreadSafeQueue<SensorSample>& sensor_q,
                  ThreadSafeQueue<std::string>& log_q,
                  std::atomic<bool>& running) {

    // Sensor task thread
    std::thread tsensor([&]() {
        sensor_task(sensor_q, running);
    });

    // Processing task thread
    std::thread tproc([&]() {
        while (running.load()) {
            SensorSample sample = sensor_q.pop();
            log_q.push("Sensor ID: " + std::to_string(sample.id) + 
                       " Value: " + std::to_string(sample.value));
        }
    });

    // Logger task thread
    std::thread tlogger([&]() {
        while (running.load()) {
            std::string line = log_q.pop();
            std::cout << "[LOG] " << line << std::endl;
        }
    });

    tsensor.join();
    tproc.join();
    tlogger.join();
}