#include "lfucache.hpp"

int main()
{
    using namespace cache;
    size_t hits = 0;
    size_t size = 0;
    size_t num = 0;
    std::cin >> size >> num;
    Cache_t<int,int> cache{size};

    for(int i = 0; i < num; i++)
    {
        int key = 0;
        std::cin >> key;
        if (!std::cin.good()) std::cerr << "error input\n";
        if(cache.update_cache(key, slow_get_page<int,int>)) hits++;
    }
    std::cout << hits << "\n";
    return 0;
}
