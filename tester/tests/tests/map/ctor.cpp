#include "map_prelude.hpp"

void map_test_ctor()
{
    // Default
    {
        intmap m;

        PRINT_ALL(m);
    }

    // Compare/Allocator
    {
        track_allocator<NAMESPACE::pair<const std::string, std::string> > alloc;
        strmap m(std::less<std::string>(), alloc);

        PRINT_ALL(m);
    }
}

MAIN(map_test_ctor)
