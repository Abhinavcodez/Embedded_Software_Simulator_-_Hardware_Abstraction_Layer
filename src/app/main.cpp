#include "../../include/app/sensor_task.h"
#include "../../include/utils/diagnostics.h"
#include <thread>
#include <iostream>

int main() {
    Diagnostics::report("Starting Embedded Simulator");

    std::thread sensorThread(sensor_task);

    // Run for 2 seconds
    std::this_thread::sleep_for(std::chrono::seconds(2));
    running.store(false);

    sensorThread.join();
    Diagnostics::report("Simulator stopped");

    return 0;
}