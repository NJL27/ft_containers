#include "map_prelude.hpp"

void map_test_swap()
{
    SETUP_ARRAYS();

    {
        intmap m1(intstr_arr, intstr_arr + 32);
        intmap m2;

        NAMESPACE::swap(m1, m2);

        PRINT_ALL(m1);
        PRINT_ALL(m2);

        m1.clear();
        m1.swap(m2);

        PRINT_ALL(m1);
        PRINT_ALL(m2);

        m1.clear();
        m2.swap(m1);

        PRINT_ALL(m1);
        PRINT_ALL(m2);

        m1.insert(NAMESPACE::make_pair(64, "N64"));
        NAMESPACE::swap(m1, m2);

        PRINT_ALL(m1);
        PRINT_ALL(m2);

        m2.insert(intstr_arr, intstr_arr + intstr_size);
        m1.swap(m2);

        PRINT_ALL(m1);
        PRINT_ALL(m2);

        m1.clear();
        m1.swap(m2);
        m1.clear();
        m1.swap(m2);

        PRINT_ALL(m1);
        PRINT_ALL(m2);
    }
}

MAIN(map_test_swap)
