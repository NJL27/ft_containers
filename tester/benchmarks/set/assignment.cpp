#include "set_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::set<int> data;

    for (std::size_t i = 0; i < MAXSIZE / 2; ++i) {
        data.insert(rand());
    }

    timer t;

    {
        NAMESPACE::set<int> s;
        for (int i = 0; i < 5; ++i) {
            s = data;
        }
    }

    PRINT_TIME(t);
}