#include "set_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::set<int> data;

    timer t;

    for (std::size_t i = 0; i < MAXSIZE / 2; ++i) {
        data.insert(rand());
    }

    PRINT_TIME(t);
}
