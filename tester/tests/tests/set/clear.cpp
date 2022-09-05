#include "set_prelude.hpp"

void set_test_clear()
{
    SETUP_ARRAYS();

    {
        strset m;

        PRINT_ALL(m);

        m.clear();

        PRINT_ALL(m);

        m.insert(str_arr, str_arr + 16);

        PRINT_ALL(m);

        m.clear();

        PRINT_ALL(m);
    }
}

MAIN(set_test_clear)
