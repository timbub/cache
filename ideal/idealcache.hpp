#pragma once
#include <list>
#include <unordered_map>
#include <queue>
#include <cstddef>
#include <iostream>

template <typename T>
struct data_t
{
    size_t size;
    using hash_t = std::unordered_map<T, std::queue<int>>;
    hash_t hash;
    std::vector<T> dataset;
    data_t(size_t sz) : size(sz), dataset(sz) {};
};

template <typename T>
struct cache_t
{
    size_t size;
    std::list<T> list;
    void update_cache(size_t* hits, data_t<T>* data, size_t num)
    {
        for(int i = 0; i < data->size; i++)
        {
            size_t l_size = list.size();
            auto it_l = list.begin();
            T page = data->dataset[i];
            auto it_id = data->hash.find(page);
            if(!find_page(page, l_size, &it_l))
            {
                if(!it_id->second.empty()) it_id->second.pop();
                std::cout << "list SIZE " << l_size <<"size" << size << "\n";
                if(size <= l_size)
                {
                    //if(!it_id->second.empty()) it_id->second.pop();
                    auto it_delete = find_to_delete(page, list, l_size, data);
                    if (it_delete != list.end())
                    {
                      std::cout << "i change " << *it_delete << " on " << page;
                      *it_delete = page;
                      std::cout << " new " << *it_delete << std::endl;
                    }
                } else
                {
                    list.push_front(page);
                    //if(!it_id->second.empty()) it_id->second.pop();
                }

            } else
            {
                std::cout << "i hit" << page << "\n";
                (*hits)++;
                if(!it_id->second.empty()) it_id->second.pop();
            }
            print_cache(&list);
        }
    }
    typename std::list<T>::iterator find_to_delete(T page, typename std::list<T>& lst, size_t l_size, data_t<T>* data)
    {
        auto it_delete = lst.begin();
        auto it_l      = lst.begin();

        if (data->hash.find(page)->second.empty())
        {
            std::cout << "no chance for " << page << std::endl;
            return lst.end();
        }
        size_t max_position = data->hash.find(page)->second.front();

        for(int i = 0; i < l_size; i++)
        {
            if(data->hash.find(*it_l)->second.empty())
            {
                it_delete = it_l;
                return it_l;
            }
            size_t current_position = data->hash.find(*it_l)->second.front();
            if(max_position < current_position)
            {
                max_position = current_position;
                it_delete = it_l;
                std::cout << "candidate " << *it_delete << " position " << max_position << std::endl;
            }
            it_l++;
        }
        return it_delete;
    }
    bool find_page(T page, size_t l_size, typename std::list<T>::iterator* it_l)
    {
        for (int i = 0; i < l_size; i++)
        {
            if(**it_l == page) return true;
            (*it_l)++;
        }
        return false;
    }
    void print_cache(std::list<T> *list)
    {
        for (const T &x: *list)
        {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    cache_t(size_t sz) : size(sz) {};
};

