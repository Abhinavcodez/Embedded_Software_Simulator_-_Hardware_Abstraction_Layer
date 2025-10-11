#include "../../include/rtos/rtos.h"
#include <thread>
#include <chrono>

namespace RTOS {

void create_task(std::function<void()> fn, const std::string&) {
    std::thread(fn).detach();
}

void start_scheduler() {}

void delay_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

}