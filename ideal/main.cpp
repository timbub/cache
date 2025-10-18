#include "idealcache.hpp"
#include <iostream>

int main()
{   size_t hits = 0;
    size_t size = 0;
    size_t num  = 0;
    std::cin >> size >> num;

    using namespace cache;
    cache_t<int, int> cache{size};
    data_t<int>  data{num};

    for(int i = 0; i < num; i++)
    {
        int key = 0;
        std::cin >> key;
        if (!std::cin.good()) std::cerr << "error input\n";
        int page = slow_get_page<int,int>(key);
        data.dataset[i] = page;
        data.map[page].push(i);
    }
    for(int i = 0; i < data.size; i++)
    {
        if(cache.update_cache(data.dataset[i], &data, num)) hits++;
    }
    std::cout << hits << std::endl;
    return 0;
}
