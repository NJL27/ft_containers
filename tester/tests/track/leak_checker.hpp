#pragma once

#include "memory_tracker.hpp"

class leak_checker
{
public:
    static void check_leaks();
    static void check_alive_objects();
    static void check_all();

private:
    static memory_tracker tracker;
};
