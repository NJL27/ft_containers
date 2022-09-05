#include "map_prelude.hpp"

void map_test_empty()
{
    SETUP_ARRAYS();

    {
        strmap m;

        PRINT_LINE("Empty:", m.empty() ? "true" : "false");

        m.insert(NAMESPACE::make_pair("Hello", "World"));

        PRINT_LINE("Empty:", m.empty() ? "true" : "false");

        m.erase(m.begin());

        PRINT_LINE("Empty:", m.empty() ? "true" : "false");
    }

    {
        intmap m(intstr_arr, intstr_arr + intstr_size);

        PRINT_LINE("Empty:", m.empty() ? "true" : "false");
    }
}

MAIN(map_test_empty)
