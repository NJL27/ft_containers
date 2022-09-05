#include "map_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::map<int, int> data;

    for (std::size_t i = 0; i < MAXSIZE / 2; ++i) {
        data.insert(NAMESPACE::make_pair(rand(), rand()));
    }

    timer t;

    {
        NAMESPACE::map<int, int> m;
        for (int i = 0; i < 5; ++i) {
            m = data;
        }
    }

    PRINT_TIME(t);
}