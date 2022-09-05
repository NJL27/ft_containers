#include "map_prelude.hpp"
#include <functional>

void map_test_compare()
{
    SETUP_ARRAYS();

    {
        NAMESPACE::map<int, std::string, std::greater<int>,
                       track_allocator<NAMESPACE::pair<const int, std::string> > >
            m(intstr_arr, intstr_arr + intstr_size);

        PRINT_ALL(m);
    }
}

MAIN(map_test_compare)
