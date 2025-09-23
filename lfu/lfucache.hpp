#pragma once
#include <unordered_map>
#include <list>
#include <cstddef>

template <typename T>
struct Node_map
{
   T value;
   size_t freq;
   typename std::list<T>::iterator it;
};

template <typename T>
struct cache_t
{
    size_t size_;
    size_t min_freq_ = 1;
    std::unordered_map<T, Node_map<T>> hash_id;
    std::unordered_map<size_t, std::list<T>> hash_fr;
    void update_cache(T page, size_t* hits)
    {
        auto it_id = hash_id.find(page);
        if(it_id == hash_id.end())
        {
            //std::cout << "i dont find " << page;
            Node_map<T> node = {};
            node.value = page;
            node.freq = 1;
            if(size_ <= hash_id.size())
            {
                //std::cout << "full\n";
                auto it_min_fr= hash_fr.find(min_freq_);
                T rm_value = it_min_fr->second.front();
                //std::cout << "i remove " << rm_value << "\n";
                it_min_fr->second.pop_front();
                if(it_min_fr->second.empty()) hash_fr.erase(it_min_fr);
                hash_id.erase(rm_value);
            }
            hash_fr[node.freq].push_back(page);
            node.it = --hash_fr[node.freq].end();
            min_freq_ = 1;
            hash_id[node.value] = node;

        } else
        {

            (*hits)++;
            //std::cout << "hit" << page << "\n";
            auto it_fr = hash_fr.find(it_id->second.freq);
            it_fr->second.erase(it_id->second.it);
            if(it_fr->second.empty()) hash_fr.erase(it_fr);

            if(it_fr->second.empty() && min_freq_ == it_id->second.freq ) { min_freq_ = it_id->second.freq + 1; }
            it_id->second.freq += 1;

            auto& lst = hash_fr[it_id->second.freq];
            lst.push_back(page);
            it_id->second.it = --lst.end();
        }
    }
    cache_t(size_t sz) : size_(sz) {};
};

