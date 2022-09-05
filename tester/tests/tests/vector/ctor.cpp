#include "vector_prelude.hpp"

void vec_test_ctor()
{
    // Default
    {
        longvector v;

        CHECK_AND_PRINT_ALL(v);
    }

    // Allocator ctor
    {
        track_allocator<char> alloc;
        NAMESPACE::vector<char, track_allocator<char> > v(alloc);

        CHECK_AND_PRINT_ALL(v);
    }
}

MAIN(vec_test_ctor)
