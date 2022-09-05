#include "map_prelude.hpp"

int main()
{
    SETUP;

    timer t;

    NAMESPACE::map<int, int> m;
    for (std::size_t i = 0; i < MAXSIZE / 2; ++i) {
        m[rand()] = rand();
    }

    PRINT_TIME(t);
}