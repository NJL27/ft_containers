#include "vector_prelude.hpp"
#include <cstddef>

void vec_test_insert_size()
{
    SETUP_ARRAYS();

    {
        intvector v;

        v.insert(v.begin(), 0, 64);

        CHECK_AND_PRINT_ALL(v);

        v.insert(v.end(), 0, 64);

        CHECK_AND_PRINT_ALL(v);

        v.insert(v.end(), 10, 64);

        CHECK_AND_PRINT_ALL(v);

        v.insert(v.begin(), 5, -1);

        CHECK_AND_PRINT_ALL(v);

        v.insert(v.begin() + 1, 1, -9);

        CHECK_AND_PRINT_ALL(v);

        v.insert(v.begin() + 7, 21, 88);

        CHECK_AND_PRINT_ALL(v);

        v.insert(v.begin(), 0, 2);

        CHECK_AND_PRINT_ALL(v);

        v.insert(v.end(), 0, 4);

        CHECK_AND_PRINT_ALL(v);

        v.insert(v.end(), 18, 420);

        CHECK_AND_PRINT_ALL(v);
    }

    {
        strvector v(5000, "Test");

        try {
            v.insert(v.begin() + 115, (std::size_t)std::numeric_limits<std::ptrdiff_t>::max(),
                     "123");
        } catch (std::length_error&) {
            PRINT_MSG("Length exception");
        }
        CATCH_UNHANDLED_EX();
    }
}

MAIN(vec_test_insert_size)
