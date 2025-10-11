#include "drivers/timer_driver.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>

static std::atomic<bool> running{false};

static void timer_thread(int interval, timer_callback_t cb) {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        cb();
    }
}

static void timer_start(int interval, timer_callback_t cb) {
    if (running) return;
    running = true;
    std::thread(timer_thread, interval, cb).detach();
    std::cout << "[Timer] Started with " << interval << "ms interval\n";
}

static void timer_stop() {
    running = false;
    std::cout << "[Timer] Stopped\n";
}

static timer_driver_t drv = {timer_start, timer_stop};
timer_driver_t *get_virtual_timer() { return &drv; }