#ifndef CACHE_FUNC
#define CACHE_FUNC
#include <unordered_map>

template <typename T>
struct Node_map
{
   T value;
   size_t freq;
   std::list<T>::iterator it;
};

template <typename T>
struct cache_t
{
    size_t size;
    size_t min_freq_ = 1;
    std::unordered_map<T, Node_map<T>> hash_id;
    std::unordered_map<size_t, std::list<T>> hash_fr;
    bool update_cache(T page, cache_t* cache)
    {
        auto it_id = cache->hash_id.find(page);
        if(it_id == cache->hash_id.end())
        {
            Node_map<T> node = {};
            node.value = page;
            node.freq = 1;
            if(cache->size <= cache->hash_id.size())
            {
                auto it_min_fr= cache->hash_fr.find(cache->min_freq_);
                T rm_value = it_min_fr->second.front();
                it_min_fr->second.pop_front();
                if(it_min_fr->second.empty()) cache->hash_fr.erase(it_min_fr);
                cache->hash_id.erase(rm_value);
                // если эл не найден и места нет
            }
            // эл не найден но размер есть
            cache->hash_fr[node.freq].push_back(page);
            node.it = --cache->hash_fr[node.freq].end();
            cache->min_freq_ = 1;
            cache->hash_id[node.value] = node;

        } else
        {
        // эл найден
            auto it_fr = cache->hash_fr.find(it_id->second.freq);
            it_fr->second.erase(it_id->second.it);
            if(it_fr->second.empty()) cache->hash_fr.erase(it_fr);

            if(cache->min_freq_ == it_id->second.freq) { cache->min_freq_ = it_id->second.freq + 1; }
            ++(it_id->second.freq);

            auto& lst = cache->hash_fr[it_id->second.freq];
            lst.push_back(page);
            it_id->second.it = --lst.end();
        }
    } //добавить учет хитов
    cache_t(size_t sz) : size_(sz) {};
};
#endif CACHE_FUNC
