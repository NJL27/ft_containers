#include "vector_prelude.hpp"

void vec_test_front()
{
    SETUP_ARRAYS();

    {
        longvector v(1, 9);

        PRINT_LINE("Front:", v.front());

        if (&v.front() != &v[0]) {
            PRINT_MSG("Wrong reference");
        }
    }

    {
        longvector v(123, 543);

        PRINT_LINE("Front:", v.front());

        if (&v.front() != &v[0]) {
            PRINT_MSG("Wrong reference");
        }
    }

    {
        const longvector v(1, 9);

        PRINT_LINE("Front:", v.front());

        longvector::const_reference b = v.front();
        if (&b != &v[0]) {
            PRINT_MSG("Wrong reference");
        }
    }

    {
        const longvector v(123, 543);

        PRINT_LINE("Front:", v.front());

        longvector::const_reference b = v.front();
        if (&b != &v[0]) {
            PRINT_MSG("Wrong reference");
        }
    }
}

MAIN(vec_test_front)
