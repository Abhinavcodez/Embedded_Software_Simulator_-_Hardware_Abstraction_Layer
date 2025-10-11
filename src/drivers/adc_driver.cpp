#include "drivers/adc_driver.h"
#include <iostream>
#include <cstdlib>

static void adc_init() {
    std::cout << "[ADC] Initialized virtual ADC\n";
}

static float adc_read_voltage(uint8_t channel) {
    float v = (std::rand() % 3300) / 1000.0f;
    std::cout << "[ADC] Channel " << (int)channel << " voltage: " << v << "V\n";
    return v;
}

static adc_driver_t drv = {adc_init, adc_read_voltage};
adc_driver_t *get_virtual_adc() { return &drv; }