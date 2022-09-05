#include "vector_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::vector<int> data;

    for (std::size_t i = 0; i < MAXSIZE; ++i) {
        data.push_back(rand());
    }

    timer t;

    {
        NAMESPACE::vector<int> v = data;

        t.reset();
        for (int i = 0; i < 10; ++i) {
            v = data;
            BLOCK_OPTIMIZATION(v);
        }
    }

    for (int i = 0; i < 10; ++i) {
        NAMESPACE::vector<int> v;
        v = data;
        BLOCK_OPTIMIZATION(v);
    }

    PRINT_TIME(t);
}
