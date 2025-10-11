#pragma once
#include "drivers/timer_driver.h"

namespace HAL {
    void Timer_Start(int interval_ms, timer_callback_t cb);
    void Timer_Stop();
}