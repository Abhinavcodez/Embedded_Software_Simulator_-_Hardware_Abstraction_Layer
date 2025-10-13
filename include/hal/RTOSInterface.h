#pragma once
#include <functional>
#include <string>

class RTOSInterface {
public:
    virtual ~RTOSInterface() = default;
    virtual void create_task(std::function<void()> task, const std::string& name) = 0;
    virtual void start_scheduler() = 0;
    virtual void delay_ms(int ms) = 0;
};