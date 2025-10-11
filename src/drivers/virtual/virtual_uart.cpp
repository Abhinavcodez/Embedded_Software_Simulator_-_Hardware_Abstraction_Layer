// src/drivers/virtual/virtual_uart.cpp
#include "hal/hal_uart.h"
#include "utils/thread_safe_queue.h"
#include <thread>
#include <atomic>
#include <fstream>
#include <mutex>
#include <chrono>

using namespace std::chrono_literals;

class VirtualUart : public IUart {
public:
    VirtualUart(const std::string &log_path = "/tmp/virtual_uart.log", bool loopback=true)
        : log_path_(log_path), loopback_(loopback), running_(false) {}

    ~VirtualUart() {
        running_ = false;
        if (rx_thread_.joinable()) rx_thread_.join();
    }

    bool init() override {
        log_.open(log_path_, std::ios::app);
        running_ = true;
        // background thread that dispatches incoming bytes to callback (if set)
        rx_thread_ = std::thread([this]{
            while (running_) {
                uint8_t b;
                if (rx_queue_.try_pop(b)) {
                    std::lock_guard<std::mutex> lk(cb_mtx_);
                    if (cb_) cb_(b);
                } else {
                    std::this_thread::sleep_for(5ms);
                }
            }
        });
        return (bool)log_;
    }

    void write(const uint8_t* data, size_t len) override {
        if (!log_) return;
        // log human readable and raw
        log_.write(reinterpret_cast<const char*>(data), len);
        log_.flush();

        // if loopback - make the written bytes appear in RX (for CLI testing)
        if (loopback_) {
            for (size_t i=0;i<len;++i) rx_queue_.push(data[i]);
        }
    }

    bool read(uint8_t &out) override {
        return rx_queue_.try_pop(out);
    }

    void set_callback(uart_callback_t cb) override {
        std::lock_guard<std::mutex> lk(cb_mtx_);
        cb_ = cb;
    }

private:
    std::string log_path_;
    bool loopback_;
    std::ofstream log_;
    ThreadSafeQueue<uint8_t> rx_queue_;
    std::thread rx_thread_;
    std::atomic<bool> running_;
    std::mutex cb_mtx_;
    uart_callback_t cb_;
};