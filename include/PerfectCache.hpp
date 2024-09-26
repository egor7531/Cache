#pragma once

#include <iterator>
#include <list>
#include <unordered_map>

namespace cache
{
    template <typename T, typename KeyT = int>
    class perfect_cache_t
    {
            size_t capacity_ = 0;
            int hits_ = 0;
            
            std::list<std::pair<KeyT, T>> cache_;

    };
}