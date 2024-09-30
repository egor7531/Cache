#pragma once

#include <iterator>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>


namespace cache
{
    template <typename T, typename KeyT = int>
    class perfect_cache_t
    {
            const size_t capacity_ = 0;
            int hits_ = 0;
            
            struct cache_node_t 
            {
                T       page;
                KeyT    key;
            };

            std::list<cache_node_t> cache_;
            std::unordered_map<KeyT, std::list<size_t>> hash_;
            std::unordered_set<KeyT> dataSet_;
            
            using CacheIt = typename std::list<cache_node_t>::iterator;

            bool is_full() const { return capacity_ == cache_.size(); }

            void delete_elem()
            {
                size_t maxPosition = 0;
                CacheIt erasingElem = {};

                for (auto cacheElem = cache_.begin(); cacheElem != cache_.end(); cacheElem++)
                {
                    if (hash_.find(cacheElem->key) != hash_.end())
                    {
                        auto nearestElemPosition = hash_[cacheElem->key].begin();

                        if (*nearestElemPosition > maxPosition)
                        {
                            maxPosition = *nearestElemPosition;
                            erasingElem = cacheElem;
                        }
                    }

                    else
                    {
                        erasingElem = cacheElem;
                        break;
                    }
                }
                
                dataSet_.erase(erasingElem->key);
                cache_.erase(erasingElem);
            }

        public:
            perfect_cache_t(const size_t capacity, const std::vector<KeyT>& data): capacity_(capacity)
            {
                size_t position = 0;

                for (auto elem : data)
                    hash_[elem].push_back(position++);
            }

            int get_hits() const { return hits_; }

            template <typename F> 
            void lookup_update(KeyT key, F slow_get_page)
            {
                auto setHit = dataSet_.find(key);

                if (setHit == dataSet_.end())
                {
                    if (hash_[key].size() == 1)
                        return;
                
                    if (is_full())
                        delete_elem();

                    dataSet_.insert(key);
                    cache_.push_back({slow_get_page(key), key});
                }

                else
                    hits_++;
                
                hash_[key].pop_front();

                if (hash_[key].size() == 0)
                    hash_.erase(key);
            }   
    };
}


void perfect_cache();