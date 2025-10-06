#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include <cstddef>
#include <iterator>

namespace cache {
    template <typename T>
    struct Node_map
    {
       size_t freq;
       using ListIt = typename std::list<T>::iterator;
       ListIt it;
    };

    template <typename T>
    class Cache_t
    {
        const size_t MIN_FR = 1;
        using MapIt = typename std::unordered_map<T, Node_map<T>>::iterator;

        size_t size_;
        size_t min_freq_ = MIN_FR;
        std::unordered_map<T, Node_map<T>> hash_id;
        std::unordered_map<size_t, std::list<T>> hash_fr;
        void processing_new_element(const T& page)
        {
            if(size_ <= hash_id.size())
            {
                auto it_min_fr =  hash_fr.find(min_freq_);
                if(  it_min_fr == hash_fr.find(min_freq_)) std::cerr << "element with min frequency was not found" << std::endl;

                T rm_value = it_min_fr->second.front();
                it_min_fr->second.pop_front();
                if(it_min_fr->second.empty()) hash_fr.erase(it_min_fr);
                hash_id.erase(rm_value);
            }
            hash_fr[MIN_FR].push_back(page);
            hash_id.emplace(page, Node_map<T>{MIN_FR, std::prev(hash_fr[MIN_FR].end())});
            min_freq_ = MIN_FR;
        }
        void processing_hit_element(const T& page, MapIt it_id)
        {
            auto it_fr = hash_fr.find(it_id->second.freq);
            it_fr->second.erase(it_id->second.it);
            if(it_fr->second.empty()) hash_fr.erase(it_fr);

            if(it_fr->second.empty() && min_freq_ == it_id->second.freq ) { min_freq_ = it_id->second.freq + 1; }
            it_id->second.freq += 1;

            auto& lst = hash_fr[it_id->second.freq];
            lst.push_back(page);
            it_id->second.it = std::prev(lst.end());
        }
    public:
        bool update_cache(const T& page)
        {
            auto it_id = hash_id.find(page);
            if(it_id == hash_id.end())
            {
                processing_new_element(page);
                return false;
            } else
            {
                processing_hit_element(page, it_id);
                return true;
            }
        }
        Cache_t(size_t sz) : size_(sz) {};
    };
}

