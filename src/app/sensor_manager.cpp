#include "../../include/app/sensor_manager.h"

std::vector<SensorSample> SensorManager::readSensors() {
    std::vector<SensorSample> samples;
    SensorSample s1{1, 23.5f};
    SensorSample s2{2, 42.0f};
    samples.push_back(s1);
    samples.push_back(s2);
    return samples;
}