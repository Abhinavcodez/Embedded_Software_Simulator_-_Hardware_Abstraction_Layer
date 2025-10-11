#pragma once
#include <functional>

using timer_callback_t = std::function<void(void)>;

struct timer_driver_t {
    void (*start)(int interval_ms, timer_callback_t cb);
    void (*stop)();
};

timer_driver_t *get_virtual_timer();