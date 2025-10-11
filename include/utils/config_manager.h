#pragma once
#include <string>

namespace Config {
    void save_config(const std::string &key, const std::string &value);
    std::string load_config(const std::string &key);
}