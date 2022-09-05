#include "vector_prelude.hpp"

void vec_test_ctor_size()
{
    SETUP_ARRAYS();

    {
        intvector v(64, 1);

        CHECK_AND_PRINT_ALL(v);
    }

    {
        intvector v(0, -1);

        CHECK_AND_PRINT_ALL(v);
    }

    {
        strvector v(26, b_string[0]);

        CHECK_AND_PRINT_ALL(v);
    }

    {
        strvector v(0, b_string[32]);

        CHECK_AND_PRINT_ALL(v);
    }

    {
        try {
            const std::size_t max_size = NAMESPACE::vector<big_struct>().max_size();
            NAMESPACE::vector<big_struct> v(max_size + 1);

            PRINT_MSG("Allocation shouldve failed");
        } catch (std::length_error& e) {
            PRINT_MSG("Length exception");
        }
        CATCH_UNHANDLED_EX();
    }
}

MAIN(vec_test_ctor_size)
