#include "map_prelude.hpp"

void map_test_index_operator()
{
    SETUP_ARRAYS();

    {
        intmap m(intstr_arr, intstr_arr + intstr_size);

        PRINT_SIZE(m);
        PRINT_LINE("Value:", m[64]);
        PRINT_SIZE(m);

        m[64] = "Hello";

        PRINT_SIZE(m);
        PRINT_LINE("Value:", m[64]);
        PRINT_SIZE(m);

        PRINT_SIZE(m);
        PRINT_LINE("Value:", m[0]);
        PRINT_SIZE(m);

        m[0] = "ABCDEF";

        PRINT_SIZE(m);
        PRINT_LINE("Value:", m[0]);
        PRINT_SIZE(m);
    }

    {
        strmap m(strstr_arr, strstr_arr + strstr_size);

        PRINT_SIZE(m);
        PRINT_LINE("Value:", m["Index"]);
        PRINT_SIZE(m);

        m["Index"] = "World";

        PRINT_SIZE(m);
        PRINT_LINE("Value:", m["Index"]);
        PRINT_SIZE(m);

        m["abcd"] = "World";

        PRINT_SIZE(m);
        PRINT_LINE("Value:", m["abcd"]);
        PRINT_SIZE(m);
    }
}

MAIN(map_test_index_operator)
