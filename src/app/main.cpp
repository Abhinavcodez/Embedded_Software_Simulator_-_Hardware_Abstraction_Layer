// src/app/main.cpp
#include "hal/hal_uart.h"
#include "utils/thread_safe_queue.h"
#include <memory>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <random>

// forward-declare VirtualUart (or include its header)
extern std::unique_ptr<IUart> create_virtual_uart(const std::string& path, bool loopback);

using namespace std::chrono_literals;

struct SensorSample { double temp; double press; double hum; uint64_t ts; };

// Simple moving average filter
class MovingAverage {
    double sum = 0;
    size_t window;
    std::deque<double> q;
public:
    explicit MovingAverage(size_t w=5):window(w){}
    double update(double v) {
        q.push_back(v); sum += v;
        if (q.size() > window) { sum -= q.front(); q.pop_front(); }
        return sum / q.size();
    }
};

// sensors produce samples and push to processing queue
void sensor_task(ThreadSafeQueue<SensorSample>& q, std::atomic<bool>& running) {
    std::mt19937 rng(0);
    std::normal_distribution<double> noise(0.0, 0.2);
    while (running) {
        SensorSample s;
        s.temp = 25.0 + noise(rng);
        s.press = 1013.25 + noise(rng);
        s.hum = 40.0 + noise(rng);
        s.ts = (uint64_t)std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::system_clock::now().time_since_epoch()).count();
        q.push(s);
        std::this_thread::sleep_for(100ms);
    }
}

// processing: filter + produce log lines to logger queue
void processing_task(ThreadSafeQueue<SensorSample>& inq,
                     ThreadSafeQueue<std::string>& outq,
                     std::atomic<bool>& running) {
    MovingAverage mtemp(8);
    while (running) {
        SensorSample s = inq.pop();
        double ft = mtemp.update(s.temp);
        char buf[200];
        int n = snprintf(buf, sizeof(buf), "%llu, temp=%.2f filt=%.2f press=%.2f hum=%.2f\n",
                        (unsigned long long)s.ts, s.temp, ft, s.press, s.hum);
        outq.push(std::string(buf, n));
    }
}

// simple logger that writes to a file (virtual SD)
void logger_task(ThreadSafeQueue<std::string>& q, std::atomic<bool>& running) {
    std::ofstream sd("virtual_sd_log.txt", std::ios::app);
    while (running) {
        std::string line = q.pop();
        sd << line;
        sd.flush();
    }
}

// CLI: listens via callback on UART and sends commands to logger
void cli_task(IUart* uart, ThreadSafeQueue<std::string>& logger_q, std::atomic<bool>& running) {
    // set callback to collect bytes into line buffer
    std::string buf;
    uart->set_callback([&](uint8_t b){
        if (b == '\n' || b == '\r') {
            logger_q.push(std::string("CLI_CMD: ")+buf+"\n");
            buf.clear();
        } else buf.push_back((char)b);
    });
    while (running) std::this_thread::sleep_for(200ms);
}

int main(int argc, char** argv) {
    // create virtual UART (factory function implemented in virtual uart file)
    std::unique_ptr<IUart> uart = create_virtual_uart("/tmp/virtual_uart.log", true);
    if (!uart->init()) { std::cerr<<"UART init failed\n"; return 1; }

    ThreadSafeQueue<SensorSample> sensor_q;
    ThreadSafeQueue<std::string> log_q;

    std::atomic<bool> running{true};
    std::thread ts(sensor_task, std::ref(sensor_q), std::ref(running));
    std::thread tp(processing_task, std::ref(sensor_q), std::ref(log_q), std::ref(running));
    std::thread tl(logger_task, std::ref(log_q), std::ref(running));
    std::thread tcli(cli_task, uart.get(), std::ref(log_q), std::ref(running));

    std::cout<<"Sim running. Type text into /tmp/virtual_uart.log loopback (or write to the VirtualUart) to send CLI commands.\n";
    // run for 10s for demo
    std::this_thread::sleep_for(10s);
    running = false;
    // push wakeups to unblock threads if needed
    log_q.push("shutdown\n");
    sensor_q.push(SensorSample{}); // unblock
    ts.join(); tp.join(); tl.join(); tcli.join();
    std::cout<<"Sim stopped\n";
    return 0;
}