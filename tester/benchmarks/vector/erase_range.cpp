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

        t.reset();
        v.erase(v.begin(), v.end());
        sum += t.get_time();
    }

    NAMESPACE::vector<int> v(data.begin(), data.end());
    for (int i = 0; i < 10; ++i) {
        BLOCK_OPTIMIZATION(v);

        t.reset();
        v.erase(v.begin() + 1000, v.begin() + 200000);
        sum += t.get_time();
    }

    PRINT_SUM();
}
