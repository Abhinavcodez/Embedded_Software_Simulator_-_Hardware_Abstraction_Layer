#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <string>
#include "../../include/hal/hal_manager.h"
#include "../../include/hal/hal_manager_stubs.h"
#include "../../include/app/sensor_task.h"
#include "../../include/utils/thread_safe_queue.h"

// Processing task
void processing_task(ThreadSafeQueue<SensorSample>& inq,
                     ThreadSafeQueue<std::string>& outq,
                     std::atomic<bool>& running) {
    while (running.load()) {
        SensorSample sample = inq.pop();
        outq.push("Sensor ID: " + std::to_string(sample.id) + 
                  " Value: " + std::to_string(sample.value));
    }
}

// Logger task
void logger_task(ThreadSafeQueue<std::string>& q, std::atomic<bool>& running) {
    while (running.load()) {
        std::string line = q.pop();
        std::cout << "[LOG] " << line << std::endl;
    }
}

// CLI task stub
void cli_task(IUart* uart, ThreadSafeQueue<std::string>& logger_q, std::atomic<bool>& running) {
    std::cout << "[CLI] CLI task started..." << std::endl;
    while (running.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::atomic<bool> running(true);

    // Queues
    ThreadSafeQueue<SensorSample> sensor_q;
    ThreadSafeQueue<std::string> log_q;

    // Create virtual HAL devices
    auto uart = get_virtual_uart();
    auto gpio = get_virtual_gpio();

    HalManager::instance().register_uart(std::move(uart));
    HalManager::instance().register_gpio(std::move(gpio));

    // Launch tasks
    std::thread tsensor(sensor_task, std::ref(sensor_q), std::ref(running));
    std::thread tproc(processing_task, std::ref(sensor_q), std::ref(log_q), std::ref(running));
    std::thread tlogger(logger_task, std::ref(log_q), std::ref(running));
    std::thread tcli(cli_task, HalManager::instance().uart(), std::ref(log_q), std::ref(running));

    // Run simulation for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));
    running = false;

    // Join threads
    tsensor.join();
    tproc.join();
    tlogger.join();
    tcli.join();

    std::cout << "[MAIN] Simulation finished." << std::endl;
    return 0;
}