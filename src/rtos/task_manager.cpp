#include "rtos/task_manager.h"
#include "rtos/freertos_sim.h"
#include <vector>
#include <algorithm>
#include <iostream>

static std::vector<RTOS::TaskDescriptor> task_list;

void RTOS::register_task(const std::string &name, TaskFunction_t entry, int priority) {
    task_list.push_back({name, entry, priority});
    std::cout << "[RTOS] Registered task: " << name << " (prio " << priority << ")\n";
}

void RTOS::start_registered_tasks() {
    std::sort(task_list.begin(), task_list.end(), [](auto &a, auto &b) {
        return a.priority > b.priority; // high priority first
    });

    for (auto &t : task_list)
        RTOS::create_task(t.entry, t.name);

    RTOS::start_scheduler();
}