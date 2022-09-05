#include "set_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::vector<int> data;

    for (std::size_t i = 0; i < MAXSIZE / 4; ++i) {
        data.push_back(rand());
    }

    NAMESPACE::set<int> s;

    timer t;

    for (std::size_t i = 0; i < 2; ++i) {
        s.insert(data.begin(), data.end());
    }
    sum += t.get_time();

    NAMESPACE::set<int> s2;
    for (std::size_t i = 0; i < 5; ++i) {
        t.reset();
        s2.insert(s.begin(), s.end());
        sum += t.get_time();
        s2.clear();
    }

    PRINT_SUM();
}
