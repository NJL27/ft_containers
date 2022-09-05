#include "map_prelude.hpp"

void map_test_get_allocator()
{
    intmap m;

    track_allocator<NAMESPACE::pair<const int, std::string> > alloc = m.get_allocator();

    NAMESPACE::pair<const int, std::string>* buff = alloc.allocate(64);

    alloc.deallocate(buff, 64);
}

MAIN(map_test_get_allocator)
