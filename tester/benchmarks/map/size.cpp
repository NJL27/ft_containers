#include "map_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::vector<NAMESPACE::pair<int, int> > data;

    for (std::size_t i = 0; i < MAXSIZE; ++i) {
        data.push_back(NAMESPACE::make_pair(rand(), rand()));
    }

    NAMESPACE::map<int, int> m(data.begin(), data.begin() + 2500000);

    timer t;

    for (int i = 0; i < 20; ++i) {
        size_t s = m.size();
        if (s > 97) {
            m.erase(m.begin());
        }
    }

    PRINT_TIME(t);
}