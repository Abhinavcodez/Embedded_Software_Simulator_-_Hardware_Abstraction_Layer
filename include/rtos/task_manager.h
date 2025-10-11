#pragma once
#include <string>
#include <functional>

namespace RTOS {
    using TaskFunction_t = std::function<void()>;

    struct TaskDescriptor {
        std::string name;
        TaskFunction_t entry;
        int priority;
    };

    void register_task(const std::string &name, TaskFunction_t entry, int priority);
    void start_registered_tasks();
}