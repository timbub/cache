#include "idealcache.hpp"
#include <iostream>

int main()
{   size_t hits = 0;
    size_t size = 0;
    size_t num  = 0;

    std::cin >> size >> num;
    cache_t<int, int> cache{size};
    data_t<int>  data{num};

    for(int i = 0; i < num; i++)
    {
        int page = 0;
        std::cin >> page;
        if (!std::cin.good()) std::cerr << "error input\n";
        data.dataset[i] = page;
        data.map[page].push(i);
    }
    cache.update_cache(&hits, &data, num);
    std::cout << hits << std::endl;
    return 0;
}
