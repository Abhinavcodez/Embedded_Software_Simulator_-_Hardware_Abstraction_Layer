#ifndef IGPIO_H
#define IGPIO_H

class IGpio {
public:
    virtual ~IGpio() = default;
    virtual void write(int pin, bool value) = 0;
    virtual bool read(int pin) = 0;
};

#endif // IGPIO_H