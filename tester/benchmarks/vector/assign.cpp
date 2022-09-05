#include "vector_prelude.hpp"

int main()
{
    SETUP;

    timer t;

    for (int i = 0; i < 10; ++i) {
        NAMESPACE::vector<int> v;

        v.assign(MAXSIZE, rand());

        BLOCK_OPTIMIZATION(v);
    }

    {
        NAMESPACE::vector<int> v;
        for (int i = 0; i < 10; ++i) {
            v.assign(MAXSIZE, rand());

            BLOCK_OPTIMIZATION(v);
        }
    }

    PRINT_TIME(t);
}
