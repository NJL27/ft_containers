#include "map_prelude.hpp"

void map_test_clear()
{
    SETUP_ARRAYS();

    {
        strmap m;

        PRINT_ALL(m);

        m.clear();

        PRINT_ALL(m);

        m.insert(strstr_arr, strstr_arr + 16);

        PRINT_ALL(m);

        m.clear();

        PRINT_ALL(m);
    }
}

MAIN(map_test_clear)
