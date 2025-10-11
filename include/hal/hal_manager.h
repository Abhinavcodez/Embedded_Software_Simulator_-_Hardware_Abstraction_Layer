#pragma once
#include <memory>
#include "IUart.h"
#include "IGpio.h"

class HalManager {
public:
    static HalManager& instance() {
        static HalManager inst;
        return inst;
    }

    void register_uart(std::unique_ptr<IUart> u) { uart_ = std::move(u); }
    void register_gpio(std::unique_ptr<IGpio> g) { gpio_ = std::move(g); }

    IUart* uart() { return uart_.get(); }
    IGpio* gpio() { return gpio_.get(); }

private:
    HalManager() = default;
    std::unique_ptr<IUart> uart_;
    std::unique_ptr<IGpio> gpio_;
};