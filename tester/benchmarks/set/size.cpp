#include "set_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::vector<int> data;

    for (std::size_t i = 0; i < MAXSIZE; ++i) {
        data.push_back(rand());
    }

    NAMESPACE::set<int> s(data.begin(), data.begin() + 2500000);

    timer t;

    for (int i = 0; i < 20; ++i) {
        size_t size = s.size();
        if (size > 1235) {
            s.erase(s.begin());
        }
    }

    PRINT_TIME(t);
}
