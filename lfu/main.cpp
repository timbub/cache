#include "lfucache.hpp"
#include <iostream>

int main()
{   size_t hits = 0;
    size_t size = 0;
    size_t num = 0;
    std::cin >> size >> num;
    cache_t<int> cache{size};

    for(int i = 0; i < num; i++)
    {
        int page = 0;
        std::cin >> page;
        if (!std::cin.good()) std::cerr << "error input\n";
        cache.update_cache(page, &cache, &hits);
    }
    std::cout << hits << "\n";
    return 0;
}
