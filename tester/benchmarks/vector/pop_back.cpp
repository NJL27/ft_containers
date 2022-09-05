#include "vector_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::vector<int> data;

    for (std::size_t i = 0; i < MAXSIZE; ++i) {
        data.push_back(rand());
    }

    timer t;

    for (int i = 0; i < 5; ++i) {
        NAMESPACE::vector<int> v = data;

        BLOCK_OPTIMIZATION(v);

        while (!v.empty()) {
            v.pop_back();
        }
    }

    PRINT_TIME(t);
}
