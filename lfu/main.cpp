#include "lfucache.hpp"

int main()
{
    using namespace cache;
    size_t hits = 0;
    size_t size = 0;
    size_t num = 0;
    std::cin >> size >> num;
    Cache_t<int> cache{size};

    for(int i = 0; i < num; i++)
    {
        int page = 0;
        std::cin >> page;
        if (!std::cin.good()) std::cerr << "error input\n";
        if(cache.update_cache(page)) hits++;
    }
    std::cout << hits << "\n";
    return 0;
}
