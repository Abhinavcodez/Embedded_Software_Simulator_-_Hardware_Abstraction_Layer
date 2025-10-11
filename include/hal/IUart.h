#pragma once
#include <cstddef>

class IUart {
public:
    virtual ~IUart() = default;
    virtual void send(const char* data, int length) = 0;
    virtual int receive(char* buffer, int length) = 0;
};