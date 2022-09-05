#include "vector_prelude.hpp"

void vec_test_ctor_range()
{
    SETUP_ARRAYS();

    {
        doublevector v(s_double, s_double + s_size);

        CHECK_AND_PRINT_ALL(v);
    }

    {
        strvector v1(s_string, s_string + s_size);

        CHECK_AND_PRINT_ALL(v1);

        strvector v2(v1.begin(), v1.end());

        CHECK_AND_PRINT_ALL(v2);

        if (&v1[0] == &v2[0]) {
            PRINT_MSG("Copy ctor doesn't do a deep copy!");
        }
    }

    {
        std::string str = "Hello World!";
        charvector v(str.begin(), str.end());

        CHECK_AND_PRINT_ALL(v);
    }

    {
        // This test checks if vector works with iterators tagged as std::input_iterator_tag
        std::istringstream str("");
        std::istreambuf_iterator<char> it(str), end;

        charvector v(it, end);

        CHECK_AND_PRINT_ALL(v);
    }

    {
        // This test checks if vector works with iterators tagged as std::input_iterator_tag
        std::istringstream str("1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        std::istreambuf_iterator<char> it(str), end;

        charvector v(it, end);

        CHECK_AND_PRINT_ALL(v);
    }
}

MAIN(vec_test_ctor_range)
