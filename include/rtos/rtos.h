#pragma once
#include <functional>
#include <string>

namespace RTOS {
void create_task(std::function<void()> task_fn, const std::string& name);
void start_scheduler();
void delay_ms(int ms);
}