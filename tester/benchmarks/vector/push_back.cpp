#include "vector_prelude.hpp"

int main()
{
    SETUP;

    timer t;
    for (int i = 0; i < 3; ++i) {
        NAMESPACE::vector<int> v;

        for (std::size_t i = 0; i < MAXSIZE; ++i) {
            v.push_back(rand());
        }

        BLOCK_OPTIMIZATION(v);
    }

    PRINT_TIME(t);
}
