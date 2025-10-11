#pragma once
#include <cstdint>

struct adc_driver_t {
    void (*init)(void);
    float (*read_voltage)(uint8_t channel);
};

adc_driver_t *get_virtual_adc();