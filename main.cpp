#include "cache.h"
#include <iostream>

int main()
{   size_t hits = 0;
    size_t size = 0;
    size_t num = 0;
    std::cin >> size >> num;
    cache_t<int, int> cache{size};

    for(int i = 0; i < num; i++)
    {
        int page = 0;
        std::cin >> page;
        if (!std::cin.good()) std::cerr << "error input\n";
        //processing list + hash and посчитать хит если
        // функция bool
    }
    std::cout << hits << "\n";
    return 0;
}
