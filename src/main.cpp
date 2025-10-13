#include <thread>       // for std::thread
#include <chrono>       // for std::chrono
#include <atomic>       // for std::atomic
#include <memory>
#include <iostream>
#include <string>
#include "../include/app/sensor_task.h"
#include "../include/utils/thread_safe_queue.h"
#include "../include/hal/hal_manager.h"
#include "../include/hal/IGpio.h"
#include "../include/hal/IUart.h"

#ifdef USE_RTOS
#include "../include/hal/rtos_sim.h"
#endif


ThreadSafeQueue<SensorSample> sensor_q;
ThreadSafeQueue<std::string> log_q;

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

// Virtual UART/GPIO
class VirtualUART : public IUart {
public:
    bool init() { return true; }
    void send(const char* data, int length) override {}
    int receive(char* buffer, int length) override { return 0; }
};

class VirtualGPIO : public IGpio {
public:
    void init() {}
    void write(int pin, bool value) override {}
    bool read(int pin) override { return false; }
};

int main() {
    std::atomic<bool> running(true);

    auto uart = std::make_unique<VirtualUART>();
    auto gpio = std::make_unique<VirtualGPIO>();

    HalManager::instance().register_uart(std::move(uart));
    HalManager::instance().register_gpio(std::move(gpio));

#ifdef USE_RTOS
RTOS::create_task([&]() { sensor_task(sensor_q, running); });
RTOS::create_task([&]() { processing_task(sensor_q, log_q, running); });
RTOS::create_task([&]() { logger_task(log_q, running); });
RTOS::create_task([&]() { cli_task(HalManager::instance().uart(), log_q, running); });
RTOS::start_scheduler();
RTOS::delay_ms(5000);
#else
// HAL-only threading
std::thread tsensor(sensor_task, std::ref(sensor_q), std::ref(running));
std::thread tproc(processing_task, std::ref(sensor_q), std::ref(log_q), std::ref(running));
std::thread tlogger(logger_task, std::ref(log_q), std::ref(running));
std::thread tcli(cli_task, HalManager::instance().uart(), std::ref(log_q), std::ref(running));

std::this_thread::sleep_for(std::chrono::seconds(5));

tsensor.join();
tproc.join();
tlogger.join();
tcli.join();
#endif

    std::cout << "[MAIN] Simulation finished." << std::endl;
    return 0;
}