#include "vector_prelude.hpp"

void vec_test_resize()
{
    SETUP_ARRAYS();

    {
        strvector v;

        v.resize(14, "HelloWorld");

        CHECK_AND_PRINT_ALL(v);

        v.resize(6, "ABC");

        CHECK_AND_PRINT_ALL(v);

        v.resize(14, b_string[18]);

        CHECK_AND_PRINT_ALL(v);

        v.resize(15, b_string[57]);

        CHECK_AND_PRINT_ALL(v);

        v.resize(64, "I-like-vectors");

        CHECK_AND_PRINT_ALL(v);
    }

    {
        NAMESPACE::vector<big_struct, track_allocator<big_struct> > v;

        try {
            v.resize(v.max_size() + 1);
            PRINT_MSG("Bad reserve");
        } catch (std::length_error&) {
            PRINT_MSG("Length exception");
        }
        CATCH_UNHANDLED_EX();
    }
}

MAIN(vec_test_resize)
