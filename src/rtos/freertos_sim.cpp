#include <functional>
#include <string>
#include <iostream>

namespace RTOS {
    void create_task(std::function<void()> task_func, const std::string& name) {
        std::cout << "[RTOS] Created task: " << name << std::endl;
    }
    void start_scheduler() {
        std::cout << "[RTOS] Scheduler started." << std::endl;
    }
    void delay_ms(int ms) {}
}