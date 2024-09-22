#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

namespace cache
{
    template <typename T, typename KeyT = int>
    class lru_cache_t
    {
            size_t capacity;
            int hits;

            std::list<std::pair<KeyT, T>> cache;

            using ListIt = typename std::list<std::pair<KeyT, T>>::iterator;
            std::unordered_map<KeyT, ListIt> hash;

        public:
            
            lru_cache_t(size_t cap): capacity(cap), hits{0} {}
            
            int get_hits() const { return hits; }
            
            bool full() const { return capacity == cache.size(); }

            template <typename F> 
            bool lookup_update(KeyT key, F slow_get_page)
            {
                auto hit = hash.find(key);

                if(hit == hash.end())
                {
                    if(full())
                    {
                        hash.erase(cache.back().first);
                        cache.pop_back();
                    }

                    cache.emplace_front(key, slow_get_page(key));
                    hash.emplace(key, cache.begin());
                    return false;
                }

                auto eltit = hit->second;
                if(eltit != cache.begin())
                    cache.splice(cache.begin(), cache, eltit);//, std::next(eltit));
                
                hits++;

                return true;
            }
    };
}