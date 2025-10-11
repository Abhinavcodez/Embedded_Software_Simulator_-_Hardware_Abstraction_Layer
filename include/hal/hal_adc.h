#pragma once
#include "drivers/adc_driver.h"

namespace HAL {
    void ADC_Init();
    float ADC_Read(uint8_t channel);
}