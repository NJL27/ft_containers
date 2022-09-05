#pragma once

#include <sys/time.h>

class timer
{
public:
    timer();

public:
    long get_time();
    void reset();

private:
    struct timeval stamp;
};
