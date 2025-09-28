#pragma once
#include <list>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstddef>
#include <iostream>

template <typename T>
struct data_t
{
    size_t size;
    using hash_t = std::unordered_map<T, std::queue<size_t>>;
    hash_t map;
    std::vector<T> dataset;
    data_t(size_t sz) : size(sz), dataset(sz) {};
};

template <typename T, typename Position>
class cache_t
{
private:
    size_t size;
    std::unordered_map<T, typename std::multimap<Position, T>::iterator> cache_map;
    std::multimap<Position, T> cache_heap;
public:
    void update_cache(size_t* hits, data_t<T>* data, size_t num)
    {
        for(int i = 0; i < data->size; i++)
        {
            //std::cout << "new page" << std::endl;
            T page = data->dataset[i];

            auto it_data_page = data->map.find(page);
            if(it_data_page == data->map.end()) continue;

            size_t position_page = num + 1;
            if(!it_data_page->second.empty()) it_data_page->second.pop();
            if(!it_data_page->second.empty()) position_page = it_data_page->second.front();

            auto it_cache_page = cache_map.find(page);
            if(it_cache_page == cache_map.end())
            {
                size_t current_size  = cache_heap.size();
                if(current_size >= size)
                {
                    auto it_delete = std::prev(cache_heap.end());
                    //std::cout << " potential delete " << it_delete->second << std::endl;
                    if (it_delete != cache_heap.end() && it_delete->first > position_page)
                    {
                        cache_map.erase(it_delete->second);
                        cache_heap.erase(it_delete);

                        auto it_new = cache_heap.insert({position_page ,page});
                        //std::cout << "add to full " << page << std::endl;
                        cache_map[page] = it_new; //позиция ключ
                    }
                }
                else
                {
                    auto it_new = cache_heap.insert({position_page ,page});
                    //std::cout << "add " << page << std::endl;
                    cache_map[page] = it_new;
                }
            } else
            {
                cache_heap.erase(it_cache_page->second);
                auto it_new = cache_heap.insert({position_page ,page});
                //std::cout << "hit " << page << std::endl;
                cache_map[page] = it_new;
                (*hits)++;
            }
            // for (const auto &p : cache_heap) {
            // std::cout << p.first << " -> " << p.second << "\n";
            // }
        }
    }
    cache_t(size_t sz) : size(sz) {};
};

