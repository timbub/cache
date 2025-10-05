#pragma once
#include <unordered_map>
#include <list>
#include <cstddef>

const size_t MIN_FR = 1;
template <typename T>
struct Node_map
{
   T value;
   size_t freq;
   typename std::list<T>::iterator it;
};

template <typename T>
class cache_t
{
    size_t size_;
    size_t min_freq_ = MIN_FR;
    std::unordered_map<T, Node_map<T>> hash_id;
    std::unordered_map<size_t, std::list<T>> hash_fr;
void processing_new_element(T page)
{
    if(size_ <= hash_id.size())
    {
        auto it_min_fr= hash_fr.find(min_freq_);
        T rm_value = it_min_fr->second.front();
        it_min_fr->second.pop_front();
        if(it_min_fr->second.empty()) hash_fr.erase(it_min_fr);
        hash_id.erase(rm_value);
    }
    hash_fr[MIN_FR].push_back(page);
    hash_id.emplace(page, Node_map<T>{page, MIN_FR, --hash_fr[MIN_FR].end()});
    min_freq_ = MIN_FR;
}
void processing_hit_element(T page, typename std::unordered_map<T, Node_map<T>>::iterator it_id)
{
        auto it_fr = hash_fr.find(it_id->second.freq);
        it_fr->second.erase(it_id->second.it);
        if(it_fr->second.empty()) hash_fr.erase(it_fr);

        if(it_fr->second.empty() && min_freq_ == it_id->second.freq ) { min_freq_ = it_id->second.freq + 1; }
        it_id->second.freq += 1;

        auto& lst = hash_fr[it_id->second.freq];
        lst.push_back(page);
        it_id->second.it = --lst.end();
}
public:
    void update_cache(T page, size_t* hits)
    {
        auto it_id = hash_id.find(page);
        if(it_id == hash_id.end())
        {
            processing_new_element(page);

        } else
        {
            (*hits)++;
            processing_hit_element(page, it_id);
        }
    }
    cache_t(size_t sz) : size_(sz) {};
};

