#pragma once
#include <vector>
#include <unordered_map>
#include <map>
#include <queue>
#include <cstddef>

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
    std::unordered_map<T, typename std::map<Position, T>::iterator> cache_map;
    std::map<Position, T> cache_heap;
public:
    bool update_cache(const T& page, data_t<T>* data, size_t num)
    {
        auto it_data_page = data->map.find(page);
        if(it_data_page == data->map.end()) return false;

        size_t position_page = num + 1;
        if(!it_data_page->second.empty()) it_data_page->second.pop();
        if(!it_data_page->second.empty()) position_page = it_data_page->second.front();

        auto it_cache_page = cache_map.find(page);
        if(it_cache_page == cache_map.end())
        {
            processing_new_element(page, position_page);
            return false;
        } else
        {
            processing_hit_element(page, position_page, it_cache_page->second);
            return true;
        }
    }
    void processing_new_element(const T& page, size_t position_page)
    {
        size_t current_size  = cache_heap.size();
        if(current_size >= size)
        {
            auto it_delete = std::prev(cache_heap.end());
            if (it_delete != cache_heap.end() && it_delete->first > position_page)
            {
                cache_map.erase(it_delete->second);
                cache_heap.erase(it_delete);
                auto it_new = cache_heap.insert({position_page ,page});
                cache_map[page] = it_new.first;
            }
        }
        else
        {
            auto it_new = cache_heap.insert({position_page ,page});
            cache_map[page] = it_new.first;
        }
    }
    void processing_hit_element(const T& page, size_t position_page, typename std::multimap<Position, T>::iterator it)
    {
        cache_heap.erase(it);
        auto it_new = cache_heap.insert({position_page ,page});
        cache_map[page] = it_new.first;
    }
    cache_t(size_t sz) : size(sz) {};
};

