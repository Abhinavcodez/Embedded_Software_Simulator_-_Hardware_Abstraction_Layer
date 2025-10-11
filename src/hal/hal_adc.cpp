#include "hal/hal_adc.h"

static adc_driver_t *drv = nullptr;

void HAL::ADC_Init() {
    drv = get_virtual_adc();
    drv->init();
}

float HAL::ADC_Read(uint8_t ch) {
    return drv->read_voltage(ch);
}