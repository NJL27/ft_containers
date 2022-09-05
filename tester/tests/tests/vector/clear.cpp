#include "vector_prelude.hpp"

void vec_test_clear()
{
    {
        intvector v;

        CHECK_AND_PRINT_ALL(v);

        v.clear();

        CHECK_AND_PRINT_ALL(v);
    }

    {
        intvector v(1, 64);

        CHECK_AND_PRINT_ALL(v);

        v.clear();

        CHECK_AND_PRINT_ALL(v);

        v.clear();

        CHECK_AND_PRINT_ALL(v);
    }

    {
        intvector v(64, 420);

        CHECK_AND_PRINT_ALL(v);

        v.clear();

        CHECK_AND_PRINT_ALL(v);

        v.clear();

        CHECK_AND_PRINT_ALL(v);
    }
}

MAIN(vec_test_clear)
