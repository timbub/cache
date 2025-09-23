#include <gtest/gtest.h>
#include <cstdlib>
#include "idealcache.hpp"

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
    test_t<int> tests[] = {
    {
        2,
        8,
        {1, 2, 5, 1, 3, 5, 2, 1},
        3
    },
    {
        3,
        9,
        {1, 2, 3, 4, 1, 2, 5, 3, 4},
        3
    },
    {
        3,
        10,
        {1, 2, 3, 1, 2, 3, 5, 1, 2, 3},
        6
    },
    {
        4,
        13,
        {10, 20, 30, 40, 10, 20, 30, 50, 40, 60, 10, 20, 30},
        7
    },
    {
        5,
        15,
        {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 1, 2, 3, 4, 5},
        4
    },
    {
        3,
        15,
        {1, 2, 3, 1, 2, 3, 1, 2, 5, 1, 2, 3, 1, 2, 3},
        11
    }};

    for(int i = 0; i < num_tests; i++)
    {
        size_t hits = 0;
        size_t size = tests[i].size;
        size_t num = tests[i].num;
        cache_t<int> cache{size};
        data_t<int>  data{num};

        for(int j = 0; j < num; j++)
        {
            int page = tests[i].data[j];
            data.dataset[j] = page;
            data.hash[page].push(i);
        }
        cache.update_cache(&hits, &data, num);
        EXPECT_EQ (hits, tests[i].hits);
    }
}


