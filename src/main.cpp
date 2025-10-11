#include <iostream>
#include <thread>
#include <atomic>
#include <memory>
#include <string>
#include "../../include/hal/hal_manager.h"
#include "../../include/hal/IUart.h"
#include "../../include/hal/IGpio.h"
#include "../../include/app/sensor_task.h"
#include "../../include/utils/thread_safe_queue.h"
#include <atomic>
#include <thread>
#include "../../include/utils/thread_safe_queue.h"
#include "../../include/app/sensor_manager.h"


// Example sensor data structure
struct SensorSample {
    int id;
    float value;
};

// Processing task
void processing_task(ThreadSafeQueue<SensorSample>& inq,
                     ThreadSafeQueue<std::string>& outq,
                     std::atomic<bool>& running) {
    while (running.load()) {
        SensorSample sample;
        if (inq.pop(sample)) {
            outq.push("Sensor ID: " + std::to_string(sample.id) + " Value: " + std::to_string(sample.value));
        }
    }
}

// Logger task
void logger_task(ThreadSafeQueue<std::string>& q, std::atomic<bool>& running) {
    while (running.load()) {
        std::string line;
        if (q.pop(line)) {
            std::cout << "[LOG] " << line << std::endl;
        }
    }
}

// CLI task stub
void cli_task(IUart* uart, ThreadSafeQueue<std::string>& logger_q, std::atomic<bool>& running) {
    std::cout << "[CLI] CLI task started..." << std::endl;
    while (running.load()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// Virtual UART/GPIO factories
std::unique_ptr<IUart> create_virtual_uart(const std::string& path, bool loopback) {
    class VirtualUART : public IUart {
    public:
        bool init() override { return true; }
        bool write(const uint8_t* data, size_t len) override { return true; }
        bool read(uint8_t* data, size_t len) override { return true; }
    };
    return std::make_unique<VirtualUART>();
}

std::unique_ptr<IGpio> create_virtual_gpio(size_t pins) {
    class VirtualGPIO : public IGpio {
    public:
        void init() override {}
        void write_pin(uint8_t pin, bool value) override {}
        bool read_pin(uint8_t pin) override { return false; }
    };
    return std::make_unique<VirtualGPIO>();
}

int main(int argc, char** argv) {
    std::atomic<bool> running(true);

    // Queues for inter-task communication
    ThreadSafeQueue<SensorSample> sensor_q;
    ThreadSafeQueue<std::string> log_q;

    // Create virtual HAL interfaces
    auto uart = create_virtual_uart("/tmp/virtual_uart.log", true);
    auto gpio = create_virtual_gpio(8);

    // Register virtual devices with HAL manager
    HalManager::instance().register_uart(std::move(uart));
    HalManager::instance().register_gpio(std::move(gpio));

    // Launch tasks
    std::thread tsensor(sensor_task); // sensor_task() from app/sensor_task.h
    std::thread tproc(processing_task, std::ref(sensor_q), std::ref(log_q), std::ref(running));
    std::thread tlogger(logger_task, std::ref(log_q), std::ref(running));
    std::thread tcli(cli_task, HalManager::instance().uart(), std::ref(log_q), std::ref(running));

    // Run simulation for a fixed period
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