#pragma once
#include <thread>
#include <vector>
#include <functional>
#include <chrono>
#include <mutex>

namespace RTOS {

// Thread storage
inline std::vector<std::thread> tasks;
// Mutex to protect task creation in multi-threaded scenarios
inline std::mutex task_mutex;

/**
 * @brief Create a simulated RTOS task
 * @param func Task function (void())
 */
inline void create_task(std::function<void()> func) {
    std::lock_guard<std::mutex> lock(task_mutex);
    tasks.emplace_back(func);
}

/**
 * @brief Start the simulated scheduler
 *        This will detach all tasks to simulate parallel execution
 */
inline void start_scheduler() {
    std::lock_guard<std::mutex> lock(task_mutex);
    for (auto& t : tasks) {
        if (t.joinable()) t.detach();
    }
    // Clear tasks vector after detaching
    tasks.clear();
}

/**
 * @brief Delay function to simulate RTOS delay
 * @param ms Milliseconds to sleep
 */
inline void delay_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

} // namespace RTOS