#include "vector_prelude.hpp"

int main()
{
    SETUP;

    timer t;
    for (int i = 0; i < 10; ++i) {
        NAMESPACE::vector<int> v(MAXSIZE, rand());

        BLOCK_OPTIMIZATION(v);
    }

    PRINT_TIME(t);
}
