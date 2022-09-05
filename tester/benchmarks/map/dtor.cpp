#include "map_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::vector<NAMESPACE::pair<int, int> > data;

    for (std::size_t i = 0; i < MAXSIZE; ++i) {
        data.push_back(NAMESPACE::make_pair(rand(), rand()));
    }

    timer t;

    for (int i = 0; i < 5; ++i) {
        sum += t.get_time();
        NAMESPACE::map<int, int> m(data.begin(), data.begin() + 2500000);
        t.reset();
    }

    PRINT_SUM();
}