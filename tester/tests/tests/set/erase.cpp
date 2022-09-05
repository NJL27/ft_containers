#include "set_prelude.hpp"

void set_test_erase()
{
    SETUP_ARRAYS();

    {
        intset m(int_arr, int_arr + 25);

        intset::iterator it = m.begin();

        m.erase(it);

        PRINT_ALL(m);

        it = m.begin();

        std::advance(it, 21);

        m.erase(it);

        PRINT_ALL(m);

        it = m.end();

        std::advance(it, -10);

        m.erase(it);

        PRINT_ALL(m);

        it = m.end();

        std::advance(it, -3);

        m.erase(it);

        PRINT_ALL(m);

        it = m.end();

        std::advance(it, -1);

        m.erase(it);

        PRINT_ALL(m);

        it = m.begin();

        std::advance(it, 1);

        m.erase(it);

        PRINT_ALL(m);

        for (it = m.begin(); it != m.end(); it = m.begin()) {
            m.erase(it);
            PRINT_ALL(m);
        }
    }
}

MAIN(set_test_erase)
