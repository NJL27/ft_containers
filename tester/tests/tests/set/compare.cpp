#include "set_prelude.hpp"
#include <functional>

void set_test_compare()
{
    SETUP_ARRAYS();

    {
        NAMESPACE::set<int, std::greater<int>, track_allocator<int> > s(int_arr,
                                                                        int_arr + int_size);

        PRINT_ALL(s);
    }
}

MAIN(set_test_compare)
