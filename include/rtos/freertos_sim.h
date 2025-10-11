#pragma once
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <functional>

namespace RTOS {
    using TaskFunction_t = std::function<void()>;

    void create_task(TaskFunction_t func, const std::string &name);
    void start_scheduler();
    void delay_ms(int ms);
}