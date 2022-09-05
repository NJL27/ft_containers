#include "map_prelude.hpp"

void map_test_comparisons_eq()
{
    SETUP_ARRAYS();

    {
        intmap m;
        intmap n;

        if (m == n) {
            PRINT_MSG("Equal");
        }
    }

    {
        intmap m(intstr_arr, intstr_arr + 1);
        intmap n;

        if (m == n) {
            PRINT_MSG("Equal.");
        }
    }

    {
        intmap m(intstr_arr, intstr_arr + 1);
        intmap n;

        if (n == m) {
            PRINT_MSG("Equal..");
        }
    }

    {
        intmap m(intstr_arr, intstr_arr + 1);
        intmap n(intstr_arr, intstr_arr + 1);

        if (n == m) {
            PRINT_MSG("Equal...");
        }
    }

    {
        intmap m(intstr_arr, intstr_arr + intstr_size);
        intmap n(intstr_arr, intstr_arr + intstr_size);

        if (n == m) {
            PRINT_MSG("Equal....");
        }
    }

    {
        intmap m(intstr_arr, intstr_arr + 5);
        intmap n;

        n.insert(NAMESPACE::make_pair(5, "Hello"));
        n.insert(NAMESPACE::make_pair(7, "Hello"));
        n.insert(NAMESPACE::make_pair(8, "Hello"));
        n.insert(NAMESPACE::make_pair(1, "Hello"));
        n.insert(NAMESPACE::make_pair(0, "Hello"));

        if (n == m) {
            PRINT_MSG("Equal.....");
        }
    }

    {
        intmap m(intstr_arr, intstr_arr + 5);
        intmap n(intstr_arr, intstr_arr + 4);

        n.insert(NAMESPACE::make_pair(5, "Hello"));

        if (n == m) {
            PRINT_MSG("Equal......");
        }
    }
}

MAIN(map_test_comparisons_eq)
