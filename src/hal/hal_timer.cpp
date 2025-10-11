#include "hal/hal_timer.h"

static timer_driver_t *drv = nullptr;

void HAL::Timer_Start(int interval_ms, timer_callback_t cb) {
    drv = get_virtual_timer();
    drv->start(interval_ms, cb);
}

void HAL::Timer_Stop() { drv->stop(); }