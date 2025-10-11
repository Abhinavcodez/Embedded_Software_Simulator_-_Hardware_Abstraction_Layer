#include "utils/logger.h"
#include <fstream>
#include <ctime>

void Logger::log_to_file(const std::string &fname, const std::string &msg) {
    std::ofstream f(fname, std::ios::app);
    time_t t = std::time(nullptr);
    f << "[" << std::ctime(&t) << "] " << msg << "\n";
}