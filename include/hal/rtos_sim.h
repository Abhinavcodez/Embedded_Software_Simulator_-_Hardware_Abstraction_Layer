// remove rtos_sim.cpp completely
#include <thread>
#include <vector>
#include <functional>
#include <chrono>

namespace RTOS {
inline std::vector<std::thread> tasks;

inline void create_task(std::function<void()> func) {
    tasks.emplace_back(func);
}

inline void start_scheduler() {
    for (auto& t : tasks) {
        if (t.joinable()) t.detach();
    }
}

inline void delay_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
} // namespace RTOS