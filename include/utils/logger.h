#pragma once
#include <string>

namespace Logger {
    void log_to_file(const std::string &fname, const std::string &msg);
}