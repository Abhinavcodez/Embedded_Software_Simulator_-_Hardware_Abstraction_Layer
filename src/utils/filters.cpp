#include "utils/filters.h"

float kalman_filter(float measurement) {
    static float estimate = 0.0f;
    static float error = 1.0f;
    float gain = error / (error + 1.0f);
    estimate = estimate + gain * (measurement - estimate);
    error = (1 - gain) * error;
    return estimate;
}