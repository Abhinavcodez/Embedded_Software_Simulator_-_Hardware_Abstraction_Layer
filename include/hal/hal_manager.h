#ifndef HAL_MANAGER_H
#define HAL_MANAGER_H

#include <memory>
#include "IUart.h"
#include "IGpio.h"

class HalManager {
public:
    static HalManager& instance() {
        static HalManager inst;
        return inst;
    }

    void register_uart(std::unique_ptr<IUart> uart) { uart_ = std::move(uart); }
    void register_gpio(std::unique_ptr<IGpio> gpio) { gpio_ = std::move(gpio); }

    IUart* uart() { return uart_.get(); }
    IGpio* gpio() { return gpio_.get(); }

private:
    HalManager() = default;
    std::unique_ptr<IUart> uart_;
    std::unique_ptr<IGpio> gpio_;
};

#endif // HAL_MANAGER_H