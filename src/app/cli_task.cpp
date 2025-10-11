#include <iostream>
#include "../../include/hal/IUart.h"
#include "../../include/utils/thread_safe_queue.h"
#include <atomic>
#include <string>

void cli_task(IUart* uart, ThreadSafeQueue<std::string>& logger_q, std::atomic<bool>& running) {
    std::cout << "[CLI] Running CLI Task..." << std::endl;
}