#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <string>

class Diagnostics {
public:
    static void report(const std::string& msg);
};

#endif // DIAGNOSTICS_H