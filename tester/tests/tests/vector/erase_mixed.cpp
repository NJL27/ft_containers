#include "vector_prelude.hpp"

void vec_test_erase_mixed()
{
    SETUP_ARRAYS();

    {
        strvector v(b_string, b_string + b_size);

        v.erase(v.begin(), v.begin());

        CHECK_AND_PRINT_ALL(v);

        v.erase(v.end(), v.end());

        CHECK_AND_PRINT_ALL(v);

        v.erase(v.begin());

        CHECK_AND_PRINT_ALL(v);

        v.erase(v.end() - 1);

        CHECK_AND_PRINT_ALL(v);

        v.erase(v.begin() + 3, v.begin() + 16);

        CHECK_AND_PRINT_ALL(v);

        strvector::iterator it = v.erase(v.begin() + 9);

        PRINT_LINE("It:", *it);
        CHECK_AND_PRINT_ALL(v);

        v.erase(v.begin(), v.end());

        CHECK_AND_PRINT_ALL(v);
    }
}

MAIN(vec_test_erase_mixed)
