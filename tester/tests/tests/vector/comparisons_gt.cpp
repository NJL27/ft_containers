#include "vector_prelude.hpp"

void vec_test_comparisons_gt()
{
    {
        NAMESPACE::vector<long> v1;
        NAMESPACE::vector<long> v2;

        if (v1 > v2) {
            PRINT_MSG("Greater than");
        }
    }

    {
        NAMESPACE::vector<long> v1(5, 64);
        NAMESPACE::vector<long> v2;

        if (v1 > v2) {
            PRINT_MSG("Greater than.");
        }
    }

    {
        NAMESPACE::vector<long> v1;
        NAMESPACE::vector<long> v2(5, 32);

        if (v1 > v2) {
            PRINT_MSG("Greater than..");
        }
    }

    {
        NAMESPACE::vector<long> v1(5, 64);
        NAMESPACE::vector<long> v2(5, 48);

        if (v1 > v2) {
            PRINT_MSG("Greater than...");
        }
    }

    {
        NAMESPACE::vector<long> v1(5, 64);
        NAMESPACE::vector<long> v2(5, 64);

        if (v1 > v2) {
            PRINT_MSG("Greater than...");
        }
    }

    {
        NAMESPACE::vector<long> v1(5, 64);
        NAMESPACE::vector<long> v2(4, 64);

        if (v1 > v2) {
            PRINT_MSG("Greater than....");
        }
    }

    {
        NAMESPACE::vector<long> v1(4);
        NAMESPACE::vector<long> v2(5);

        if (v1 > v2) {
            PRINT_MSG("Greater than.....");
        }
    }
}

MAIN(vec_test_comparisons_gt)
