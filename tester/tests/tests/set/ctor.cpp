#include "set_prelude.hpp"

void set_test_ctor()
{
    // Default
    {
        intset m;

        PRINT_ALL(m);
    }

    // Compare/Allocator
    {
        track_allocator<NAMESPACE::pair<const std::string, std::string> > alloc;
        strset m(std::less<std::string>(), alloc);

        PRINT_ALL(m);
    }
}

MAIN(set_test_ctor)
