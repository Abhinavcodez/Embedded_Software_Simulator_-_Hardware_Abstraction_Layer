#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>

enum class GpioState { LOW = 0, HIGH = 1 };
using Pin = uint8_t;

class VirtualGPIO {
public:
    static void init();
    static void write(Pin pin, GpioState state);
    static GpioState read(Pin pin);
    static void toggle(Pin pin);
private:
    static std::unordered_map<Pin, GpioState> pins;
};