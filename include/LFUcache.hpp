#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

namespace cache
{
    template <typename T, typename KeyT = int>
    class lfu_cache_t
    {   
            size_t capacity_ = 0;
            size_t size_ = 0;
            int hits_ = 0;

            struct freq_node_t;
            using FreqIterator = typename std::list<freq_node_t>::iterator;
            
            struct cache_node_t
            {
                T               page_;
                KeyT            key_;
                FreqIterator    freqIt_;
            };
            
            struct freq_node_t
            {
                size_t freq_ = 1;
                std::list<cache_node_t> sublist_;
            };

            std::list<freq_node_t> cache_;

            using ListIt = typename std::list<cache_node_t>::iterator;
            std::unordered_map<KeyT, ListIt> hash_;

            template <typename F>
            void push_elem(KeyT key, F slow_get_page)
            {
                cache_.front().sublist_.push_front({slow_get_page(key), key, cache_.begin()});
                hash_.emplace(key, cache_.front().sublist_.begin());
                size_++;
            }

            void delete_elem()
            {   
                hash_.erase(cache_.front().sublist_.back().key_);
                cache_.front().sublist_.pop_back();
                size_--;
            }

            void add_new_hit(ListIt iterator)
            {
                size_t frequency = iterator->freqIt_->freq_;
                
                if (iterator->freqIt_ == std::prev(cache_.end()))
                    cache_.push_back({frequency + 1, {}});

                else if(std::next(iterator->freqIt_)->freq_ != frequency + 1)
                    cache_.insert(std::next(iterator->freqIt_), {frequency + 1, {}});

                FreqIterator nextFreqIt = std::next(iterator->freqIt_);

                nextFreqIt->sublist_.splice(nextFreqIt->sublist_.begin(), 
                                                iterator->freqIt_->sublist_, iterator);

                if (iterator->freqIt_->sublist_.size() == 0)
                    cache_.erase(iterator->freqIt_);

                iterator->freqIt_ = nextFreqIt;
            }

        public:
            lfu_cache_t(size_t capacity): capacity_(capacity) {}

            bool is_full() const { return capacity_ == size_; }
            bool is_empty() const { return size_ == 0; }
            int get_hits() const { return hits_; }

            template <typename F> 
            bool lookup_update(KeyT key, F slow_get_page)
            {
                auto hit = hash_.find(key);

                if(hit == hash_.end())
                {
                    if(is_full())
                        delete_elem();

                    if(is_empty() || cache_.front().freq_ != 1) 
                        cache_.push_front({});

                    push_elem(key, slow_get_page);

                    return false;
                }

                add_new_hit(hit->second);
                hits_++;

                return true;
            }
    };
}
