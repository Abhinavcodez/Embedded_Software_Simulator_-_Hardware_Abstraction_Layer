#include "app/logger_task.h"
#include "rtos/freertos_sim.h"
#include "utils/logger.h"

void logger_task() {
    while (true) {
        Logger::log_to_file("system.log", "Periodic log entry");
        RTOS::delay_ms(5000);
    }
}