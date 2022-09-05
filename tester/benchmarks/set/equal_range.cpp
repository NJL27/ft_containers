#include "set_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::set<int> data;

    for (std::size_t i = 0; i < MAXSIZE / 2; ++i) {
        data.insert(rand());
    }

    timer t;

    for (int i = 0; i < 10000000; ++i) {
        NAMESPACE::pair<NAMESPACE::set<int>::iterator, NAMESPACE::set<int>::iterator> eq =
            data.equal_range(rand());
        if (eq.first != data.end()) {
            (void)*eq.second;
        }
    }

    PRINT_TIME(t);
}
