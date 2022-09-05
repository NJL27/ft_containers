#include "map_prelude.hpp"

void map_test_insert_hint()
{
    SETUP_ARRAYS();

    {
        intmap m;

        intmap::iterator it = m.insert(m.end(), NAMESPACE::make_pair(64, "Gamepak"));

        PRINT_PAIR_REF(*it);

        it = m.insert(m.end(), NAMESPACE::make_pair(64, "Test"));

        PRINT_PAIR_REF(*it);

        it = m.insert(m.end(), NAMESPACE::make_pair(100, "100$"));

        PRINT_PAIR_REF(*it);

        it = m.end();
        --it;

        it = m.insert(it, NAMESPACE::make_pair(100, "12345"));

        PRINT_PAIR_REF(*it);

        it = m.insert(it, NAMESPACE::make_pair(69, "420"));

        PRINT_PAIR_REF(*it);
    }
}

MAIN(map_test_insert_hint)
