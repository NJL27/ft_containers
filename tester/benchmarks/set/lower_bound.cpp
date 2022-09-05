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
        NAMESPACE::set<int>::iterator it = data.lower_bound(rand());
        if (it != data.end()) {
            (void)*it;
        }
    }

    PRINT_TIME(t);
}
