#include <gtest/gtest.h>
#include <cstdlib>
#include "lfucache.hpp"

template <typename T>
struct test_t
{
    size_t size;
    size_t num;
    std::vector<T> data;
    size_t hits;

};


TEST(EndToEnd, In_Out)
{
    size_t num_tests = 6;
    test_t<int> tests[] = {{2, 6, {1, 2, 1, 2, 1, 2}, 4},
                      {3, 8, {1, 2, 3, 1, 2, 4, 1, 5}, 3},
                      {5, 4, {1, 2, 3, 4}, 0},
                      {2, 5, {1, 2, 3, 4, 5}, 0},
                      {4, 13, {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 6, 7, 1}, 5},
                      {3, 9, {1, 2, 3, 1, 2, 3, 1, 2, 3}, 6}};
    for(int i = 0; i < num_tests; i++)
    {
        size_t hits = 0;
        size_t size = tests[i].size;
        size_t num = tests[i].num;
        cache_t<int> cache{size};
        for(int j = 0; j < num; j++)
        {
            cache.update_cache(tests[i].data[j], &hits);
        }
        EXPECT_EQ (hits, tests[i].hits);
    }
}


