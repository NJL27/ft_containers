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
        NAMESPACE::vector<int> v(data.begin(), data.end());

        t.reset();
        while (!v.empty()) {
            v.erase(v.end() - 1);
        }
        sum += t.get_time();
        BLOCK_OPTIMIZATION(v);
    }

    for (int i = 0; i < 5; ++i) {
        NAMESPACE::vector<int> v(data.begin(), data.begin() + 200000);

        t.reset();
        while (!v.empty()) {
            v.erase(v.begin());
        }
        sum += t.get_time();
        BLOCK_OPTIMIZATION(v);
    }

    PRINT_SUM();
}
