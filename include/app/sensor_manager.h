#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <vector>
#include <string>

// Sample struct for sensors
struct SensorSample {
    int id;
    float value;
};

// Sensor manager class
class SensorManager {
public:
    std::vector<SensorSample> readSensors();
};

#endif // SENSOR_MANAGER_H