#include "set_prelude.hpp"

int main()
{
    SETUP;

    NAMESPACE::vector<int> data(MAXSIZE);

    iota(data.begin(), data.end(), rand());

    NAMESPACE::set<int> s;

    timer t;

    for (std::size_t i = 0; i < 5; ++i) {
        t.reset();
        for (NAMESPACE::vector<int>::iterator it = data.begin(); it != data.end(); ++it) {
            s.insert(s.end(), *it);
        }
        sum += t.get_time();
        s.clear();
    }

    PRINT_SUM();
}
