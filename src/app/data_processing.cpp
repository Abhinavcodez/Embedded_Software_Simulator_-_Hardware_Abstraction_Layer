#include "app/data_processing.h"
#include "rtos/freertos_sim.h"
#include "utils/filters.h"
#include <iostream>
#include <vector>

void processing_task() {
    std::vector<float> buffer;
    while (true) {
        float val = rand() % 100;
        buffer.push_back(val);
        if (buffer.size() > 10) buffer.erase(buffer.begin());
        float avg = moving_average(buffer);
        std::cout << "[Processing] Filtered Value: " << avg << "\n";
        RTOS::delay_ms(2000);
    }
}

float moving_average(const std::vector<float> &data) {
    if (data.empty()) return 0.0f;
    float sum = 0;
    for (auto &d : data) sum += d;
    return sum / data.size();
}