#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

namespace cache
{
    template <typename T, typename KeyT = int>
    class lfu_cache_t
    {   
            size_t capacity;
            size_t size;
            int hits;

            struct freq_node_t;
            using FreqIterator = typename std::list<freq_node_t>::iterator;
            
            struct cache_node_t
            {
                T               page;
                KeyT            key;
                FreqIterator    freqIt;
            };
            
            struct freq_node_t
            {
                size_t freqSize;
                std::list<cache_node_t> sublist;
            };

            std::list<freq_node_t> cache;

            using ListIt = typename std::list<cache_node_t>::iterator;
            std::unordered_map<KeyT, ListIt> hash;

        public:
            lfu_cache_t(size_t cap): capacity(cap), size{0}, hits{0} {}

            int get_hits() const { return hits; }

            bool full() const { return capacity == cache.size(); }

            template <typename F> 
            bool lookup_update(KeyT key, F slow_get_page)
            {
                auto hit = hash.find(key);

                if(hit == hash.end())
                {
                    if(full())
                        delete_min_counting(key);

                    if(cache.size() == 0 || cache.front().freqSize != 0)
                        cache.push_front({});

                    push_elem(key, slow_get_page);

                    return false;
                }

                add_new_hit(hit->second);
                
                hits++;

                return true;
            }

            template <typename F>
            void push_elem(KeyT key, F slow_get_page)
            {
                cache.front().sublist.push_front({slow_get_page(key), key, cache.begin()});
                hash.emplace(key, cache.front().sublist.begin());
                size++;
            }

            void delete_min_counting(KeyT key)
            {   
                hash.erase(cache.front().sublist.back().key);
                cache.front().sublist.pop_back();
                size--;
            }

            void add_new_hit(auto iterator)
            {
                size_t frequency = iterator->freqIt->freqSize;
                
                if (iterator->freqIt == std::prev(cache.end()))
                    cache.push_back({frequency + 1, {}});

                else if(std::next(iterator->freqIt)->freqSize != frequency + 1)
                    cache.insert(std::next(iterator->freqIt), {frequency + 1, {}});

                FreqIterator next_freq_iterator = std::next(iterator->freqIt);

                next_freq_iterator->sublist.splice(next_freq_iterator->sublist.begin(), 
                                                iterator->freqIt->sublist, iterator);

                if (iterator->freqIt->sublist.size() == 0)
                    cache.erase(iterator->freqIt);

                iterator->freqIt = next_freq_iterator;
            }
    };
}
