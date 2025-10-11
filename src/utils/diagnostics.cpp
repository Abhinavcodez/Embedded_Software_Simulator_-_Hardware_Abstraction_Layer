#include "../../include/utils/diagnostics.h"
#include <iostream>

void Diagnostics::report(const std::string &msg) {
    std::cout << "[Diagnostics] " << msg << std::endl;
}
