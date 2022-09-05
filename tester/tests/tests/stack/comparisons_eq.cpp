#include "stack_prelude.hpp"

void stack_test_comparisons_eq()
{
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        if (v1 == v2) {
            PRINT_MSG("Equal");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 0, 5);

        if (v1 == v2) {
            PRINT_MSG("Equal.");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 0, 8);
        add_values(v2, 0, 9);

        if (v1 == v2) {
            PRINT_MSG("Equal..");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 0, 9);
        add_values(v2, 0, 8);

        if (v1 == v2) {
            PRINT_MSG("Equal...");
        }
    }
    {
        ft::stack<long> v1;
        ft::stack<long> v2;

        add_values(v1, 1, 64);
        add_values(v2, 1, 64);

        if (v1 == v2) {
            PRINT_MSG("Equal....");
        }
    }
}

MAIN(stack_test_comparisons_eq)
