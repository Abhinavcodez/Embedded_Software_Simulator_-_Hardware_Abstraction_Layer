#include "utils/config_manager.h"
#include <map>

static std::map<std::string, std::string> cfg;

void Config::save_config(const std::string &key, const std::string &value) {
    cfg[key] = value;
}

std::string Config::load_config(const std::string &key) {
    return cfg.count(key) ? cfg[key] : "";
}