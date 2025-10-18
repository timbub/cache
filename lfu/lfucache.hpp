#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include <cstddef>
#include <iterator>
#include <cassert>

namespace cache {
    template <typename PageT, typename KeyT> PageT slow_get_page(const KeyT key) {
        PageT page = static_cast<PageT>(key); //get page
        return page;
    }

    template <typename KeyT, typename PageT>
    struct Node_map
    {
        size_t freq;
        PageT  page;
        using ListIt = typename std::list<KeyT>::iterator;
        ListIt it;
    };

    template <typename KeyT, typename PageT>
    class Cache_t
    {
        const size_t MIN_FR = 1;
        using MapIt = typename std::unordered_map<KeyT, Node_map<KeyT,PageT>>::iterator;

        size_t size_;
        size_t min_freq_ = MIN_FR;
        std::unordered_map<KeyT, Node_map<KeyT,PageT>> hash_id;
        std::unordered_map<size_t, std::list<KeyT>> hash_fr;

        template <typename F>
        void processing_new_element(const KeyT& key, F slow_get_page)
        {
            if(size_ <= hash_id.size())
            {
                auto it_min_fr =  hash_fr.find(min_freq_);
                assert(it_min_fr != hash_fr.end() && "Element with min frequency was not found\n");

                KeyT rm_value = it_min_fr->second.front();
                it_min_fr->second.pop_front();
                if(it_min_fr->second.empty()) hash_fr.erase(it_min_fr);
                hash_id.erase(rm_value);
            }
            PageT page = slow_get_page(key);
            hash_fr[MIN_FR].push_back(page);
            hash_id.emplace(page, Node_map<KeyT, PageT>{MIN_FR, page, std::prev(hash_fr[MIN_FR].end())});
            min_freq_ = MIN_FR;
        }
        void processing_hit_element(const KeyT& key, MapIt it_id)
        {
            auto it_fr = hash_fr.find(it_id->second.freq);
            it_fr->second.erase(it_id->second.it);
            if(it_fr->second.empty()) hash_fr.erase(it_fr);

            if(it_fr->second.empty() && min_freq_ == it_id->second.freq ) { min_freq_ = it_id->second.freq + 1; }
            it_id->second.freq += 1;

            auto& lst = hash_fr[it_id->second.freq];
            PageT page = it_id->second.page;
            lst.push_back(page);
            it_id->second.it = std::prev(lst.end());
        }
    public:
        template <typename F>
        bool update_cache(const KeyT& key, F slow_get_page)
        {
            auto it_id = hash_id.find(key);
            if(it_id == hash_id.end())
            {
                processing_new_element(key, slow_get_page);
                return false;
            } else
            {
                processing_hit_element(key, it_id);
                return true;
            }
        }
        Cache_t(size_t sz) : size_(sz) {};
    };
}

