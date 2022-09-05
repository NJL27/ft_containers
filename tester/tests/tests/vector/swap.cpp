#include "vector_prelude.hpp"
#include <algorithm>

void vec_test_swap()
{
    SETUP_ARRAYS();

    {
        strvector v1(s_string, s_string + s_size);
        strvector v2(b_string, b_string + b_size);

        v1.swap(v2);

        CHECK_AND_PRINT_ALL(v1);
        CHECK_AND_PRINT_ALL(v2);

        NAMESPACE::swap(v1, v2);

        CHECK_AND_PRINT_ALL(v1);
        CHECK_AND_PRINT_ALL(v2);

        v1.resize(0);

        v1.swap(v2);

        CHECK_AND_PRINT_ALL(v1);
        CHECK_AND_PRINT_ALL(v2);

        v1.resize(0);

        NAMESPACE::swap(v1, v2);

        CHECK_AND_PRINT_ALL(v1);
        CHECK_AND_PRINT_ALL(v2);
    }
}

MAIN(vec_test_swap)
