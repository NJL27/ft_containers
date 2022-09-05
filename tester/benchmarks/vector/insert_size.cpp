#include "vector_prelude.hpp"

int main()
{
    SETUP;

    timer t;
    for (int i = 0; i < 2; ++i) {
        NAMESPACE::vector<int> v;

        for (std::size_t i = 0; i < 10000; ++i) {
            v.insert(v.end(), i, rand());
        }
        BLOCK_OPTIMIZATION(v);
    }

    for (int i = 0; i < 2; ++i) {
        NAMESPACE::vector<int> v;

        for (std::size_t i = 0; i < 3000; ++i) {
            v.insert(v.begin(), i, rand());
        }
        for (std::size_t i = 0; i < 3000; ++i) {
            v.insert(v.begin(), 20, rand());
        }
        BLOCK_OPTIMIZATION(v);
    }

    for (int i = 0; i < 2; ++i) {
        NAMESPACE::vector<int> v;

        for (std::size_t i = 0; i < 1000; ++i) {
            v.insert(v.end(), rand());
        }
        for (std::size_t i = 0; i < 3000; ++i) {
            v.insert(v.begin() + 450, i, rand());
        }
        BLOCK_OPTIMIZATION(v);
    }
    PRINT_TIME(t);
}
