#include "vector_prelude.hpp"

void vec_test_index_operator()
{
    SETUP_ARRAYS();

    {
        intvector v(s_int, s_int + s_size);

        PRINT_LINE("Index 0:", v[0]);

        intvector::reference value = v[26];

        PRINT_LINE("Index 26:", value);

        value = -64;

        CHECK_AND_PRINT_ALL(v);

        intvector::reference value2 = v[31];

        PRINT_LINE("Index 31:", value2);

        value2 = -1;

        CHECK_AND_PRINT_ALL(v);

        v[14] = 0;

        CHECK_AND_PRINT_ALL(v);
    }

    {
        const intvector v(s_int, s_int + s_size);

        PRINT_LINE("Index 0:", v[0]);

        intvector::const_reference value = v[26];

        PRINT_LINE("Index 26:", value);

        intvector::const_reference value2 = v[31];

        PRINT_LINE("Index 31:", value2);

        CHECK_AND_PRINT_ALL(v);
    }
}

MAIN(vec_test_index_operator)
