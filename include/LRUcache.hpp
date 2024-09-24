#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

namespace cache
{
    template <typename T, typename KeyT = int>
    class lru_cache_t
    {
            size_t capacity_ = 0;
            int hits_ = 0;

            std::list<std::pair<KeyT, T>> cache_;

            using ListIt = typename std::list<std::pair<KeyT, T>>::iterator;
            std::unordered_map<KeyT, ListIt> hash_;

        public:
            
            lru_cache_t(size_t capacity): capacity_(capacity) {}
            
            int get_hits() const { return hits_; }
            
            bool full() const { return capacity_ == cache_.size(); }

            template <typename F> 
            bool lookup_update(KeyT key, F slow_get_page)
            {
                auto hit = hash_.find(key);

                if(hit == hash_.end())
                {
                    if(full())
                    {
                        hash_.erase(cache_.back().first);
                        cache_.pop_back();
                    }

                    cache_.emplace_front(key, slow_get_page(key));
                    hash_.emplace(key, cache_.begin());
                    
                    return false;
                }

                auto eltit = hit->second;
                if(eltit != cache_.begin())
                    cache_.splice(cache_.begin(), cache_, eltit);
                
                hits_++;

                return true;
            }
    };
}