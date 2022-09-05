#include "vector_prelude.hpp"

void vec_test_get_allocator()
{
    intvector v;

    track_allocator<int> alloc = v.get_allocator();

    int* buff = alloc.allocate(2048 * 5);

    std::cout << "a leak is normal here\n";
    leak_checker::check_leaks();

    alloc.deallocate(buff, 2048 * 5);
}

MAIN(vec_test_get_allocator)
